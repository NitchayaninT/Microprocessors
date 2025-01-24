#ifndef KEYPAD_H
#define KEYPAD_H

#include <avr/io.h>
#ifndef F_CPU 
#define F_CPU 16000000UL
#endif
#include <util/delay.h>

#define KEY_PORT PORTB
#define KEY_PIN PINB
#define KEY_DDR DDRB
#define button_DDR DDRC
#define button PINC

char get_key(void);

uint8_t read_key;

void keypad_init()
{
	KEY_DDR |= 0xF0;//pin0-3 INPUT pin4-7 OUTPUT
	KEY_PORT |= 0x0F; // Enable pull-up resistors for pins 0-3
}	
void button_init()
{
	button_DDR = 0x00;
}
char keypad_check()
{
	char press;
	//ground all row
	KEY_PORT &= 0x0F;	
	// wait_for_release. 
	// wait until 0x0F, which means all bits are high (indicating no keys are pressed).
	do{read_key = KEY_PIN & (0x0F);}while(read_key != 0x0F);
	
	//wait for key press
	// wait_for_key (2 times to check if key really is pressed)
	do{read_key = KEY_PIN & (0x0F);
		//if button is pressed, return NULL so that we know in main.c that we have pressed the button
		if (button & (1 << PINC0)) {
			_delay_ms(15);
			return '0';
		}
	}while(read_key == 0x0F); //1
	_delay_ms(15);
	do{read_key = KEY_PIN & (0x0F);}while(read_key == 0x0F); //2
	

	press = get_key();
	return press;
}

char get_key()
{
	char c = 'x';
	KEY_PORT  = 0b01111111; // ground row0
	_delay_us(10);
	read_key = KEY_PIN & (0x0F);
	if(read_key != 0x0F)
	{
		if (!(read_key & (1<<0))) c = '1';
		else if (!(read_key & (1 << 1))) c = '2';
		else if (!(read_key & (1 << 2))) c = '3';
		else if (!(read_key & (1 << 3))) c = 'A';
		return c;
	}
	KEY_PORT  = 0b10111111; // ground row1
	_delay_us(10);
	read_key = KEY_PIN & (0x0F);
	if(read_key != 0x0F)
	{
		if (!(read_key & (1 << 0))) c = '4';
		else if (!(read_key & (1 << 1))) c = '5';
		else if (!(read_key & (1 << 2))) c = '6';
		else if (!(read_key & (1 << 3))) c = 'B';
		return c;
	}
	KEY_PORT  = 0b11011111; // ground row2
	_delay_us(10);
	read_key = KEY_PIN & (0x0F);
	if(read_key != 0x0F)
	{
		if (!(read_key & (1 << 0))) c = '7';
		else if (!(read_key & (1 << 1))) c = '8';
		else if (!(read_key & (1 << 2))) c = '9';
		else if (!(read_key & (1 << 3))) c = 'C';
		return c;
	}
	KEY_PORT  = 0b11101111; // ground row3
	_delay_us(10);
	read_key = KEY_PIN & (0x0F);
	if(read_key != 0x0F)
	{
		if (!(read_key & (1 << 0))) c = 'E';
		else if (!(read_key & (1 << 1))) c = '0';
		else if (!(read_key & (1 << 2))) c = 'F';
		else if (!(read_key & (1 << 3))) c = 'D';
		return c;
	}
	return c;
}


#endif