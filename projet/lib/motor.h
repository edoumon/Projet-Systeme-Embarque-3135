/*
 Authors: Astir Tadrous, Motassembellah Mohamed Bassiouni, Elena Doumon, Raphael Ramanitranja
 Due date: 31 october 2022
 Group: 02
 Description of the program:

    The motor series controls the motors of the robot but does the basic movements. It adjusts the direction of the motors and their speed,
    whilst using either the timer 0 or timer 2.

 Material Identification: When using timer 0, PB5 and PB6 are used to control the direction of the motors
                          When using timer 2, PD4 and PD5 are used to control the direction of the motors
*/

#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

class Motor
{
    public:
        enum class Timer
        {
            TIMER0,
            TIMER2
        };

        enum class Direction
        {
            ADVANCE,
            REVERSE
        };

        Motor(Timer timer);
        void adjustDirection(Direction direction);
        void ajustPWMPourcentage(uint8_t valueA, uint8_t valueB);
        ~Motor() = default;

    private:
        Timer timer_;
        Direction direction_;
        const uint8_t DDRB3_B4_B5_B6_OUT = (1 << DDB4) | (1 << DDB3) | (1 << DDB5) | (1 << DDB6);
        const uint8_t ENABLE_PWM_B3_B4_TIMER0 = (1 << PB3) | (1 << PB4);
        const uint8_t DDRD4_D5_D6_D7_OUT = (1 << DDD6) | (1 << DDD7) | (1 << DDD5) | (1 << DDD4);
        const uint8_t ENABLE_PWM_D6_D7_TIMER2 = (1 << PD6) | (1 << PD7);
        const uint8_t DIRECTION_ADVANCE_TIMER0 = ~(1 << PB5) & ~(1 << PB6);
        const uint8_t DIRECTION_REVERSE_TIMER0 = (1 << PB5) | (1 << PB6);
        const uint8_t DIRECTION_ADVANCE_TIMER2 = ~(1 << PD4) & ~(1 << PD5);
        const uint8_t DIRECTION_REVERSE_TIMER2 = (1 << PD4) | (1 << PD5);
};