#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>



int main(){

    const uint8_t DEL_OFF = 0x00;
    const uint8_t DEL_RED = (1 << PA0);
    const uint8_t DEL_GREEN = (1 << PA1);
    const uint8_t READ_DELAY = 30;
    const uint8_t COLOR_CHANGE_DELAY = 100;
    const uint8_t A0A1_OUTMODE = 0b00000011;
    const uint8_t ALL_INMODE = 0b00000000;
    DDRD = ALL_INMODE;
    DDRA = A0A1_OUTMODE;
    while (true){
        uint8_t D2_MASK1 = PIND & (1 << PIND2);
        bool FIRST_READ = D2_MASK1;
        if (FIRST_READ)
        {
            _delay_ms(READ_DELAY);
            uint8_t D2_MASK2 = PIND & (1 << PIND2);
            bool SECOND_READ = D2_MASK2;
            
            if (SECOND_READ)
            {
                PORTA = DEL_RED;
                _delay_ms(COLOR_CHANGE_DELAY);

                PORTA = DEL_GREEN;
                _delay_ms(COLOR_CHANGE_DELAY);
            }
            else if (D2_MASK2 == false)
            {
                PORTA = DEL_OFF;
            }
        }
        else
        {
            PORTA = DEL_OFF;
        }
        }
    return 0;   
}

