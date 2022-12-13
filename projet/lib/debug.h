/* 
 Authors: Astir Tadrous, Motassembellah Mohamed Bassiouni, Elena Doumon, Raphael Ramanitranja
 Due date: December 8th 2022
 Group: 02
 
 Description of the program: This class is used to print data in the terminal as a method of debug

 Material identification (Broches I/O) : --
*/

#pragma once
#include <avr/io.h>
#include "communication.h"


#ifdef DEBUG

#define DEBUG_PRINT(x) print(x) // ou par RS-232
#define DEBUG_PRINT_SENTENCE(sentence) printSentence(sentence)
 
#else

#define DEBUG_PRINT(x) while(true){} // code mort

#define DEBUG_PRINT_SENTENCE(sentence) while (true){}
    
#endif

void print(uint8_t x);
void printSentence(char sentence[]);
