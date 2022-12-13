#include <avr/io.h>
#define F_CPU 8000000
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>


void delayUs(uint16_t pulseWidthUs, const uint8_t partialDelayUs)
{
    int NO_PARTIALDELAYS = pulseWidthUs / partialDelayUs;

    for (int i = 0; i < NO_PARTIALDELAYS; i++)
    {
        _delay_us(partialDelayUs);
    }

}


void AttenuateLight(uint16_t DelOffTimeMs, const uint8_t partialDelayUs,const uint8_t DelColor, const uint8_t DelOff)
{
    for (uint16_t accumulatedTimeMs = 0; accumulatedTimeMs < DelOffTimeMs; accumulatedTimeMs++)
    {
        uint16_t PULSE_WIDTH_OFF = accumulatedTimeMs / 3;
        uint16_t PULSE_WIDTH_ON = 1000 - PULSE_WIDTH_OFF;

        PORTA = DelColor;
        delayUs(PULSE_WIDTH_ON, partialDelayUs);
        
        PORTA = DelOff;
        delayUs(PULSE_WIDTH_OFF, partialDelayUs);
    }
}


int main()
{
    const uint8_t DEL_GREEN = (1 << PA1);
    const uint8_t DEL_RED = (1 << PA0);
    const uint8_t DEL_OFF= ~(1 << PA1) | ~(1 << PA0);
    const uint8_t D2_INMODE = ~(1 << DDD2);
    const uint8_t A0A1_OUTMODE = (1 << DDA1) | (1 << DDA0);
    uint16_t DEL_OFF_TIME_MS = 3000;
    const uint8_t PARTIAL_DELAY_US = 35;
    const uint16_t COLOR_CHANGE_DELAY = 2000;

    DDRD = D2_INMODE;
    DDRA = A0A1_OUTMODE;

    AttenuateLight(DEL_OFF_TIME_MS, PARTIAL_DELAY_US, DEL_RED, DEL_OFF);

    _delay_ms(COLOR_CHANGE_DELAY);

    AttenuateLight(DEL_OFF_TIME_MS, PARTIAL_DELAY_US, DEL_GREEN, DEL_OFF);

    return 0;
    
}


