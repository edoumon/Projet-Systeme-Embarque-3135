/*
 * 
 * Nom: pb2
 * Auteures: Elena Doumon & Raphael Ramanitranja
 * Description du programme: Jeu de programme utilisant un compteur affecter par le bouton blanc. 
 * 
 * Identifications matérielles (Broches I/O): La broche A du atmega324pa est l'entrée. La broche B est la sortie. 
 * Le port D2 est associé au bouton blanc du breadboard
 * Les ports B0 et B1 sont liés à une DEL bicolore. 
 * Il y a un fil rouge et noir est qui est lié du PORT Avcc/Ground pour alimenter le breadboard breadboard. 
 */

#include <avr/io.h>
#define F_CPU 8000000
#include <avr/interrupt.h>
#include <util/delay.h>

volatile bool gButtonP;
volatile uint8_t counter = 0;
const uint8_t DEBOUNCE_TIME = 10;

const uint8_t D2_MASK = (1 << PD2);
const uint8_t DEL_RED = (1 << PB0);
const uint8_t DEL_GREEN = (1 << PB1);
const uint8_t DEL_OFF = 0;
const uint8_t TOGGLE_DELAY = 250;

const uint8_t TWO = 2;
const uint8_t TWICEPERSECOND = 250;
const uint16_t DEMISECOND = 500;
const uint16_t ONESECOND = 1000;
const uint16_t TWOSECONDS = 2000;
const uint16_t MAXCOUNTER = 120;
const uint16_t ONESECONDCYCLE = 781;

ISR(TIMER1_COMPA_vect)
{
    counter += 1;
}

ISR(INT0_vect)
{
    gButtonP = true;
    _delay_ms(DEBOUNCE_TIME);
    if ((PIND & D2_MASK))
    {
        gButtonP = false;
    }
}

void initialisation()
{
    cli();
    DDRB |= (1 << DDB0) | (1 << DDB1);
    DDRD &= ~(1 << DDD2);
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}

void startTimer(uint16_t cycles)
{
    TCNT1 = 0;
    counter = 0;
    OCR1A = cycles;
    TCCR1A = 0;
    TCCR1B |= (1 << CS12) | (1 << CS10) | (1 << WGM12);
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A);
}

void setLedRed()
{
    PORTB = DEL_RED;
}

void setLedGreen()
{
    PORTB = DEL_GREEN;
}

void setLedOff()
{
    PORTB = DEL_OFF;
}

void flickerLedRed()
{
    for (uint8_t i = 0; i < (counter / TWO); i++)
    {
        setLedRed();
        _delay_ms(TWICEPERSECOND);
        setLedOff();
        _delay_ms(TWICEPERSECOND);
    };
}

void changeLights()
{
    setLedGreen();
    _delay_ms(DEMISECOND);
    setLedOff();
    _delay_ms(TWOSECONDS);

    flickerLedRed();

    setLedGreen();
    _delay_ms(ONESECOND);
    setLedOff();
}

int main()
{
    initialisation();

    while (true)
    {

        while (!gButtonP)
        {
        }
        //CALCUL POUR TROUVER CYCLE DE 1 SECONDE (781) : nombre de cycles = temps/période ET Période = fréquence de l'ordi/prescaler
        startTimer(ONESECONDCYCLE);
        while ((counter != MAXCOUNTER) && (gButtonP));

        cli();
        changeLights();
        sei();
    }
}