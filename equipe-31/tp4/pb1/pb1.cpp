
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t AMBER_TOGGLE_DELAY = 1;
const uint8_t DEL_RED = (1 << PA0);
const uint8_t DEL_GREEN = (1 << PA1);
const uint8_t DEL_OFF = 0;
volatile uint8_t gEtat = 0;


void initialisation(void)
{
    cli();
    DDRA |= (1 << PORTA0) | (1 << PORTA1);
    DDRD &= ~(1 << PD2);
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    EICRA &= ~(1 << ISC01);
    sei();
}

void setLedRed()
{
    PORTA = DEL_RED;
}

void setLedGreen()
{
    PORTA = DEL_GREEN;
}

void setLedAmber()
{
    setLedRed();
    _delay_ms(AMBER_TOGGLE_DELAY);
    setLedGreen();
    _delay_ms(AMBER_TOGGLE_DELAY);
}

void setLedOff()
{
    PORTA = DEL_OFF;
}

void behaviourD2(uint8_t etat)
{
    switch (etat)
    {
    case 0:
        setLedRed();
        break;
    case 1:
        setLedAmber();
        break;
    case 2:
        setLedGreen();
        break;
    case 3:
        setLedRed();
        break;
    case 4:
        setLedOff();
        break;
    case 5:
        setLedGreen();
        break;
    }
}

void whereD2Next(uint8_t etat)
{
    switch (etat)
    {
    case 0:
        gEtat = 1;
        behaviourD2(1);
        break;
    case 1:
        gEtat = 2;
        behaviourD2(2);
        break;
    case 2:
        gEtat = 3;
        behaviourD2(3);
        break;
    case 3:
        gEtat = 4;
        behaviourD2(4);
        break;
    case 4:
        gEtat = 5;
        behaviourD2(5);
        break;
    case 5:
        gEtat = 0;
        behaviourD2(0);
        break;
    }
}

ISR(INT0_vect)
{
    _delay_ms(30);
    // se souvenir ici si le bouton est pressé ou relâche
    // Voir la note plus bas pour comprendre cette instruction et son rôle

    whereD2Next(gEtat);

    EIFR |= (1 << INTF0);
}

int main()
{
    initialisation();
    setLedRed();
    while (true)
    {
        behaviourD2(gEtat);
    }
    return 0;
}
