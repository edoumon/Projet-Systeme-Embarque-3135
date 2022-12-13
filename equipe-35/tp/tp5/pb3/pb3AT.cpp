#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "memoire_24.h"

#include <string.h>

// const uint8_t A0A1_OUTMODE = (1 << DDA1) | (1 << DDA0);
const uint8_t D0D1_OUTMODE = (1 << DDD1) | (1 << DDD0);

void initializationUART(void)
{
    UBRR0H = 0;

    UBRR0L = 0xCF;

    UCSR0A |= (1 << MPCM0);

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    UCSR0C |= (1 << USBS0) | (3 << UCSZ00);
}

void transmissionUART(uint8_t data)
{

    while (!(UCSR0A & (1 << UDRE0)))
    {
    }

    UDR0 = data;
}

int main()
{
    Memoire24CXXX memoire;
    DDRD = D0D1_OUTMODE;
    DDRA = 0xff;
    initializationUART();
    uint8_t writeSentence[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*t*r*t*e*h*e*E*"; // uint8_t n'est pas une déclaration de int, mais plus une déclaration d'un unsigned de 8 bits du type que je lui donnera
    uint8_t length = 44;
    uint16_t adress = 0x0000;
    uint8_t dataToReturn;

    /*uint8_t data[255];
    for (int i = 0; i <255; i++) {
        data[i] = 0xff;
    }

    memoire.ecriture(0x0000, data, 254);
    _delay_ms(5);*/

    memoire.ecriture(0x0000, writeSentence, strlen((char*)writeSentence)); // const uint16_t adresse, uint8_t *donnee,const uint8_t longueur
    _delay_ms(5);

    while (true)
    {

        memoire.lecture(ad<ress, &dataToReturn);
        if (dataToReturn != 0xFF)
        {
            transmissionUART(dataToReturn);
            adress++;
        }
        else
            break;
    }


    return 0;
}
