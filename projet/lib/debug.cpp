/* 
 Authors: Astir Tadrous, Motassembellah Mohamed Bassiouni, Elena Doumon, Raphael Ramanitranja
 Due date: December 8th 2022
 Group: 02
 
 Description of the program: This class is used to print data in the terminal as a method of debug

 Material identification (Broches I/O) : --
*/

#include "debug.h"

Communication comm;

void print(uint8_t x)
{
    comm.transferUart(x);
}

void printSentence(char sentence[])
{
    uint8_t i, j;
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 20; j++)
        {
            comm.transferUart(sentence[j]);
        }
    }
}