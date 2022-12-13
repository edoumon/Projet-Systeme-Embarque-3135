
#include "decipher.h"


Decipher::Decipher()
{
}

void Decipher::readTotalInstructions()
{
    uint8_t firstByteSize = readByte();
    sizeOfInstructions = static_cast<uint16_t>(firstByteSize) << 8;

    uint8_t secondByteSize = readByte();
    sizeOfInstructions |= static_cast<uint16_t>(secondByteSize);

    sizeOfInstructions -= 2;
}

uint8_t Decipher::readByte()
{
    uint8_t data;
    memory.lecture(currentAddress, &data);
    currentAddress++;
    return data;
}

void Decipher::readLine()
{
    uint8_t instruction = readByte();
    uint8_t operand = readByte();
    translate(instruction, operand);
}

void Decipher::decipherCode()
{
    readTotalInstructions();

    for (uint16_t i = 0; i < sizeOfInstructions / 2; i++)
    {
        readLine();
    }
}
void Decipher::translate(uint8_t instruction, uint8_t operand)
{
    if (instruction == dbt || active)
    {
        switch (instruction)
        {
        case dbt:
            active = true;
            break;

        case att:
            for (int i = 0; i < operand; i++)
            {
                _delay_ms(25);
            }
            break;

        case dal:
            if (operand == 1)
            {
                led.setLedGreen();
            }
            else if (operand == 2)
            {
                led.setLedRed();
            }
            break;

        case det:
            led.setLedOff();
            break;

        case sgo:
        {
            sound.initVariables(operand);
            sound.startTimerSound();
            break;
        }

        case sar:
            sound.stopSound();
            break;

        case mar60:
        case mar61:
            navigation.stop();
            break;

        case mav:
            navigation.setDirectionAdvance();
            navigation.customSpeed(operand, operand);
            break;

        case mre:
            navigation.setDirectionReverse();
            navigation.customSpeed(operand, operand);
            break;

        case trd:
            navigation.setDirectionAdvance();
            navigation.turnRight();
            break;

        case trg:
            navigation.setDirectionAdvance();
            navigation.turnLeft();
            break;

        case dbc:
            loopCounter = operand + 1;
            beginAddress = currentAddress;

            break;

        case fbc:
            if (loopCounter != 0)
            {
                loopCounter -= 1;
                currentAddress = beginAddress;
            }

            break;

        case fin:
            sound.stopSound();
            led.setLedOff();
            navigation.stop();
            active = false;
            break;
        }
    }
}