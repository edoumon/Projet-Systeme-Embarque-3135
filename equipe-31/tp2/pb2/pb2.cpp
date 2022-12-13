/*Identification:
/
/    Noms des auteurs = Elena Doumon, Raphael Ramanitranja
/    Travail : Probleme 2,TP2  \\Section # : 2 \\Équipe # : 31
/    Description du programme : Changement de couleur de la DEL en appuyant ou en relachant le bouton
/    Identifications matérielles (Broches I/O) 	: PINA0 PINA1 en sortie pour la del libre, PIND2 en entree pour le bouton poussoir
/                                                 Alors 0x03 pour DDRA en sortie et DDRD en entree
/
/  +--------------+----+--------------+--------+
/  | Etat Present | D2 | Etat Suivant | Sortie |
/  +--------------+----+--------------+--------+
/  | INIT         |  1 | HOLD1        |  RED   |
/  | -            |  0 | INIT         |        |
/  | HOLD1        |  1 | HOLD1        | AMBER  |
/  | -            |  0 | RELEASE1     |        |
/  | RELEASE1     |  1 | HOLD2        | GREEN  |
/  | -            |  0 | RELEASE1     |        |
/  | HOLD2        |  1 | HOLD2        | RED    |
/  | -            |  0 | RELEASE2     |        |
/  | RELEASE2     |  1 | HOLD3        | OFF    |
/  | -            |  0 | RELEASE2     |        |   
/  | HOLD3        |  1 | HOLD3        | GREEN  |
/  | -            |  0 | INIT         |        |   
   +--------------+----+--------------+--------+
/
/
/
*/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>


const uint8_t DEBOUNCE_DELAY = 10;
const uint8_t D2_MASK = (1 << PD2);

const uint8_t AMBER_TOGGLE_DELAY = 1;
const uint8_t DEL_RED = (1 << PA0);
const uint8_t DEL_GREEN = (1 << PA1);
const uint8_t DEL_OFF = 0;

bool buttonPressed()
{
  if (PIND & D2_MASK)
  {
    _delay_ms(DEBOUNCE_DELAY);
    if (PIND & D2_MASK)
    {
      return true;
    }
  }
  return false;
}

void setLedRed()
{
  PORTA = DEL_RED;
}

void setLedGreen()
{
  PORTA = DEL_GREEN;
}

void setLedAmber()
{
  setLedRed();
  _delay_ms(AMBER_TOGGLE_DELAY);
  setLedGreen();
  _delay_ms(AMBER_TOGGLE_DELAY);
}

void setLedOff()
{
  PORTA = DEL_OFF;
}

enum class State
{
  INIT,
  HOLD1,
  RELEASE1,
  HOLD2,
  RELEASE2,
  HOLD3
};


void initializeRegisters()
{
  DDRA = 0x03;
  DDRD = 0x00;
}

State nextState(State state) 
{
     switch (state)
    {
    case State::INIT:
      setLedRed();
      if (buttonPressed())
      {
        state = State::HOLD1;
      }
      break;

    case State::HOLD1:
      while (buttonPressed())
      {
        setLedAmber();
      };
      state = State::RELEASE1;
      break;

    case State::RELEASE1:
      setLedGreen();
      if (buttonPressed())
      {
        state = State::HOLD2;
      }
      break;

    case State::HOLD2:
      while (buttonPressed())
      {
        setLedRed();
      };
      state = State::RELEASE2;
      break;

    case State::RELEASE2:
      setLedOff();
      if (buttonPressed())
      {
        state = State::HOLD3;
      }
      break;

    case State::HOLD3:
      while (buttonPressed())
      {
        setLedGreen();
      };
      state = State::INIT;
    }
}

int main()
{
  initializeRegisters();

  State state = State::INIT;
  while (true)
  {
    state = nextState(state);
  }
}