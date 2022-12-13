/* 
 Authors: Astir Tadrous, Motassembellah Mohamed Bassiouni, Elena Doumon, Raphael Ramanitranja
 Due date: December 8th 2022
 Group: 02
 
 Description of the program: This class inherits from all the other classes. It is inspired by the Singleton design.
                             It's goal is to translate the pseudocode of the assignment and execute all the necessary
                             actions.

 Material identification (Broches I/O) : ---
*/

#include "parcours.h"

Parcours::Parcours() {}

void Parcours::behaviourState(uint8_t state)
{

    switch (state)
    {
    case A:
        stateA();
        break;
    case B:
        stateB();
        break;
    case S:
        stateS();
        break;
    case END:
        break;
    }
}

void Parcours::nextState(uint8_t state)
{
    switch (state)
    {
    case A:
        gState = B;
        break;
    case B:
        gState = S;
        break;
    case S:
        gState = A;
        break;
    }
};

uint8_t Parcours::getNumberOfObstacles(uint16_t readingAddress)
{
    uint8_t *number;
    memory.lecture(readingAddress, number);
    return *number;
}

void Parcours::stateA()
{
    led.blinkLedGreen();
    lineSensor.continueStraight();
    _delay_ms(700);

    while (true)
    {
        if (wallSensor.lineSensor.followLineCounter.followLineEndA)
        {
            break;
        }

        wallSensor.detectDistance();
    }

    navigation.stop();
    _delay_ms(2000);

    if (wallSensor.numberOfObstacles == 2)
    {
        wallSensor.distance = wallSensor.NO_OBSTACLE;
        wallSensor.saveDistance();
    }

    memory.ecriture(3, wallSensor.numberOfObstacles);
    _delay_ms(5);

    gState = states::END;
}

void Parcours::stateB()
{
    led.blinkLedRed();
    lineSensor.continueStraight();
    _delay_ms(700);
    while (!(lineSensor.isAtStopSignNoObstacle()))
    {
        lineSensor.followLine();
    }

    //Dependemment du nombre d'obstacles detecte, l'ordre de l'écriture dans la memoire sera differente
    //il faut dont l'appeler dans le bon ordre (explication du 0-1-2)

    if (numberOfObstacles == 2)
    {
        wallSensor.avoid2Obstacles(1);
        wallSensor.avoid2Obstacles(2);
        wallSensor.avoid2Obstacles(0);
    }
    else if (numberOfObstacles == 3)
    {
        wallSensor.avoid3Obstacles(2);
        wallSensor.avoid3Obstacles(1);
        wallSensor.avoid3Obstacles(0);
    };

    navigation.givePower();
    lineSensor.continueStraight();
    _delay_ms(700);

    while (!(lineSensor.isAtFinalStop()))
    {
        lineSensor.followLineAfterObstacles();
    }

    navigation.stop();
    _delay_ms(2000);

    gState = states::S;
}

void Parcours::stateS()
{
    lineSensor.followLineCounter.finishedFollowLine = false;
    lineSensor.followLineCounter.finishedZigZag = false;
    led.blinkLedAmber();

    navigation.customSpeed(150, 150);
    _delay_ms(700);

    // Nous utilisons un timer afin de le forcer a suivre la ligne jusqu'à ce qu'il 
    // puisse entreprendre le zigzag, ce processus prends environ 4 secondes
    uint16_t timeFollowLine = lineSensor.followLineCounter.convertTimeToCycles(4000000);
    lineSensor.followLineCounter.startTimerCTC(timeFollowLine);

    while (!(lineSensor.followLineCounter.finishedFollowLine))
    {
        lineSensor.followLine();
    }

    navigation.turnRightSlight();
    _delay_ms(500);
    while (lineSensor.numberOfZigZag < 3)
    {
        lineSensor.zigZag();
    }
    lineSensor.adjustSlightlyRight();

    lineSensor.stateSfollowLine = true;
    while (true)
    {
        if (lineSensor.lost())
        {
            led.setLedGreen();
            _delay_ms(70);
            if (lineSensor.lost())
            {
                break;
            }
        }
        lineSensor.followLine();
    }
    navigation.stop();
    _delay_ms(2000);

    navigation.stationnement();

    piezo.emitHighSound();
    _delay_ms(1000);
    piezo.stopSound();

    lineSensor.followLineCounter.finishedFollowLine = false;
    gState = states::END;
}
