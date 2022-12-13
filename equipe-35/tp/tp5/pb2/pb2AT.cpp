
 #include <avr/io.h> 
 #define F_CPU 8000000
 #include <util/delay.h>
 #include <avr/interrupt.h>
 #include "memoire_24.h"
 

void initializationUART (void) {
    UBRR0H = 0;

    UBRR0L = 0xCF;

    UCSR0A |= (1 << MPCM0);

    UCSR0B |=  (1<<RXEN0)| (1<<TXEN0) ;


    UCSR0C |= (1<<USBS0) | (3<<UCSZ00);
}

void transmissionUART (uint8_t data) {

    while (!(UCSR0A & (1 << UDRE0))) {

    }

    UDR0 = data;
}

int main() {
    //Memoire24CXXX memoire;
    DDRD = (1 << PD0) | (1 << PD1);
    initializationUART();
    char mots[21] = "Le robot en INF1900\n";

    uint8_t i, j;

    for ( i = 0; i < 100; i++ ) {

        for ( j=0; j < 20; j++ ) {

            transmissionUART ( mots[j] );

        }

    }      
    return 0;
}
