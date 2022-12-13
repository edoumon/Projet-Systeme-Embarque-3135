#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>


// const uint8_t MOTOR_ON = (1 << PD4) | (1 << PD5); 
// const uint8_t MOTOR_OFF = ~(1 << PD4) & ~(1 << PD5); 


const uint8_t MOTOR_ON = (1 << PD5) ; 
const uint8_t MOTOR_OFF = ~(1 << PD5); 
const uint8_t DIRECTION_DRIVE = (1 << PD4);
const uint8_t DIRECTION_REVERSE = ~(1 <<PD6);

uint8_t MYDIRECTION = DIRECTION_DRIVE;

void delayUs(int pulseWidthUs)
{
    const int partialDelayUs = 100;
    int NO_PARTIALDELAYS = pulseWidthUs / partialDelayUs;

    for (int i = 0; i < NO_PARTIALDELAYS; i++) {
        _delay_us(partialDelayUs);
    }

}

void GeneratePWM(int frequency, int percentage, bool reverseMode)
{
    uint32_t PERIOD_US= ((uint32_t)1000*1000)/frequency;
    const uint32_t TOTAL_TIME_US = (uint32_t)2000 * 1000;
    int TOTAL_NO_CYCLES = TOTAL_TIME_US / PERIOD_US;
    int WIDTH_ON = (percentage * PERIOD_US) / 100;
    int WIDTH_OFF = PERIOD_US - WIDTH_ON;
    if (reverseMode)
    {
        MYDIRECTION = (1 << PD4);
    }
    else {
        MYDIRECTION = 0;
    }

    for (int numberCycles = 1; numberCycles <= TOTAL_NO_CYCLES; numberCycles++)
    {
        PORTD = MOTOR_ON | MYDIRECTION;
        delayUs(WIDTH_ON);

        PORTD = MOTOR_OFF | MYDIRECTION;
        delayUs(WIDTH_OFF);
    }
}

void VariatePWM(int frequency, bool driveMode)
{
    for (int percentage = 0; percentage <= 100; percentage+= 25)
    {
        GeneratePWM(frequency, percentage, driveMode);
    }
    PORTD = MOTOR_OFF;
}



int main()
{


    const uint8_t D2_INMODE = ~(1 << DDD2);
    const uint8_t D4D5_OUTMODE = (1 << DDD4) | (1 << DDD5);
    DDRD = D2_INMODE | D4D5_OUTMODE;

    VariatePWM(60, true);
    VariatePWM(400, false);

    return 0;
}


