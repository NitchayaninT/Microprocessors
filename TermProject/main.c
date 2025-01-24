#define F_CPU 16000000UL
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "keypad.h"
#include "LCD.h"
#include <avr/io.h>

static char rightPassword[4] = {'2','0','0','3'};
char currentPassword[4];
volatile uint8_t count;  // Variable to store the countdown value

// Function prototypes
void getIntArray(char[], int);  // Convert char array to int array
void getCharArray(int[],int ); // Convert int array to char array
int getShiftRight(char[], int);  
void shiftRight(char[], int);    // Shift array to the right
void countDown(int);
char hex_to_ASCII(int );
int ASCII_to_int(char);


// Initialize Timer1
void delay() {
	
	TCCR0A = 0;  // Normal mode
	TCCR0B = (1 << CS00);  // No prescaling (use full clock speed)
 
	while (!(TIFR0 & (1 << TOV0))) {}
	TIFR0 |= (1 << TOV0);
	
}
ISR(TIMER0_OVF_vect) {
	if (count > 0) {
		
		count--;  // Decrement the countdown value
	}

	if (count == 0) {
		TCCR0B = 0;  
	}
}

int main() {
	DDRC &= ~(1 << DDC0);
	keypad_init();
	lcd_init();
	button_init();
	_delay_ms(30);

	lcd_gotoxy(1, 1);
	char c;

	while (1) {
		int pressCount = 0;
		char counter = 0;
		lcd_clear();
		lcd_print("Enter Password:");
		lcd_gotoxy(1, 2);

		// Password input loop
		while (pressCount < 4) {
			c = keypad_check();
			if (c != 0xFF) {
				lcdData('*');
				currentPassword[pressCount] = c;
				pressCount++;
			}
		}

		// Compare entered password with correct one
		int correct = 0;
		for (int i = 0; i < 4; i++) {
			if (currentPassword[i] == rightPassword[i]) {
				correct++;
			}
		}

		// If password is correct, process further
		int no_of_digits = 4;
		char counterArr[4] = {'0','0','0','0'}; // Maximum size 4
		lcd_clear();
		if (correct == 4) {
			lcd_print("Access Granted");
			_delay_ms(1000);
			lcd_clear();
			lcd_print("Insert Timer : ");
			lcd_gotoxy(1, 2);
			pressCount = 0;

				while (1) {
					counter = keypad_check();
					if (counter == '0') {
						_delay_ms(15);
						lcd_clear();
						if (pressCount == 5) {  // Ensure we don't go beyond 4 digits
							lcd_print("Digits exceed 4");
							_delay_ms(1500);
							lcd_clear();
							memset(counterArr, 0, sizeof(counterArr));
							pressCount = -1;
							lcd_print("Insert Timer : ");
							lcd_gotoxy(1, 2);
							continue;
						}
						lcd_print("Button Pressed = ");
						lcd_gotoxy(1, 2);

						int shifts = getShiftRight(counterArr, 4); // Get number of shifts
						shiftRight(counterArr, shifts); // Shift the array
					
						// Print the shifted array. Eg. 123 -> 0123
						lcd_print(counterArr);
						_delay_ms(1000);
						break;
						} 
						else {
						lcdData(counter);
						if (pressCount < 4) {
							counterArr[pressCount] = counter;
							pressCount++;
						}
					}
					//continue doing countdown, but we have to convert from char array to hex
					for(int i=0;i<4;i++)
					{
						int hex = ASCII_to_int(counterArr[i]); //got hex
						hex +=hex;
					}
					
					//countDown(hex);

				}
			} 
			else {
			lcd_print("Access Denied");
			_delay_ms(1000);
			continue;
		}

		_delay_ms(200);
	}

	return 0;
}


void getIntArray(char arr[], int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = arr[i] - '0';  // Convert char to int
	}
}
void getCharArray(int arr[],int size){
	for (int i = 0; i < size; i++) {
		arr[i] = arr[i] + '0';  // Convert int to char
	}
}
int getShiftRight(char arr[], int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i] == '0') {
			count++;
		}
	}
	return count;
}


void shiftRight(char arr[], int shifts) {
	
	for (int i = 3; i >= shifts; i--) {
		arr[i] = arr[i - shifts];  
	}
	for (int i = 0; i < shifts; i++) {
		arr[i] = '0';
	}
}

void countDown(int hex)
{
	count = hex;
	delay();
}
    
char hex_to_ASCII(int hex) {
	char ascii;
	if (hex < 0 || hex > 15)
	return '\0';
	if (hex >= 0 && hex <= 9)
	ascii = '0' + hex;
	else
	ascii = 'A' + (hex - 10);
	return ascii;
}


int ASCII_to_int(char ascii) //char to hex
{
	int i = -1;
	if (ascii >= '0' && ascii <= '9')
	i = ascii-'0';
	else if (ascii >= 'A' && ascii <= 'F')
	i = ascii-'A'+10;
	return i;
}