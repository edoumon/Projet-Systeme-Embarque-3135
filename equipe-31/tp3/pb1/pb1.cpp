/*Identification:
/
/    Noms des auteurs = Elena Doumon, Raphael Ramanitranja
/    Travail : Probleme 1,TP3  \\Section # : 2 \\Équipe # : 31
/    Description du programme : 3 appuis du bouton poussoir afin d'avoir la del verte allumee pour 2 secondes
/    Identifications matérielles (Broches I/O) 	: PINA0 PINA1 en sortie pour la del libre, PIND2 en entree pour le bouton poussoir
/                                                 Alors 0x03 pour DDRA en sortie et DDRD en entree
/
*/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

const uint8_t DEBOUNCE_DELAY = 10;
const uint8_t D2_MASK = (1 << PD2);

const uint8_t DEL_RED = (1 << PA0);
const uint8_t DEL_GREEN = (1 << PA1);
const uint8_t DEL_OFF = 0;

void setLedRed()
{
  PORTA = DEL_RED;
}

void setLedGreen()
{
  PORTA = DEL_GREEN;
}
void setLedOff()
{
  PORTA = DEL_OFF;
}

int main()
{
  DDRA = 0x03;
  DDRD = 0x00;

  while (true)
  {
  }
}
}