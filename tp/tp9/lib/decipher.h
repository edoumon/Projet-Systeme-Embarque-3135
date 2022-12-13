
/* 
 Authors: Astir Tadrous, Motassembellah Mohamed Bassiouni, Elena Doumon, Raphael Ramanitranja
 Due date: November 9 2022
 Group: 02
 Description of the program:

    The methods of this class reads the memory and interprets the code thanks to a switch-case.
    Using this class should be paired with the TransferByteCode class as it writes in the memory.
    Multiple objects such as led, sound and navigation are instancied so that we may control the behavior of the robot.
 Material identification:
    - PC
    - SerieViaUSB
    - Printer Cable 
    - Microcontroller
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

class Decipher
{
public:
    Decipher();
    void decipherCode();
    enum instruction
    {
        dbt = 0x01,
        att = 0x02,
        dal = 0x44,
        det = 0x45,
        sgo = 0x48,
        sar = 0x09,
        mar60 = 0x60,
        mar61 = 0x61,
        mav = 0x62,
        mre = 0x63,
        trd = 0x64,
        trg = 0x65,
        dbc = 0xC0,
        fbc = 0xC1,
        fin = 0xFF

    };

private:
    uint8_t readByte();
    void readTotalInstructions();
    void readLine();
    void translate(uint8_t instruction, uint8_t operand);
    bool active = true;

    Memoire24CXXX memory;
    uint16_t sizeOfInstructions = 0;
    uint16_t currentAddress = 0;
    Led led = Led(PB0, PB1);
    Motor::Timer wheelsTimer = Motor::Timer::TIMER2;
    Navigation navigation = Navigation(wheelsTimer);
    Sound sound = Sound();
    uint8_t loopCounter = 0;
    uint16_t beginAddress;
};
