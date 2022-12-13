/*

*/

#include "navigation.h"

Navigation::Navigation(Motor::Timer timer) : motor_(Motor(timer)) {}

void Navigation::setDirectionAdvance()
{
    Motor::Direction direction = Motor::Direction::ADVANCE;
    motor_.adjustDirection(direction);
}

void Navigation::setDirectionReverse()
{
    Motor::Direction direction = Motor::Direction::REVERSE;
    motor_.adjustDirection(direction);
}

void Navigation::turnLeftSlight()
{
    motor_.ajustPWMPourcentage(80, 50);
}

void Navigation::turnLeftHard()
{
    motor_.ajustPWMPourcentage(200, 50);
}

void Navigation::turnLeft()
{
    motor_.ajustPWMPourcentage(130, 70);
}

void Navigation::turnRightSlight()
{
    motor_.ajustPWMPourcentage(70, 100);
}

void Navigation::turnRightHard()
{
    motor_.ajustPWMPourcentage(50, 200);
}

void Navigation::turnRight()
{
    motor_.ajustPWMPourcentage(70, 130);
}

void Navigation::goStraightSlow()
{
    motor_.ajustPWMPourcentage(250, 250);
    _delay_ms(20);
    motor_.ajustPWMPourcentage(90, 70);
}

void Navigation::goStraight()
{
    motor_.ajustPWMPourcentage(150, 150);
}

void Navigation::goStraightFast()
{
    motor_.ajustPWMPourcentage(210, 210);
}

void Navigation::customSpeed(uint8_t valueA, uint8_t valueB) {
    motor_.ajustPWMPourcentage(valueA, valueB);
}

void Navigation::stop()
{
    motor_.ajustPWMPourcentage(0, 0);
}