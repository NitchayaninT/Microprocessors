;
; LAB4-A.asm
;
; Created: 4/11/2567 21:51:25
; Author : User
;


; Replace with your application code
//act1
main:
    LDI R16, 0xFF
	LDI R17, 0x00
	OUT DDRD, R17
	OUT DDRB, R16

	//IN R16,PIND
	SBIC PIND,1 //skip if bit cleared (==0)
	SBI PORTB,0 //set bit portB.0 = 1

	SBIC PIND,2
	SBI PORTB,1

	SBIC PIND,3
	SBI PORTB,2
	
	RJMP main
	
	
