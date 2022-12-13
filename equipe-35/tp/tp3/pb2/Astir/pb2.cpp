#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


//When we give a fréquence we are giving a periode (b) (temps complet pour faire un on et un off). a = temps que le cycle est on. Ex: Fréquence = 1000 so période =1/1000 
// 0.001 s = 1 ms
// 50% cycle = 50 us on and 50 us off.
// b - a = le temps c'est à off
//duty cycle (temps de travail) = a/b * 100

// le plus qu'on augmente la fréquence, plus le mouvement est fluide (moteur ou DEL ou toute autre composante)
/*
ex :  4HZ a 50%. donce période de 250 ms  donc a = 62.5 ms et c = b = a = 187.5 cm
donc code sera :
PORTA = HIGH;
delay_ms(a = 62.5);
PORTA = LOW;
delay_ms(c = 187.5);
*/

const uint8_t OFF = ~(1 << PD4) & ~(1 << PD5);
const uint8_t ON = (1 << PD4) | (1 << PD5);
const uint8_t DIRECTION = ~(1 << PD6) | ~(1 << PD7); 

inline void delayMs(int tempsattente) {
    for (int i = 0; i < (tempsattente); i++) {
        _delay_us(1000); 
    }
}

inline void delayUs(int tempsattente) {
    for (int i = 0; i < (tempsattente)/35; i++) {
        _delay_us(35); 
    }
}

void PWM(float frequency, int Percentage) {

    float period = ((1/frequency) * 1000);
    int totalTime = (2000/period); // how many ms we have to repeat the cycle to get 2s for each (2000 is for 2 seconds)
    float timeOnHigh = ((period * Percentage)/100);
    float timeOnLow = period - timeOnHigh;
    PORTC = timeOnHigh;
    PORTD = timeOnLow;
    while (totalTime != 0)
    {
        if (frequency < 100) 
        {
            PORTD = ON;
            delayMs(timeOnHigh);
            PORTD = OFF;
            delayMs(timeOnLow);
        }

        if(frequency > 100) 
        {
            PORTD = ON;
            delayUs(1000*timeOnHigh);
            PORTD = OFF;
            delayUs(1000*timeOnLow);

        }

        totalTime--;

    }
    

}

int main() {

    DDRD = (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 <<  DDD7);

    PWM(60, 0);
    PWM(60, 25);
    PWM(60, 50);
    PWM(60, 75);
    PWM(60, 100);

    _delay_ms(1000);

    PWM(400, 0);

    PWM(400, 25);

    PWM(400,50);

    PWM(400,75);

    PWM(400, 100);

    PORTD = 0x00;

    return 0;
    
}