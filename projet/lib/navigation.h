/* 
 Authors: Astir Tadrous, Motassembellah Mohamed Bassiouni, Elena Doumon, Raphael Ramanitranja
 Due date: November 8th 2022
 Group: 02

 Description of the program: The navigaftion class is used to dictate a variety of movements the robot can do such as parking.
                            It uses a Motors object with its Timer to choose the behaviour. 
                            
 Material Identification: When using timer 0, PB5 and PB6 are used to control the direction of the motors
                          When using timer 2, PD4 and PD5 are used to control the direction of the motors
*/

#pragma once
#include "motor.h"

class Navigation
{
    public:
        Navigation(Motor::Timer timer);
        void setDirectionAdvance();
        void setDirectionReverse();
        void turnRightSlight();
        void turnRightHard();
        void turnRight();
        void turnLeftSlight();
        void turnLeftHard();
        void turnLeft();
        void goStraightSlow();
        void goStraight();
        void goStraightFast();
        void stationnement();
        void zigZag();
        void stop();
        void customSpeed(uint8_t valueA, uint8_t valueB);
        void givePower();
        void giveMaxPower();
        ~Navigation() = default;
        
        bool zigZagEnd = false;
    private:
        Motor motor_;
};
