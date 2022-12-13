/*
 * Nom:TP4 pb1
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
*/

 #include <avr/io.h> 
 #define F_CPU 8000000
 #include <util/delay.h>
 #include <avr/interrupt.h>
 #include "memoire_24.h"
 
 const uint8_t A0A1_OUTMODE = (1 << DDA1) | (1 << DDA0);
 enum COULEUR
{
    RED = (1 << PA1),
    GREEN = (1 << PA0),
    OFF = ~(1 << PA0) & ~(1 << PA1)
};


int main() {
    Memoire24CXXX memoire;
    DDRA = A0A1_OUTMODE;
    uint8_t writeSentence[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";  //uint8_t n'est pas une déclaration de int, mais plus une déclaration d'un unsigned de 8 bits du type que je lui donnera
    uint8_t readSentence[] =  "000000000000000000000000000000000000000000000";
    bool isTheSame = true;
    uint8_t length = 46;

    memoire.ecriture(0x0000, writeSentence, length);         //const uint16_t adresse, uint8_t *donnee,const uint8_t longueur
    _delay_ms(5);
    memoire.lecture(0x0000, readSentence, length);
    _delay_ms(5);

    for(int i = 0; i < length; i++) {
        if (writeSentence[i] != readSentence[i])
        {
            isTheSame = false;
        }
        
    }

    if(isTheSame)
        PORTA = GREEN;
    else
        PORTA = RED;

    return 0;
}
