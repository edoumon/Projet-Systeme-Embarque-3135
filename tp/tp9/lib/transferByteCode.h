/* 
 Authors: Astir Tadrous, Motassembellah Mohamed Bassiouni, Elena Doumon, Raphael Ramanitranja
 Due date: November 9 2022
 Group: 02
 Description of the program:

   While using a communication instance, the progrem method allows us to write the content of a file to the external memory.

 Material identification:
    - PC
    - SerieViaUSB
    - Printer Cable 
    - Microcontroller
*/

#pragma once
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "memoire_24.h"
#include "communication.h"

class TransferByteCode
{
public:
    TransferByteCode();
    void transferTheCode();
    volatile bool transfered = false;

private:
    Communication communication = Communication();
    Memoire24CXXX memory;
    uint16_t sizeOfInstructions = 0x0000;

    void writeTotalInstructions();
    void writeProgramToMemory();
};