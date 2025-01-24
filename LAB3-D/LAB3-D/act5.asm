;
; LAB3-D.asm
;
; Created: 2/11/2567 22:14:47
; Author : User
;


; Replace with your application code


.ORG 0x180//program memory start at $300
MYDATA: 
	.DB	$92,$34,$84,$129,$33,$88,$100,$56,$73,$64

.ORG 0x0000 
main:
	LDI R28, 0 
	LDI R29, 0
	LDI ZL, LOW(2*MYDATA)
	LDI ZH, HIGH(2*MYDATA)
	LDI R18, 10

readdata:
	LPM R19, Z+
	ADD R28, R19
	BRCC nocarry
	INC R29

nocarry:
	DEC R18
	BRNE readdata
	RJMP main