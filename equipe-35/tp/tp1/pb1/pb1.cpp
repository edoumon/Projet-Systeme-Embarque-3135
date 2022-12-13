#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

int main(){

    
    DDRA = 0b00000011;

    while (true){

        int delay_counter = 0;

        // RougevsVert

        PORTA = 0b00000001;
        _delay_ms(2500);

        PORTA = 0b00000010;
        _delay_ms(2500);


        // Jaune
        while(delay_counter < 2500){

            PORTA = 0b00000001;
            _delay_ms(5);
            
            PORTA = 0b00000010;
            _delay_ms(5);

            delay_counter+=10;
        }
    }
    return 0;
}