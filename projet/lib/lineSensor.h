/* 
 Authors: Astir Tadrous, Motassembellah Mohamed Bassiouni, Elena Doumon, Raphael Ramanitranja
 Due date: December 8th 2022
 Group: 02
 
 Description of the program: Essentially this class controls the line Sensor, it gives precise instructions to the robot's
                             Navigation and Motor class. 

 Material identification (Broches I/O) : Cytron LSS05 using the Port A
*/

#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "navigation.h"
#include <util/delay.h>
#include "counter.h"


class LineSensor
{
    public:
        LineSensor();
        bool isAtStopSignNoObstacle();
        bool isAtStopSignObstacle();
        bool detectBlackLine(const uint8_t brocheAnMask);
        void followLine();
        void followLineObstacles();
        void followLineObstacle2ndCurve();
        void followLineAfterObstacles();
        void continueStraight();
        void adjustSlightlyRight();
        void adjustHardlyRight();
        void adjustSlightlyLeft();
        void adjustHardlyLeft();
        void stopAtSign();
        void takeYourLeft();
        void takeYourRight();
        void specialFollowLineWallDetection();
        void zigZag();
        bool isStillLost();
        bool isAtFinalStop();
        bool finishedZigZag();
        bool lost();

        bool heyStop = false;
        bool okayStoped = false;
        bool endZigZag = false;
        bool zigZagLastDetectedLeft = true;
        bool obstacleN = false;
        bool obstacleO = false;
        bool stateSfollowLine = false;

        uint8_t counter = 0;
        uint8_t numberOfZigZag = 0;
        
        Counter followLineCounter;

    private:
        Navigation navigation = Navigation(Motor::Timer::TIMER2);
        const uint8_t SENSOR_EXTREME_LEFT = (1 << PA0);
        const uint8_t SENSOR_LEFT = (1 << PA1);
        const uint8_t SENSOR_MIDDLE = (1 << PA2);
        const uint8_t SENSOR_RIGHT = (1 << PA3);
        const uint8_t SENSOR_EXTREME_RIGHT = (1 << PA4);
        const uint8_t CALIBRATION = (1 << PA5);
};