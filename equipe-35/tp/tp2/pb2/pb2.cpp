/* Problem 2

Authors : Astir Tadrous and Motassembellah Mohamed Bassiouni 
Due date : 16th September 2022
Group: 02 

Description of the program:

    Implementing a state machine that begins with the DEL on red and changes color to amber when the interrupt button is pressed. When the button is released, the DEL turns to green. 
    When the button is pressed again, the DEL changes to red. When the button is released, the DEL is off and when pressed for the 3rd time, the DEL turns to green. If the button is released 
    again, the state machine rebegins and the DEL changes to red.

Material used:

    - Del_bicolor: cathode (+) => PA0, anode (-) => PA1
    - Button: PD2

////////////////////////////////////////State Machine Table/////////////////////////////////////////

    Present State   |  INPUT (D2)  |     NEXT STATE    | OUTPUT (A1) | OUTPUT (A0) | VISUAL OUTPUT

    INITRED         |       0      |     INITRED       |      0      |      1      |    DEL_RED
    INITRED         |       1      |    GREENSTATE     |      1      |      1      |    DEL_AMBER

    GREENSTATE      |       0      |    GREENSTATE     |      1      |      0      |    DEL_GREEN
    GREENSTATE      |       1      |     OFFSTATE      |      0      |      1      |    DEL_RED

    OFFSTATE        |       0      |     OFFSTATE      |      0      |      0      |    DEL_OFF
    OFFSTATE        |       1      |      INITRED      |      1      |      0      |    DEL_GREEN
     
////////////////////////////////////////////////////////////////////////////////////////////////*/

#include <avr/io.h>
#define F_CPU 8000000
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

/*bool buttonIsPressed()
{
    if ((PIND & (1 << PIND2)))
    {
        return true;
    }

    return false;
}*/

void initializeInterruptD2()
{

    cli();                // interrompre tous les interruptions
    EIMSK |= (1 << INT0); // activate interrupts on timer 0
    EICRA = (1 << ISC00); //| (1 << ISC01); 
    sei(); // interrupt can now resume
}

void makeDelAmber(const uint8_t& redLight, const uint8_t& greenLight, const uint8_t& changeLightDelay)
{
    while (buttonIsPressed())
    {
        PORTA = redLight;
        _delay_ms(changeLightDelay);

        PORTA = greenLight;
        _delay_ms(changeLightDelay);
    }
}



int main()
{

    const uint8_t DEL_GREEN = (1 << PA1);
    const uint8_t DEL_RED = (1 << PA0);
    const uint8_t DEL_OFF= ~(1 << PA1) | ~(1 << PA0);
    const uint8_t D2_INMODE = ~(1 << DDD2);
    const uint8_t A0A1_OUTMODE = (1 << DDA1) | (1 << DDA0);
    const uint8_t READ_DELAY = 30;
    const uint8_t COLOR_CHANGE_DELAY = 10;


    DDRD = D2_INMODE;
    DDRA = A0A1_OUTMODE;


    enum class State 
    { 
        INITRED, GREENSTATE, OFFSTATE
    };

    State state = State::INITRED;

    while (true)
    {

        switch(state)
        {
            case State::INITRED:

            if (buttonIsPressed())
            {
                _delay_ms(READ_DELAY);
                if (buttonIsPressed())
                {
                    makeDelAmber(DEL_RED, DEL_GREEN, COLOR_CHANGE_DELAY);

                    state = State::GREENSTATE;
                }
            }

            else
            {
                PORTA = DEL_RED;
                state = State::INITRED;
            }

            break;




            case State::GREENSTATE:

            if (buttonIsPressed())
            {
                _delay_ms(READ_DELAY);
                if (buttonIsPressed())
                {
                    PORTA = DEL_RED;
                    
                    while (true)
                    {
                        if (!buttonIsPressed())
                        {
                            PORTA = DEL_OFF;
                            break;
                        }
                    }
                    state = State::OFFSTATE;
                }
            }
            
            else
            {
                PORTA = DEL_GREEN;
                state = State::GREENSTATE;
            }
          

            break;




            case State::OFFSTATE:

            if (buttonIsPressed())
            {
                _delay_ms(READ_DELAY);
                if (buttonIsPressed())
                {
                    PORTA = DEL_GREEN;

                    while (true)
                    {
                        if (!buttonIsPressed())
                        {
                            PORTA = DEL_RED;
                            state = State::INITRED;
                            break;
                        }
                    }
                }
            }

            else
            {
                PORTA = DEL_OFF;
                state = State::OFFSTATE;
            }

            break;
        }

    }

}

