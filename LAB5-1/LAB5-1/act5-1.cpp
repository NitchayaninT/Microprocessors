
//act5
#define F_CPU 20000000 // AVR clock frequency in Hz, used by util/delay.h
#define LED_PIN 1
#include <avr/io.h>
#include <util/delay.h>

void set_direction(){
	uint8_t dir = DDRD;
	asm volatile(
	"ldi r16, 0b00000010 \n\t" 
	"out %0, r16 \n\t"           
	:                            
	: "I" (dir)   
	: "r16"                    
	);
}

void toggle(){
	uint8_t port = PORTD;
	asm volatile(
	"in r16, %[port]\n\t"  
	"eor r16, %[mask]\n\t" 
	"out %[port], r16\n\t"  
	:                       
	: [port] "I" (port), 
	[mask] "r" (1 << LED_PIN)       
	: "r16"                            
	);
}

int main() {
	set_direction();  // Set PORTD1 as output
	while (1) {
		toggle();       // Toggle the LED
		_delay_ms(500); // Wait for 500ms
	}
}