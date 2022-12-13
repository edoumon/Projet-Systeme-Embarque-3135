
#include "transferByteCode.h"
#include "led.h"
TransferByteCode::TransferByteCode()
{
}

void TransferByteCode::transferTheCode()
{
    writeTotalInstructions();
    writeProgramToMemory();
}

void TransferByteCode::writeTotalInstructions()
{
    uint16_t firstByteSize = static_cast<uint16_t>(communication.receiveData());
    uint16_t secondByteSize = static_cast<uint16_t>(communication.receiveData());

    sizeOfInstructions |= firstByteSize << 0x08 | secondByteSize;

    memory.ecriture(0x0000, static_cast<uint8_t>(sizeOfInstructions >> 0x08));
    _delay_ms(5);
    memory.ecriture(0x0001, static_cast<uint8_t>(sizeOfInstructions));
    _delay_ms(5);
}

void TransferByteCode::writeProgramToMemory()
{
    uint8_t dataToBeExecuted;

    for (uint16_t i = 2; i < sizeOfInstructions; i++)
    {
        dataToBeExecuted = communication.receiveData();
        memory.ecriture(i, dataToBeExecuted);
        _delay_ms(5);
    }
    transfered = true;
}
