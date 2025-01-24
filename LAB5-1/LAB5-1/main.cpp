#define F_CPU 20000000
#include <avr/io.h>
#include <util/delay.h>

void set_direction(){
	//uint8_t dir = DDRB;
	asm volatile(
	"ldi r16, 0xFF \n\t"
	"out %0, r16 \n\t"
	"ldi r17, 0x00 \n\t"
	"out %1, r17 \n\t"
	:
	: "I" (_SFR_IO_ADDR(DDRB)), "I" (_SFR_IO_ADDR(DDRD))
	: "r16", "r17"
	);
}
void toggling(uint8_t count){
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
	int count = 0;
	int toggle = 0;

	if (PIND == 0x01) {  // 0 1 state
		_delay_ms(10);         // Debounce
		if (PIND == 0x01) {
			toggle = !toggle;
		}
		while (PIND == 0x01); // Wait for release
		
		if (toggle) {
			while(1){
				// Run LED animation
				if(count == 8) count = 0;
				toggling(count);
				_delay_ms(100);
				toggling(count); //OFF
				_delay_ms(400);
				count++;
				if(PIND == 0x01)
				{
					//_delay_ms(50);
					break;
				}
			}
			} else {
			while(1)
			{
				// Freeze LEDs
				toggling(count);
				if(PIND == 0x01)
				{
					//_delay_ms(50);
					break;
				}
			}
			
		}
	}
	
}
