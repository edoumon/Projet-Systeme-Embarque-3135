#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t MOTOR_ON = (1 << PD5);
const uint8_t MOTOR_OFF = ~(1 << PD5);
const uint8_t ADVANCE = ~(1 << PD4);
const uint8_t REVERSE = (1 << PD4);

void initialisation (bool Direction) 
{
    if (Direction == true) { 
        DDRD |= MOTOR_ON;
        DDRD &= ADVANCE;
    }
    
    else {
        DDRD |= MOTOR_ON | REVERSE;
    }

    TCNT1  = 0;

} 


void ajustementPwm (uint8_t valeurA, uint8_t valeurB) {

// mise à un des sorties OC1A et OC1B sur comparaison

// réussie en mode PWM 8 bits, phase correcte

// et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5

// page 130 de la description technique du ATmega324PA)
cli();

OCR1A = valeurA ;

OCR1B = valeurB ;


// division d'horloge par 8 - implique une fréquence de PWM fixe
//(1 << COM1B1)
TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
TCCR1B |= (1 << CS11);

TCCR1C = 0;
sei();

}

int main() {

    //uint8_t tempsAttente = 2000;
    initialisation(true); 

    while (true) {

        ajustementPwm(0,0);
        _delay_ms(10000);
        ajustementPwm(63, 63);
        _delay_ms(10000);
        ajustementPwm(127,127);
        _delay_ms(10000);
        initialisation(false);
        ajustementPwm(191,191);
        _delay_ms(10000);
        ajustementPwm(250,250);
        _delay_ms(10000);

    }

    return 0;
}