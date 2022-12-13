/* 
 Authors: Astir Tadrous, Motassembellah Mohamed Bassiouni, Elena Doumon, Raphael Ramanitranja
 Due date: December 8th 2022
 Group: 02
 
 Description of the program: Essentially this class controls the reaction of the detection of an object.
                             This object uses a Memoire_24 instance to write and read in the memory.

 Material identification (Broches I/O) : Infrared captor Sharp GP2Y0A21YK0F on PA6
*/

#pragma once
#define F_CPU 8000000
#include "communication.h"
#include "can.h"
#include "memoire_24.h"
#include "motor.h"
#include "sound.h"
#include "navigation.h"
#include "lineSensor.h"
#include "counter.h"

class WallSensor
{

    public:
    
        enum Distance
        {

            CLOSE = 0,
            FAR = 1,
            NO_OBSTACLE = 2,

        };

        WallSensor();
        ~WallSensor() = default;
        uint8_t readValue();
        void detectDistance();
        void saveDistance();
        Distance distance;
        uint8_t getObstaclePosition(uint16_t readingAddress);
        void avoid2Obstacles(uint16_t pathPosition);
        void avoid3Obstacles(uint16_t pathPosition);
        Counter stopwatch;
        LineSensor lineSensor;
        uint16_t outOfReadingZone = stopwatch.convertTimeToCycles(2000000);
        uint8_t numberOfObstacles;


    private:
        uint8_t data;
        uint16_t writingAddress = 0;
        Motor::Timer wheelTimer = Motor::Timer::TIMER2;
        Navigation motors = Navigation(wheelTimer);
        can converter;
        Communication communication;
        Memoire24CXXX memory;
        Sound sound;
};
