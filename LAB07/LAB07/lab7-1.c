#include <avr/interrupt.h>
#include <avr/io.h>

//Write a program to toggle pin PD5 every 1 seconds (clock frequency = 16 MHz)
// by using TIMER1 interrupt and displays output to LED

int main(void)
{
   DDRD |= (1<<DDD5);
   OCR1A = 15625;
   //set mode
   TCCR1A = 0;
   //set prescaler 1024
   TCCR1B = (1<<CS12)|(1<<CS10)|(1<<WGM12);
   TIMSK1 = (1<<OCIE1A);
   sei(); //enable global interrupt
   
    while (1) 
    {
		//do nothing
    }
}
ISR(TIMER1_COMPA_vect){
	PORTD ^= (1<<5);
}
