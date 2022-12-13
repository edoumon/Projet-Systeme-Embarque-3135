#define F_CPU 8000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

const uint8_t TEMPS_DEBOUNCE = 10;
volatile bool gMinuterieExpiree;
volatile bool gBoutonPoussoir;
const uint8_t D2_MASK = (1 << PD2);
const uint8_t DEL_RED = (1 << PA0);
const uint8_t DEL_GREEN = (1 << PA1);
const uint8_t DEL_OFF = 0;
const uint8_t TOGGLE_DELAY = 100;

ISR(TIMER1_COMPA_vect)
{
    gMinuterieExpiree = true;
}

ISR(INT0_vect)
{
    gBoutonPoussoir = true;
    _delay_ms(TEMPS_DEBOUNCE);
    if (!(PIND & D2_MASK))
    {
        gBoutonPoussoir = false;
    }
}

void initialisation()
{
    cli();
    DDRA |= (1 << DDA0) | (1 << DDA1);
    DDRD &= ~(1 << DDD2);
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}

void partirMinuterie(uint16_t duree)
{
    gMinuterieExpiree = false;
    TCNT1 = 0; //fromwhereitstarts
    OCR1A = duree;
    TCCR1A = 0;
    TCCR1B |= (1 << CS12) | (1 << CS10);
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A);
}

void setLedRed()
{
    PORTA = DEL_RED;
}

void setLedGreen()
{
    PORTA = DEL_GREEN;
}

void setLedOff()
{
    PORTA = DEL_OFF;
}

int main()
{
    initialisation();

    for (int i = 0; i < 100; i++)
    {
        PORTA ^= DEL_RED;
        _delay_ms(TOGGLE_DELAY);
    };

    partirMinuterie(7812); //start 1s
    do
    {
        setLedOff();
    } while (!gMinuterieExpiree && !gBoutonPoussoir);

    // Une interruption s'est produite. Arrêter toute
    // forme d'interruption. Une seule réponse suffit.
    cli();

    // Verifier la réponse

    if (gBoutonPoussoir && !gMinuterieExpiree)
    {
        setLedGreen();
    }

    return 0;
}