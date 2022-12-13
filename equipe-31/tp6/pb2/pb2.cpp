/*
 * 
 * Nom: pb2
 * Auteures: Elena Doumon & Raphael Ramanitranja
 * Description du programme: Quand il y a peu de lumière sur la photorésistance, la DEL est verte. Quand c'est une lumière ambiante, la DEL est ambrée. 
 * Lorsqu'on teste avec la source de lumière de nos téléphones (une lumière forte), la DEL est rouge. 
 * 
 * Identifications matérielles (Broches I/O): La broche A du atmega324pa est l'entrée. La broche B est la sortie. 
 * Le ports A0 est l'entrée pour la photorésistance (ils sont reliés).
 * Les ports B0 et B1 sont liés à une DEL bicolore. 
 * Il y a un fil rouge et noir est qui est lié du PORT Avcc/Ground pour alimenter le breadboard breadboard. 
 * 
 */
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "can.h"

const uint8_t AMBER_TOGGLE_DELAY = 1;
const uint8_t DEL_RED = (1 << PA0);
const uint8_t DEL_GREEN = (1 << PA1);
const uint8_t DEL_OFF = 0;

const uint8_t STRONG_LIGHT = 230;
const uint8_t LOW_LIGHT = 210;
const uint8_t UNSIGNIFICANT_VALUE = 2;
const uint8_t POSITION = 0;


void setInitialPorts()
{
    DDRA &= (1 << PORTA0);
    DDRB |= (1 << PORTB0) | (1 << PORTB1);
}

void setLedRed()
{
  PORTB = DEL_RED;
}

void setLedGreen()
{
  PORTB = DEL_GREEN;
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
  PORTB = DEL_OFF;
}

int main()
{
    uint8_t valueOfLight;
    can converter = can();
    setInitialPorts();
    while (true)
    {
        valueOfLight = converter.lecture(POSITION) >> UNSIGNIFICANT_VALUE;
        if (valueOfLight < LOW_LIGHT)
        {
            setLedGreen();
        }
        else if (valueOfLight > STRONG_LIGHT)
        {
            setLedRed();
        }
        else
        {
            setLedAmber();
        }
    }
}