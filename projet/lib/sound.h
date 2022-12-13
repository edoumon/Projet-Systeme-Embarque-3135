/* 
 Authors: Astir Tadrous, Motassembellah Mohamed Bassiouni, Elena Doumon, Raphael Ramanitranja
 Due date: December 8th 2022
 Group: 02
 
 Description of the program: This class is in charge of controlling the sound of the piezo.

 Material identification (Broches I/O) : piezo on PB3
*/

#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

class Sound
{
public:
    Sound();
    void emitSound();
    void emitHighSound();
    void emitLowSound();
    void initVariables(uint8_t note);
    void stopSound();

private:
    const uint16_t PRESCALER_ = 256;
    const uint32_t FREQUENCY_PROCESSOR_ = 8000000;
    float noteFrequency_;
    float noCyclesOcr0A_;
};
