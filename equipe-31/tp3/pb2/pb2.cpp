/*Identification:
/
/    Noms des auteurs = Elena Doumon, Raphael Ramanitranja
/    Travail : Probleme 2,TP3  \\Section # : 2 \\Équipe # : 31
/    Description du programme : Changement de couleur de la DEL en appuyant ou en relachant le bouton
/    Identifications matérielles (Broches I/O) 	: PINA0 PINA1 en sortie pour la del libre, PIND2 en entree pour le bouton poussoir
/                                                 PINB0 PINB1 PINB2 et PINB3 pour le controle des roues
/                                                 Alors 0x03 pour DDRA en sortie, 0x08 pour DDRB en sortie DDRD en entree
/
/
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
  DDRB = 0x08;
  DDRD = 0x00;

  while (true)
  {
  }
}
}