#define F_CPU 20000000
#include <avr/io.h>
#include <util/delay.h>
void set_direction(){
	//uint8_t dir = DDRB;
	asm volatile(
	"ldi r16, 0xFF \n\t"  
	"out %0, r16 \n\t"    
	:         
	: "I" (_SFR_IO_ADDR(DDRB))  
	: "r16"                      
	);
}

void toggle(uint8_t count){
	uint8_t mask = (1<<(count));
	asm volatile(
	"in r16, %[port]\n\t"  
	"eor r16, %[mask]\n\t"  
	"out %[port], r16\n\t"  
	:                       
	: [port] "I" (_SFR_IO_ADDR(PORTB)), 
	[mask] "r" (mask)     
	: "r16"                             
	);
}
int main() {
	set_direction();
	int count =0;
	while (1) {
		if(count == 8) count = 0;
		toggle(count); //ON
		_delay_ms(100);
		 toggle(count); //OFF
		_delay_ms(400); 
		count++;
	}
}
