#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


volatile uint8_t expiredTimer = 0;
volatile uint8_t isD2Pressed = 0;
const uint8_t D2_INMODE = ~(1 << DDD2);
const uint8_t A0A1_OUTMODE = (1 << DDA1) | (1 << DDA0);

enum COLOR
{
    RED = (1 << PA1),
    GREEN = (1 << PA0),
    OFF = ~(1 << PA0) & ~(1 << PA1)
};

void initializeInterruptD2()
{

    cli();                // interrompre tous les interruptions
    EIMSK |= (1 << INT0); // activate interrupts on timer 0
    EICRA = (1 << ISC00); //| (1 << ISC01); 
    sei(); // interrupt can now resume
}


void initializeTimer (uint16_t duree) 
{

    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée

    TCNT1 = 0; // il ne faut pas le modifier dans le programme par risque de malfonctionnement du systeme, on le met a 0. (regroupe TCNT1H et TCNT1L qui forment TCNT1)

    OCR1A = duree;

    TCCR1A |= (1 << COM1A0) | (1 << COM1A1); // set output A on compare match

    TCCR1B |= (1 << CS10) | (1 << CS12); // set prescaler to 1024

    TCCR1C = 0; // on laisse à 0

    TIMSK1 = (1 << OCIE1A); // OCIE1A to activate compare match A.
}

ISR(TIMER1_COMPA_vect) 
{
    expiredTimer = 1;
}


ISR (INT0_vect)
{

    _delay_ms(30);
    isD2Pressed = 1;
    EIFR |= (1 << INTF0);
}


int main() {
    DDRD = D2_INMODE;
    DDRA = A0A1_OUTMODE;
    initializeInterruptD2();

    do {

        _delay_ms(10000);
        PORTA = RED;
        _delay_ms(100);
        PORTA = OFF;
        initializeTimer(7812);

    } while (isD2Pressed == 0 && expiredTimer == 0 );


// Une interruption s'est produite. Arrêter toute
// forme d'interruption. Une seule réponse suffit.

    cli ();
// Verifier la réponse
    //'modifier ici'
    if (isD2Pressed == 1) {
        PORTA = GREEN;
    }

    if(expiredTimer == 1) {
        PORTA = RED;
    }

    return 0;

}