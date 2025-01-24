;
; LAB4-A.asm
;
; Created: 4/11/2567 21:51:25
; Author : User
;


; Replace with your application code
//act2
main:
	LDI R16, 0xFF
	LDI R17, 0x00
	OUT DDRC, R17 //input p
	OUT DDRB, R16 //output p

	SBIC PINC, 1
	SBI PORTB, 0

	SBIC PINC, 6
	SBI PORTB, 2

	RJMP main
