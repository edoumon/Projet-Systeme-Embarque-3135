
#define F_CPU 8000000
#include <avr/io.h>
#include <stdio.h>
#include "button.h"
#include "can.h"
#include "button.h"
#include "memoire_24.h"
#include "communication.h"
#include "counter.h"
#include "debug.h"
#include "navigation.h"
#include "led.h"

Counter counter = Counter();
Motor::Timer wheelsTimer = Motor::Timer::TIMER0;
Navigation navigation = Navigation(wheelsTimer);
Button buttonD2 = Button(INT0, Button::typeEdge::FALLING);
Led led = Led(PB0, PB1);

ISR(TIMER1_COMPA_vect)
{
    counter.gExpiredTimer = true;
}

ISR(INT0_vect)
{
    led.setLedGreen();
}


int main()
{

    while (true)
    {
        uint16_t time = counter.convertTimeToCycles(3000000);
        counter.startTimerCTC(time);

        while (!(counter.gExpiredTimer))
        {
            led.setLedGreen();
        }
        
        led.setLedRed();
        navigation.setDirectionReverse();
        navigation.goStraight();
        _delay_ms(1000);
        navigation.stop();
    }
}
