;
; LAB4-A.asm
;
; Created: 4/11/2567 21:51:25
; Author : User
;


; Replace with your application code
//act3
main:
	LDI R16, 0xFF
	LDI R17, 0x00
	OUT DDRC, R17 //input p
	OUT DDRB, R16 //output p

	SBIS PINC, 3 //skip is bit is 1
	SBI PORTB, 5

	RJMP main