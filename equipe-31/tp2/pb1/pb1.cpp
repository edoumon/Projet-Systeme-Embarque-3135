/*Identification:
/
/    Noms des auteurs = Elena Doumon, Raphael Ramanitranja
/    Travail : Probleme 1,TP2  \\Section # : 2 \\Équipe # : 31
/    Description du programme : 3 appuis du bouton poussoir afin d'avoir la del verte allumee pour 2 secondes
/    Identifications matérielles (Broches I/O) 	: PINA0 PINA1 en sortie pour la del libre, PIND2 en entree pour le bouton poussoir
/                                                 Alors 0x03 pour DDRA en sortie et DDRD en entree
/  +--------------+----+--------------+--------+
/  | Etat Present | D2 | Etat Suivant | Sortie |
/  +--------------+----+--------------+--------+
/  | INIT         |  1 | PRESS1       | OFF    |
/  | -            |  0 | INIT         |        |
/  | PRESS1       |  1 | PRESS2       | OFF    |
/  | -            |  0 | PRESS1       |        |
/  | PRESS2       |  1 | PRESS3       | OFF    |
/  | -            |  0 | PRESS2       |        |
/  | PRESS3       |  1 | APPUI3       | GREEN  |
/  | -            |  0 | INIT         |        |
/  +--------------+----+--------------+--------+
/
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

const uint8_t DEL_GREEN = (1 << PA1);
const uint8_t DEL_OFF = 0;

const uint16_t COLOR_HOLD_DELAY = 2000; // 2 secondes pour le vert
const uint8_t DEBOUNCE_DELAY = 10;
const uint8_t D2_MASK = (1 << PD2);

bool buttonPressed()
{
  if (PIND & D2_MASK)
  {
    _delay_ms(DEBOUNCE_DELAY);
    return (PIND & D2_MASK);
  }
  return false;
}

void setLedGreen()
{
  PORTA = DEL_GREEN;
}

void setLedOff()
{
  PORTA = DEL_OFF;
}

enum class State
{
  INIT,
  PRESS1,
  PRESS2,
  PRESS3
};

int main()
{
  DDRA = 0x03;
  DDRD = 0x00;

  State state = State::INIT;
  while (true)
  {
    switch (state)
    {
    case State::INIT:
      setLedOff();
      if (buttonPressed())
      {
        while (buttonPressed()); // tant que le bouton n'est pas relache on avance pas
        state = State::PRESS1;
      }
      break;
    case State::PRESS1:

      if (buttonPressed())
      {
        while (buttonPressed());
        state = State::PRESS2;
      }
      break;
    case State::PRESS2:
      if (buttonPressed())
      {
        while (buttonPressed());
        state = State::PRESS3;
      }
      break;
    case State::PRESS3:

      setLedGreen();
      _delay_ms(COLOR_HOLD_DELAY);
      state = State::INIT;

      break;
    }
  }
}
