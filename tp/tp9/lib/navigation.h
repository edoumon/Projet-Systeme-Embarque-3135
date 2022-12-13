/*

*/

#include "motor.h"

class Navigation
{
public:
    Navigation(Motor::Timer timer);
    void setDirectionAdvance();
    void setDirectionReverse();
    void turnRightSlight();
    void turnRightHard();
    void turnRight();
    void turnLeftSlight();
    void turnLeftHard();
    void turnLeft();
    void goStraightSlow();
    void goStraight();
    void goStraightFast();
    void stop();
    void customSpeed(uint8_t valueA, uint8_t valueB);
    ~Navigation() = default;

private:
    Motor motor_;
};
