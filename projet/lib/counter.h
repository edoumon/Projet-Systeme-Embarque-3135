/* 
 Authors: Astir Tadrous, Motassembellah Mohamed Bassiouni, Elena Doumon, Raphael Ramanitranja
 Due date: December 8th 2022
 Group: 02
 
 Description of the program: The counter cpp works like a stopwatch that uses microseconds

 Material identification (Broches I/O) : PD5 - OC1A is used as the output compare of our timer
*/


#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

class Counter
{
public:
    Counter();
    uint16_t convertTimeToCycles(uint32_t timeUs);

    void startTimerCTC(uint16_t cycles);
    void startTimerPWM(uint16_t cycles);
    void startTimerFastPWM(uint16_t cycles);

    volatile bool detectionAllowed = true;
    volatile bool finishedFollowLine = false;
    volatile bool finishedZigZag = false;
    volatile uint8_t numberTimer = 0;

    bool followLineEndA = false;

private:
    const uint16_t PRESCALER_ = 1024;
    const uint32_t FREQUENCY_HZ_ = 8000000;
};
