;
; LAB4-B.asm
;
; Created: 4/11/2567 23:23:42
; Author : User
;


; Replace with your application code
//act1

.SET RAM_ADD = 0x140
.ORG 0x200
hello_data:
	.DB "Hello World!"

.ORG 0x00
main:
	LDI ZH, HIGH(2*hello_data)
	LDI ZL, LOW(2*hello_data)
	LDI YH, HIGH(RAM_ADD)
	LDI YL, LOW(RAM_ADD)
	LDI R20,12
copy:
	LPM R16, Z+
	ST Y+, R16
	DEC R20
	BRNE copy

LDI R20,12
LDI YH, HIGH(RAM_ADD)
LDI YL, LOW(RAM_ADD)
LDI ZH, HIGH(0x160)
LDI ZL, LOW(0x160)
subroutine:
	LD R21, Y+
	ST Z+,R21
	DEC R20
	BRNE subroutine

end:
	RJMP end