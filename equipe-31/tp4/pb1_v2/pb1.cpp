#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

enum class State
{
  INIT,
  HOLD1,
  RELEASE1,
  HOLD2,
  RELEASE2,
  HOLD3
};

const uint8_t AMBER_TOGGLE_DELAY = 1;
const uint8_t DEBOUNCE_DELAY = 10;
const uint8_t D2_MASK = (1 << PD2);

const uint8_t DEL_RED = (1 << PA0);
const uint8_t DEL_GREEN = (1 << PA1);
const uint8_t DEL_OFF = 0;
volatile State gEtat = State::INIT;
volatile State prochainEtat;

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

void initialisation(void)
{
  cli();
  DDRA = 0x03;
  DDRD = 0x00;

  EIMSK |= (1 << INT0);
  EICRA |= (1 << ISC00);
  sei();
}

// placer le bon type de signal d'interruption

// à prendre en charge en argument

ISR ( INT0_vect ) {
_delay_ms ( 30 );

// se souvenir ici si le bouton est pressé ou relâché

gEtat = prochainEtat;

// changements d'état tels que ceux de la

// semaine précédente


EIFR |= (1 << INTF0) ;

}

int main()
{
  initialisation();


  while (true)
  {

    switch (gEtat)
    {

      case State::INIT:
      {
        prochainEtat = State::HOLD1;
        setLedRed();
      }
      break;

      case State::HOLD1:
      {
        prochainEtat = State::RELEASE1;
        setLedAmber();
      }
      break;

      case State::RELEASE1:
      {
        prochainEtat = State::HOLD2;
        setLedGreen();
      }
      break;

      case State::HOLD2:
      {
        prochainEtat = State::RELEASE2;
        setLedRed();
      }
      break;

      case State::RELEASE2:
      {
        prochainEtat = State::HOLD3;
        setLedOff();
      }
      break;

      case State::HOLD3:
      {
        prochainEtat = State::INIT;
        setLedGreen();
      }
      break;
    }
  }
}