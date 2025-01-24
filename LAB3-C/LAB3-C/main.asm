;
; LAB3-C.asm
;
; Created: 2/11/2567 19:35:00
; Author : User
;


; Replace with your application code
//ACT3
//use the DIP switches on picsimlab to set the max count for up-counter
//here, i tried using port D for both input and output
LDI R16, 0xFF 
LDI R18, 0xFF
LDI R17, 0x00
LDI R19, 0x00
OUT DDRD, R19 //set to input first
//OUT DDRB, R17

IN R20,PIND //read from pinB (count)
OUT DDRD, R18 //then set it to output
//INC R20 //so that it will count to the exact number we input to the switch
 counter:
	OUT PORTD, R17
	INC R17
	CALL DELAY
	DEC R20
	BRNE counter
	RJMP L1

L1:
	LDI R17, 0x00
	OUT PORTD, R17 //reset to 0
	IN R20, PIND
	INC R20
	RJMP counter

DELAY:  LDI	R21, 80
DL1:	LDI	R22, 125
DL2:	LDI	R23, 100
DL3:	NOP
    	NOP
    	DEC	R23
    	BRNE   DL3
    	DEC    R22
    	BRNE   DL2
    	DEC	R21
    	BRNE   DL1
    	RET