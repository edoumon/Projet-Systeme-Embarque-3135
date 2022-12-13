
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
    volatile bool gExpiredTimer;

private:
    const uint16_t PRESCALER_ = 1024;
    const uint32_t FREQUENCY_HZ_ = 8000000;
};
