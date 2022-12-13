/* 
 Authors: Astir Tadrous and Motassembellah Mohamed Bassiouni 
 Due date: 17 October 2022
 Group: 02
 Description of the program:

    When the button on breadboard is pressed an interruption occurs and a timer of 12 seconds starts. 
    If the button is released or the 12 seconds pass, DEL is flashing in green for 1/2 seconds.
    Then, DEL is off for 2 seconds.
    After this time, DEL starts flashing in red 2 times per second while repeating so for (counter/2) times.
    Finall, DEL turns green for 1 second and then it returns to its initial state while DEL light is off.

 Material used:
    - Breadboard
    - Bicolor DEL: cathode (+) => PB0, anode (-) => PB1
    - Wire of breadboard connected to PD2
    - Wire of breadboard connected to Vcc and Ground of PORTD
    - Resistor of 100K on breadboard
    - Condenser of 0.1 µF on breadboard
*/

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t BUTTON_UNTOUCHED = 0;
const uint8_t BUTTON_PRESSED = 1;
const uint8_t BUTTON_RELEASED = 2;

volatile uint8_t gCounter = 0;
volatile uint8_t gButtonState = BUTTON_UNTOUCHED;
volatile bool gExpiredTimer = false;
volatile bool gTimerOn = false;

const uint8_t DEL_GREEN = (1 << PB1);
const uint8_t DEL_RED = (1 << PB0);
const uint8_t DEL_OFF = ~(1 << PB1) & ~(1 << PB0);


const uint16_t DELAY_UNACTIVE_MOTHERBOARD_MS = 2000;
const uint16_t DEL_GREEN_DELAY = 1000;
const uint8_t DEL_ON_FLASH_GREEN_DELAY = 50;
const uint8_t DEL_OFF_FLASH_GREEN_DELAY = 30;
const uint8_t DEL_RED_FLASH_DELAY = 250; // 250 ms = (1/4) of one second ON and OFF -> Conclusion = DEL blinks 2 times per second 


uint16_t convertTimetoNoCycles(uint32_t timeUs)
{
    const uint16_t PRESCALER = 1024;
    const uint32_t FREQUENCY_HZ = 8000000;
    uint32_t timeToStop = timeUs;
    const uint16_t FREQUENCY_HZ_SLOWED = FREQUENCY_HZ / PRESCALER;
    const uint32_t PERIOD_US = uint32_t(1000000) / FREQUENCY_HZ_SLOWED;
    uint16_t noCycles = timeToStop / PERIOD_US;

    return noCycles;
}

void reinitializeGlobalVariables()
{
    gCounter = 0;
    gExpiredTimer = false;
    gButtonState = BUTTON_UNTOUCHED;
}

void turnOffLight()
{
    PORTB = DEL_OFF;
}

void turnGreenLight()
{
    PORTB = DEL_GREEN;
}

void turnRedLight()
{
    PORTB = DEL_RED;
}


void initializeInputOutput()
{
    const uint8_t B0B1_OUTMODE = (1 << PB0) | (1 << PB1);
    DDRB |= B0B1_OUTMODE;
    const uint8_t D2_INMODE = ~(1 << DDD2);
    DDRD &= D2_INMODE;
}

void initializeInterrupt()
{
    cli();
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}

void startTimer(uint16_t noCycles)
{
    TCNT1 = 0;
    OCR1A = noCycles; 
    TCCR1A = 0; 
    TCCR1B = (1 << CS12) | (1 << CS10); 
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A);
    gTimerOn = true;
}

void VerifyTimerIsOff(uint16_t noCycles)
{
    if(!gTimerOn) 
    {
        startTimer(noCycles);
    }  
}

void flashGreen(uint16_t noCycles)
{
    gExpiredTimer = false;
    startTimer(noCycles);
    while (gExpiredTimer == false)
    {
        turnGreenLight();
        _delay_ms(DEL_ON_FLASH_GREEN_DELAY);
        turnOffLight();
        _delay_ms(DEL_OFF_FLASH_GREEN_DELAY);
    }
}

void flashRed()
{
    for (int numberFlashing = 1; numberFlashing <= (gCounter / 2); numberFlashing++) 
    {
        turnRedLight();
        _delay_ms(DEL_RED_FLASH_DELAY);
        turnOffLight();
        _delay_ms(DEL_RED_FLASH_DELAY);
    }
}


bool debounce()
{
    bool FIRST_LECTURE = PIND & (1 << PIND2); 
    _delay_ms(30);
    bool SECOND_LECTURE = PIND & (1 << PIND2);

    return FIRST_LECTURE == SECOND_LECTURE;
}

ISR(INT0_vect)
{
    if (debounce())
    {
        gButtonState++;
    }  
}

ISR(TIMER1_COMPA_vect)
{
    gExpiredTimer = true;
    gTimerOn = false; 
}

void freezeCodeUntilButtonClicked() 
{
    while (gButtonState == BUTTON_UNTOUCHED);
}

void incrementCounterWhenClick()
{
    while (gButtonState == BUTTON_PRESSED && gCounter < 120)
    {
        if (!gTimerOn)
        {
            VerifyTimerIsOff(convertTimetoNoCycles(1000000));
            gCounter += 10;
        }
    }
}

void displayAndChangeDelColors()
{
    if (gButtonState == BUTTON_RELEASED || gCounter == 120)
    {
        flashGreen(convertTimetoNoCycles(500000));
        _delay_ms(DELAY_UNACTIVE_MOTHERBOARD_MS);
        flashRed();

        turnGreenLight();
        _delay_ms(DEL_GREEN_DELAY);
        turnOffLight();
    }
}

void waitTillButtonisReleased()
{
    while (gButtonState == BUTTON_PRESSED);
}

int main()
{
    initializeInputOutput();
    initializeInterrupt();
     
    while (true)
    {
        reinitializeGlobalVariables();
        freezeCodeUntilButtonClicked();
        incrementCounterWhenClick();
        displayAndChangeDelColors();
        waitTillButtonisReleased();
    }
    return 0;
}

