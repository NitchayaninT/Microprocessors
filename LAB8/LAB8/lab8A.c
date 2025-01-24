/*
 * Program12_5.c
 *  Author: Sepehr Naimi
 */
 
#include <avr/io.h>	//standard AVR header
 
#define F_CPU 16000000UL   // THE CPU FREQUENCY
#include <util/delay.h>       	//delay header
 
#define   	LCD_DPRT  PORTD  	//LCD DATA PORT  	
#define   	LCD_DDDR  DDRD         	//LCD DATA DDR
#define   	LCD_DPIN  PIND         	//LCD DATA PIN
#define   	LCD_CPRT  PORTB  	//LCD COMMANDS PORT
#define   	LCD_CDDR  DDRB         	//LCD COMMANDS DDR
#define   	LCD_CPIN  PINB         	//LCD COMMANDS PIN
#define   	LCD_RS  0              	//LCD RS
#define   	LCD_EN  1              	//LCD EN
 
void lcd_putValue(unsigned char val){
   	LCD_DPRT &= 0x0F;
   	LCD_DPRT |= (val&0xF0);       	//send cmnd to data port
   	LCD_CPRT |= (1<<LCD_EN);      	//EN = 1 for H-to-L pulse
   	_delay_us(1);                 	//wait to make enable wide
   	LCD_CPRT &= ~ (1<<LCD_EN); //EN = 0 for H-to-L pulse
   	_delay_us(100);               	//wait to make enable wide
 
   	LCD_DPRT &= 0x0F;
   	LCD_DPRT |= val<<4;           	//send cmnd to data port
   	LCD_CPRT |= (1<<LCD_EN);      	//EN = 1 for H-to-L pulse
   	_delay_us(1);                 	//wait to make enable wide
   	LCD_CPRT &= ~ (1<<LCD_EN); //EN = 0 for H-to-L pulse
   	_delay_us(100);               	//wait to make enable wide    	
}
 
//*******************************************************
void lcdCommand( unsigned char cmnd ){  
   	LCD_CPRT &= ~ (1<<LCD_RS);    	//RS = 0 for command
   	lcd_putValue(cmnd);
}
 
//*******************************************************
void lcdData( unsigned char data )
{
   	LCD_CPRT |= (1<<LCD_RS);      	//RS = 1 for data   
   	lcd_putValue(data); 
}
 
void lcd_clear()
{
   	lcdCommand(0x01);	
   	_delay_us(1700);
}
 
void lcd_showCursor()
{
   	lcdCommand(0x0E);
   	_delay_us(50);
}
 
void lcd_hideCursor()
{
   	lcdCommand(0x0C);
   	_delay_us(50);
}
 
//*******************************************************
void lcd_init()
{
   	LCD_DDDR |= 0xF0;
   	LCD_CDDR |= (1<<LCD_RS)|(1<<LCD_EN);
 
   	LCD_CPRT &=~(1<<LCD_EN);   //LCD_EN = 0
   	_delay_us(2000); 	//wait for init.
 
   	lcdCommand(0x33);	//send $33 for init.
   	lcdCommand(0x32);	//send $32 for init
   	lcdCommand(0x28);	//init. LCD 2 line,5*7 matrix
   	lcdCommand(0x0e);	//display on, cursor on
   	lcdCommand(0x06);	//shift cursor right
 
   	lcd_clear();     	
}
 
//*******************************************************
void lcd_gotoxy(unsigned char x, unsigned char y)
{ 
   	unsigned char firstCharAdr[]={0x80,0xC0,0x94,0xD4};//Table 12-4 
   	lcdCommand(firstCharAdr[y-1] + x - 1);
   	_delay_us(100);  	
}
 
//*******************************************************
void lcd_print( const char * str )
{
   	unsigned char i = 0;
 
   	while(str[i] != 0) //while it is not end of string
   	{
          	lcdData(str[i]);
          	i++ ;
   	}
}
 
//*******************************************************
int main(void)
{  	
   	lcd_init();
   	lcd_hideCursor();
   	
   	while(1)
   	{  	
          	lcd_clear();
          	lcd_gotoxy(1,1);
          	lcd_print("The world is but");
          	lcd_gotoxy(1,2);
          	lcd_print("one country");
 
          	lcd_showCursor();
          	_delay_ms(2500);
   	
          	lcd_clear();
   	
          	lcd_gotoxy(1,1);
          	lcd_print("and mankind its");
          	lcd_gotoxy(1,2);
          	lcd_print("citizens.");	
          	_delay_ms(3500); 	
   	}
 
  return 0;
}

