#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t presentState = 0;
const uint8_t D2_INMODE = ~(1 << DDD2);
const uint8_t A0A1_OUTMODE = (1 << DDA1) | (1 << DDA0);

enum COULEUR
{
    RED = (1 << PA1),
    GREEN = (1 << PA0),
    OFF = ~(1 << PA0) & ~(1 << PA1)
};

void makeDelAmber()
{
    PORTA = RED;
    _delay_ms(10);
    PORTA = GREEN;
    _delay_ms(10);
}

void initializeInterruptD2()
{

    cli();                // interrompre tous les interruptions
    EIMSK |= (1 << INT0); // activate interrupts on timer 0
    EICRA = (1 << ISC00); //| (1 << ISC01);
    sei(); // interrupt can now resume
}

ISR(INT0_vect)
{

    _delay_ms(30);
    if (presentState == 5)
    {
        presentState = 0;
    }

    else
        presentState++;

    EIFR |= (1 << INTF0);
}

int main()
{
    DDRD = D2_INMODE;
    DDRA = A0A1_OUTMODE;
    initializeInterruptD2();

    while (true)
    {
        switch (presentState)
        {
        case 0:
            PORTA = RED;
            break;

        case 1:
            makeDelAmber();
            break;

        case 2:
            PORTA = GREEN;
            break;

        case 3:
            PORTA = RED;
            break;

        case 4:
            PORTA = OFF;
            break;

        case 5:
            PORTA = RED;
            break;
        }
    }

    return 0;
}