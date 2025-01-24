#define F_CPU 16000000UL
#define LCD_MAX_COLS 16

#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

#define keypadDirectionRegister DDRB
#define keypadPortControl PORTB
#define keypadPortValue PINB


#define ctrl PORTD // We are using port D
#define en 2       // enable signal pin 2
#define rw 1       // read/write signal pin 1
#define rs 0       // register select signal pin 0

void lcd_command(unsigned char cmd);
void lcd_init(void);
void lcd_data(unsigned char data);
void lcdCommand(char);
void lcdData(char);
void lcd_print(unsigned char *str);
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_update_time(void);
void keypadScan(void);

static const uint8_t digitCodeMap[];

int main() {
	DDRD = 0xFF; // Setting DDRD to output // setting for port D

	_delay_ms(30);

	// Keypad initialization
	keypadDirectionRegister = 0xF0;
	keypadPortControl = 0x0F;
	//upper nibble of port B is rows(output), lower is for columns(input)
	
	while (1) {
		keypadScan();
	};

	return 0;
}

void keypadScan(){
	
	// Store value for column
	uint8_t keyPressCodeC = keypadPortValue & 0x0F;
	
	keypadDirectionRegister ^= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
	keypadPortControl ^= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
	
	_delay_ms(5);
	
	// Store value for row
	uint8_t keyPressCodeR = keypadPortValue & 0xF0;
	
	// Add value for column and row
	uint8_t keyPressCode = keyPressCodeC | keyPressCodeR;
	
	uint8_t blinkDuration = 0;
	uint8_t value;
	// Comparison and resultant action
	
	// Column one
	if(keyPressCode == 0b11101110){
		value = digitCodeMap[1];
		ctrl = value;
	}
	if(keyPressCode == 0b11011110){
		value = digitCodeMap[4];
		ctrl = value;
	}
	if(keyPressCode == 0b10111110){
		value = digitCodeMap[7];
		ctrl = value;
	}
	if(keyPressCode == 0b01111110){
		value = digitCodeMap[14];
		ctrl = value;
	}
	
	// Column two
	if(keyPressCode == 0b11101101){
		value = digitCodeMap[2];
		ctrl = value;
	}
	if(keyPressCode == 0b11011101){
		value = digitCodeMap[5];
		ctrl = value;
	}
	if(keyPressCode == 0b10111101){
		value = digitCodeMap[8];
		ctrl = value;
	}
	if(keyPressCode == 0b01111101){
		value = digitCodeMap[0];
		ctrl = value;
	}
	
	// Column three
	if(keyPressCode == 0b11101011){
		value = digitCodeMap[3];
		ctrl = value;
	}
	if(keyPressCode == 0b11011011){
		value = digitCodeMap[6];
		ctrl = value;
	}
	if(keyPressCode == 0b10111011){
		value = digitCodeMap[9];
		ctrl = value;
	}
	if(keyPressCode == 0b01111011){
		value = digitCodeMap[15];
		ctrl = value;
	}
	
	// Column four
	if(keyPressCode == 0b11100111){
		value = digitCodeMap[10];
		ctrl = value;
	}
	if(keyPressCode == 0b11010111){
		value = digitCodeMap[11];
		ctrl = value;
	}
	if(keyPressCode == 0b10110111){
		value = digitCodeMap[12];
		ctrl = value;
	}
	if(keyPressCode == 0b01110111){
		value = digitCodeMap[13];
		ctrl = value;
	}
	
}


static const uint8_t digitCodeMap[] = {
	0b00111111, // 0 - "0" (ABCDEF)
	0b00000110, // 1 - "1" (BC)
	0b01011011, // 2 - "2" (ABDEG)
	0b01001111, // 3 - "3" (ABCDG)
	0b01100110, // 4 - "4" (BCFG)
	0b01101101, // 5 - "5" (ACDFG)
	0b01111101, // 6 - "6" (ACDEF)
	0b00000111, // 7 - "7" (AB)
	0b01111111, // 8 - "8" (ABCDEFG)
	0b01101111, // 9 - "9" (ABCDG)
	0b01110111, // A - "A" (ABCEFG)
	0b01111100, // B - "B" (CDEFG)
	0b00111001, // C - "C" (ADE)
	0b01011110, // D - "D" (BCDEG)
	0b01111001, // E - "E" (ADFG)
	0b01110001, // F - "F" (AFG)
};