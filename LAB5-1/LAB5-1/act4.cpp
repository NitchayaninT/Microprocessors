#define F_CPU 20000000
#include <avr/io.h>
#include <util/delay.h>


int main() {
	DDRB = 0xFF; 
	DDRD = 0x00; 
	int toggle = 0;  
	int count = 0;   

	while (1) {
		if (PIND == 0x01) {  // 0 1 state
			_delay_ms(10);         // Debounce
			if (PIND == 0x01) { 
				toggle = !toggle; 
			}
			while (PIND == 0x01); // Wait for release
			
			if (toggle) {
				while(1){
					// Run LED animation
					if (count == 8) count = 0;
					PORTB = (1 << count); 
					_delay_ms(100);    
					PORTB = 0x00;
					_delay_ms(100);       
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
					PORTB = (1<<count);
					if(PIND == 0x01)
					{
						//_delay_ms(50);
						break;
					}
				}
				
			}
		}
		
		
	}
}
