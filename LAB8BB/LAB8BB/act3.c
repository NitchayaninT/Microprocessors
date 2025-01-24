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
unsigned char current_position = 0;
int main() {
	DDRD = 0xFF; // Setting DDRD to output // setting for port D
	lcd_init();  // initialization of LCD function
	_delay_ms(30);

	lcd_gotoxy(1, 1);         // Go to the location 1,1 of lcd


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
	
	// Comparison and resultant action
	
	// Column one
	if(keyPressCode == 0b11101110){
		lcd_print("1");
	}
	if(keyPressCode == 0b11011110){
		lcd_print("4");
	}
	if(keyPressCode == 0b10111110){
		lcd_print("7");
	}
	if(keyPressCode == 0b01111110){
		lcd_print("E");
	}
	
	// Column two
	if(keyPressCode == 0b11101101){
		lcd_print("2");
	}
	if(keyPressCode == 0b11011101){
		lcd_print("5");
	}
	if(keyPressCode == 0b10111101){
		lcd_print("8");;
	}
	if(keyPressCode == 0b01111101){
		lcd_print("0");
	}
	
	// Column three
	if(keyPressCode == 0b11101011){
		lcd_print("3");
	}
	if(keyPressCode == 0b11011011){
		lcd_print("6");;
	}
	if(keyPressCode == 0b10111011){
		lcd_print("9");
	}
	if(keyPressCode == 0b01111011){
		lcd_print("F");
	}
	
	// Column four
	if(keyPressCode == 0b11100111){
		lcd_print("A");
	}
	if(keyPressCode == 0b11010111){
		lcd_print("B");
	}
	if(keyPressCode == 0b10110111){
		lcd_print("C");
	}
	if(keyPressCode == 0b01110111){
		lcd_print("D");
	}
	
}

// Function moving to a given position on the LCD screen
void lcd_gotoxy(unsigned char x, unsigned char y) {
	unsigned char firstCharAdr[] = {0x80, 0xC0, 0x94, 0xD4};
	lcdCommand(firstCharAdr[y - 1] + x - 1);
	_delay_ms(0.1);
}

void lcd_init(void) {
	lcdCommand(0x02); // To initialize LCD in 4-bit mode.
	_delay_ms(1);
	lcdCommand(0x28); // To initialize LCD in 2 lines, 5X7 dots and 4bit mode.
	_delay_ms(1);
	lcdCommand(0x01); // Clear LCD
	_delay_ms(1);
	lcdCommand(0x0E); // Turn on cursor ON
	_delay_ms(1);
	lcdCommand(0x80); // —8 go to first line and –0 is for 0th position
	_delay_ms(1);
	return;
}
//lcdCommand handles the 8-bit data by splitting it into two 4-bit chunks.while lcd_command sends the byte directly.
void lcdCommand(char cmd_value) {
	char cmd_value1;
	cmd_value1 = cmd_value & 0xF0;          // Mask lower nibble
	// because PD4-PD7 pins are used.
	lcd_command(cmd_value1);                // Send to LCD
	cmd_value1 = ((cmd_value << 4) & 0xF0); // Shift 4-bit and mask
	lcd_command(cmd_value1);                // Send to LCD
}

void lcdData(char data_value) {
	char data_value1;
	data_value1 = data_value & 0xF0;          // Mask lower nibble
	lcd_data(data_value1);                    // because PD4-PD7 pins are used.
	data_value1 = ((data_value << 4) & 0xF0); // Shift 4-bit and mask
	lcd_data(data_value1);                    // Send to LCD
}

//send commands to command register
void lcd_command(unsigned char cmd) {
	ctrl = cmd;
	ctrl &= ~(1 << rs); // RS = 0 for command
	ctrl &= ~(1 << rw); // RW = 0 for write
	ctrl |= (1 << en);  // EN = 1 for High to Low pulse
	_delay_ms(1);
	ctrl &= ~(1 << en); // EN = 0 for High to Low pulse
	_delay_ms(40);
	return;
}
//send data to lcd display
void lcd_data(unsigned char data) {
	ctrl = data;
	ctrl |= (1 << rs);  // RS = 1 for data
	ctrl &= ~(1 << rw); // RW = 0 for write
	ctrl |= (1 << en);  // EN = 1 for High to Low pulse
	_delay_ms(1);
	ctrl &= ~(1 << en); // EN = 0 for High to Low Pulse
	_delay_ms(40);
	return;
}

void lcd_print(
unsigned char *str) { // store address value of the string in pointer *str
	int i = 0;
	while (str[i] != '\0') {     // loop will go on till the NULL character in the string
		// Loop until the NULL character in the string
		if (current_position == LCD_MAX_COLS) {  // If we've reached the end of the first line
			lcd_gotoxy(1, 2);  // Move to the second line
			current_position = 0;  // Reset the position for the second line
		}
		lcdData(str[i]); // sending data on LCD byte by byte
		i++;
		current_position++;
	}
	return;
}