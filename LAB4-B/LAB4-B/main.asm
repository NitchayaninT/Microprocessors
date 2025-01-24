;
; LAB4-B.asm
;
; Created: 4/11/2567 23:23:42
; Author : User
;


; Replace with your application code
//act3
.ORG 0x200
lookup_table:
	.DB 0,1,4,9,16,25,36,49,64,81,100

.ORG 0x00
	LDI R16, 10 //count
	LDI R20, 4 //x
	MOV R21, R20 //r21 stores count
	LDI R19, 2
	LDI R18, 9
	LDI ZH, HIGH(2*lookup_table)
	LDI ZL, LOW(2*lookup_table)

findlookup:
	LPM R22, Z
	MUL R21, R21 //stores result in R0:R1
	CP R22, R0
	BREQ next
	ADIW Z,1
	BRNE findlookup

next:
	MUL R19, R20
	ADD R18, R0
	ADD R18, R22 //add with x^2
	MOV R21, R18 //R21 = y
	
	RJMP next

