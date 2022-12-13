/* 
 authors: Astir Tadrous and Motassembellah Mohamed Bassiouni 
 Due date: 17 October 2022
 Group: 02

 Description of the program:
    Robot that can tan. When the light is low (hiding the photoresistor), the DEL becomes green. When more light is directed at the photoresistor, the DEL becomes red. 
    Otherwise, the DEL is amber

 Material used:
    - bicolor DEL: cathode (+) => PB1, anode (-) => PB0
    - Wire connected to PA0
    - Wire connected to vcc and ground of PORTA
    - resistor of 10K
    - photoresistor
    - condenser of 0.1 µF 
*/

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#include "can.h"

const uint8_t DELAY_CHANGE_COLORS = 5;

enum COLOR
{
    RED = (1 << PB1),
    GREEN = (1 << PB0),
    OFF = ~(1 << PB0) & ~(1 << PB1)
};

void initialization()
{
    const uint8_t A0_INPUT_MODE = ~(1 << DDA0);
    const uint8_t B0B1_OUTPUT_MODE = (1 << DDB0) | (1 << DDB1);
    DDRB |= B0B1_OUTPUT_MODE;
    DDRA &= A0_INPUT_MODE; 

}

void turnGreenLight()
{
    PORTB = GREEN;
}

void turnRedLight()
{
    PORTB = RED;
}

void turnAmberLight()
{
    turnGreenLight();
    _delay_ms(DELAY_CHANGE_COLORS);
    turnRedLight();
    _delay_ms(DELAY_CHANGE_COLORS); 
}

int main() {

    initialization();
    can objectCan;
    uint8_t intensity = 0;
    const uint8_t LOW_INTENSITY = 140; // determined by trial-error
    const uint8_t HIGH_INTENSITY = 176; // determind by trial-error


    while(true) 
    {
        intensity = objectCan.lecture(PINA0) >> 2; // intensity is on 10 bits but we only want 8 bits

        if (intensity < LOW_INTENSITY) 
        {
            turnGreenLight();
        }

        else if (intensity > HIGH_INTENSITY) 
        {
            turnRedLight();
        }
    
        else 
        {       
            turnAmberLight();
        }
            
    }   

    return 0;
}