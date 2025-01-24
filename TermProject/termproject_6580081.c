#define F_CPU 16000000UL
#define LCD_MAX_COLS 16
#include "keypad.h"
#include "LCD.h"
//PINB for keyboard
//PORTC for seven seg
//PORTD for LCD
#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

static char rightPassword[4] = {'2','0','0','3'};
char currentPassword[4];

static const uint8_t digitCodeMap[];


int main() {
	keypad_init();  
	lcd_init();   
	_delay_ms(30);
	
	lcd_gotoxy(1, 1);  
	char c;
	
	while (1) {
		int pressCount = 0;
		char counter = 0;
		lcd_clear();
		lcd_print("Enter Password:");
		lcd_gotoxy(1,2);
		while (pressCount < 4) {
			c = keypad_check();  
			if (c != 0xFF) {     
				lcdData('*');     
				currentPassword[pressCount] = c; 
				pressCount++;
			}
		}

		// After 4 digits, compare the entered password with the correct one
		int correct = 0;
		for (int i = 0; i < 4; i++) 
		{
			if (currentPassword[i] == rightPassword[i]) 
			{
				correct++;
			}
		}

		// Check if the password is correct
		lcd_clear();  
		if (correct == 4) 
		{
			lcd_print("Access Granted");
			_delay_ms(1000);
			lcd_clear();
			lcd_print("Insert Timer : ");
			counter = keypad_check();
			lcd_clear();
			lcdData(counter);
		} 
		else 
		{
			lcd_print("Access Denied");
			_delay_ms(1000);
			continue;
		}

		_delay_ms(200);
	}

	return 0;
}


