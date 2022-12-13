/* 
 Authors: Astir Tadrous, Motassembellah Mohamed Bassiouni, Elena Doumon, Raphael Ramanitranja
 Due date: 31 october 2022
 Group: 02
 Description of the program:

    The Led files affect the bicolor Del of the robot. Hence, we can light it up in red, green and amber, or just keep in closed. 

 Material Identification: 
 
    - Can only be used with DDRB
*/
#include "led.h"

Led::Led(uint8_t pinCathode, uint8_t pinAnode)
{
    DDRB |= (1 << PB0) | (1 << PB1);
    delRed = (1 << pinCathode);
    delGreen = (1 << pinAnode);
}

void Led::setLedRed()
{
    PORTB = delRed;
}

void Led::setLedGreen()
{
    PORTB = delGreen;
}

void Led::setLedOff()
{
    PORTB = ~delRed & ~delGreen;
}

void Led::setLedAmber()
{
    for(uint16_t noCurrentIteration = 0; noCurrentIteration < NO_ITERATIONS; noCurrentIteration++)
    {
        setLedGreen();
        _delay_ms(5);
        setLedRed();
        _delay_ms(7);
    }
}
