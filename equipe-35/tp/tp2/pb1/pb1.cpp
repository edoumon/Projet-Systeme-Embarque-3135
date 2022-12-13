#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

/*

Authors: Motassembellah Mohamed Bassiouni and Astir Tadrous
Due date : 16th September 2022
Group: 02 


Description of the program:

    The following program is meant to display a green LED light for 2 seconds after pressing and releasing the switch 3 times. 
    Then, the counter automatically resets itself to be able to repeat the procedure again. 
    The program uses state machine in order to make this transition possible.

    State machines observe human behaviour (button is pressed or released) and interpret it as an input.
    Consequently, it decides whether they should remain in their state or change it and they also decide when to send electric power to make the green LED light appear.
    
    
Material used:

    - Del_bicolor: cathode (+) => PA0, anode (-) => PA1
    - Button: PD2



/////////////////////////State Machine Table///////////////////////////////

    Present state   | Input (D2)  |  Next state   | Output (A1)

    INITOFF         |      0      |    INITOFF    |      0
    INITOFF         |      1      |    INITOFF    |      0

    INITOFF         |      0      |    OFF1       |      0
    OFF1            |      1      |    OFF1       |      0

    OFF1            |      0      |   PRESSGREEN  |      0
    PRESSGREEN      |      1      |   PRESSGREEN  |      0

    PRESSGREEN      |      0      |    INITOFF    |      1

////////////////////////////////////////////////////////////////////////*/



bool buttonIsPressed()
{
    if ((PIND & (1 << PIND2)))
    {
        return true;
    }

    return false;
}

int main()

{
    const uint8_t DEL_GREEN = (1 << PA1);
    const uint8_t DEL_OFF = ~(1 << PA1) | ~(1 << PA0);
    const uint8_t D2_INMODE = ~(1 << DDD2);
    const uint8_t A0A1_OUTMODE = (1 << DDA1) | (1 << DDA0);
    const uint8_t READ_DELAY = 30;
    const uint16_t DEL_OFF_DELAY = 2000;

    DDRD = D2_INMODE;
    DDRA = A0A1_OUTMODE;
    
    enum class State 
    { 
        INITOFF, OFF1, PRESSGREEN
    };

    State state = State::INITOFF;

    while (true)
    {

        
        switch(state)
        {
            case State::INITOFF:

            if (buttonIsPressed())
            {
                _delay_ms(READ_DELAY);
    
                if (buttonIsPressed())
                {
                    while (true)
                    {
                        if (!buttonIsPressed())
                        {
                            PORTA = DEL_OFF;
                            state = State::OFF1;
                            break;
                        }
                    }
                }
            }

            else
            {
                PORTA = DEL_OFF;
                state = State::INITOFF;
            }


            break;


            case State::OFF1:

            if (buttonIsPressed())
            {
                _delay_ms(READ_DELAY);

                if (buttonIsPressed())
                {
                    while (true)
                    {
                        if (!buttonIsPressed())
                        {
                            PORTA = DEL_OFF;
                            state = State::PRESSGREEN;
                            break;
                        }
                    }
                }

                
            }

            else
            {
                PORTA = DEL_OFF;
                state = State::OFF1;
            }


            break;

            
            case State::PRESSGREEN:

            if (buttonIsPressed())
            {
                _delay_ms(READ_DELAY);
                if (buttonIsPressed())
                {
                    while (true)
                    {
                        if (!buttonIsPressed())
                        {
                            PORTA = DEL_GREEN;
                            _delay_ms(DEL_OFF_DELAY);
                            state = State::INITOFF;
                            break;
                        }
                    }
                }
            }

            else
            {
                PORTA = DEL_OFF;
                state = State::PRESSGREEN;
            }



            break;
        }


    }
    


}