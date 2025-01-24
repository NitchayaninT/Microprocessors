#include <avr/interrupt.h>
#include <avr/io.h>

//A switch is connected to an External interrupt 1 (PD.3). 
//Any time a L-to-H pulse comes in, after 3 seconds, a single LED (connected with PD.6)  is turned on.
// Any time a H-to-L pulse comes in, after 3 seconds, the same LED is turned off. 


volatile uint8_t led = 0; // 0: LED OFF, 1: LED ON

void timer() {                        
	TCCR1A = 0;                               
	TCCR1B = (1 << CS12) | (1 << CS10) | (1 << WGM12);
	OCR1A = 46874;               
}

int main(void) {
	DDRD &= ~(1 << DDD3);                     
	DDRD |= (1 << DDD6);   
	EIMSK |= (1 << INT1);                   
	EICRA |= (1 << ISC10) | (1 << ISC11); //detect rising edge. Initial LED turn off
	
	timer();//set timer 3 sec       
	sei();                                   

	while (1) {
		// do nothing
	}
}

//detect interrupt
ISR(INT1_vect) { //start counting when theres interrupt
	if(led == 0)
	{
		EICRA |= (1 << ISC10) | (1 << ISC11);//led still off -> detect rising edge
	}
	else
	{
		EICRA |= (1 << ISC11); //led ON -> detect falling edge
	}
	TCNT1 = 0;
	TIMSK1 |= (1<<OCIE1A); //turn on timer interrupt 
}

ISR(TIMER1_COMPA_vect) { //once interrupt happens, what should we do?  
	//wait for 3 seconds then turn on/off the LED  
	if (led == 0) 
	{
		PORTD |= (1 << PORTD6); 
		led = 1;
	} 
	else 
	{
		EICRA |= (1 << ISC11);
		PORTD &= ~(1 << PORTD6); 
		led = 0;
	}
	TIMSK1 &= ~(1<<OCIE1A); //write 1 to clear timer interrupt flag
}

