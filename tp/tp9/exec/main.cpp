
#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <stdio.h>
#include "decipher.h"
#include "transferByteCode.h"

TransferByteCode transfer = TransferByteCode();
Decipher robot = Decipher();



int main()
{
    transfer.transferTheCode();
    robot.decipherCode();
}
