/* 
 Authors: Astir Tadrous, Motassembellah Mohamed Bassiouni, Elena Doumon, Raphael Ramanitranja
 Due date: December 8th 2022
 Group: 02
 
 Description of the program: This class inherits from all the other classes. It is inspired by the Singleton design.
                             It's goal is to translate the pseudocode of the assignment and execute all the necessary
                             actions.

 Material identification (Broches I/O) : ---
*/


#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <stdio.h>
#include "button.h"
#include "can.h"
#include "memoire_24.h"
#include "communication.h"
#include "counter.h"
#include "debug.h"
#include "navigation.h"
#include "led.h"
#include "sound.h"
#include "lineSensor.h"
#include "wallSensor.h"

class Parcours
{
public:
    Parcours();
    uint8_t getNumberOfObstacles(uint16_t readingAddress);
    void stateA();
    void stateB();
    void stateS();
    void behaviourState(uint8_t state);
    void nextState(uint8_t state);
    
    enum states
    {
        A,
        B,
        S,
        END
    };

    volatile states gState = states::A;
    Button interruptButton = Button(INT0, Button::typeEdge::FALLING);
    WallSensor wallSensor;
    LineSensor lineSensor;

private:
    
    uint8_t numberOfObstacles = getNumberOfObstacles(3);  
    Memoire24CXXX memory;
    Communication communication;
    Led led = Led(PB0, PB1);
    Motor::Timer wheelsTimer = Motor::Timer::TIMER2;
    Navigation navigation = Navigation(wheelsTimer);
    can converter = can();
    Counter stopwatch = Counter();
    Sound piezo;
};
