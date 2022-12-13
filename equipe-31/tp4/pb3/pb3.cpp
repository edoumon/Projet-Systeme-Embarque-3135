#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(TIMER1_COMPA_vect)
{
    TIFR1 |= (1 << OCF1A);
}

void initialisationTimer()
{
    cli();
    DDRA |= (1 << PA2) | (1 << PA3);

    TCNT1 = 0;
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
    TIMSK1 = (1 << OCIE1A);
    OCR1A = 14000;
    sei();
}

void initialisationTimerPwm()
{
    cli();
    DDRB |= (1 << PB2) | (1 << PB3);
    TCNT0 = 0;

    TCCR0A =
        (1 << WGM00) |
        (1 << COM0A1);
    TCCR0B = (1 << CS01);
    sei();
}

void ajustementPwm('modifier ici')
{

    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5

    // page 130 de la description technique du ATmega324PA)

    OCR1A = 'modifier ici';

    OCR1B = 'modifier ici';

    // division d'horloge par 8 - implique une fréquence de PWM fixe

    TCCR1A = 'modifier ici';

    TCCR1B = 'modifier ici';

    TCCR1C = 0;
}

int main()
{
    initialisationTimerPwm();
    while (true)
    {
        ajustementPwm();
    }

    return 0;
}