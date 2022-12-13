/* 
 Authors: Astir Tadrous, Motassembellah Mohamed Bassiouni, Elena Doumon, Raphael Ramanitranja
 Due date: December 8th 2022
 Group: 02
 
 Description of the program: This main.cpp takes care of the switch case and handles the ISRs 

 Material identification (Broches I/O) : The Special One (Name of the Robot)
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <stdio.h>
#include "parcours.h"

Parcours parcours;
Led led = Led(PB0, PB1);

ISR(INT1_vect)
{
    _delay_ms(30);
    parcours.nextState(parcours.gState);
    EIFR |= (1 << INTF1);
};

ISR(INT0_vect)
{
    _delay_ms(30);
    parcours.interruptButton.gButtonPressed = true;
    EIFR |= (1 << INTF0);
};

ISR(TIMER1_COMPA_vect)
{
    parcours.wallSensor.stopwatch.detectionAllowed = true;
    parcours.wallSensor.lineSensor.followLineCounter.finishedFollowLine = true;
    parcours.lineSensor.followLineCounter.finishedFollowLine = true;
    parcours.lineSensor.followLineCounter.finishedZigZag = true;
    TCCR1B = 0;
}
int main()
{

    parcours.interruptButton.gButtonPressed = false;

    while (parcours.interruptButton.gButtonPressed == false)
    {
        switch (parcours.gState)
        {
        case Parcours::states::A:
            led.setLedGreen();
            break;
        case Parcours::states::B:
            led.setLedRed();
            break;
        case Parcours::states::S:
            led.setLedAmber();
        }
    }

    while (parcours.gState != Parcours::states::END)
    {
        parcours.behaviourState(parcours.gState);
    }
    return 0;
}