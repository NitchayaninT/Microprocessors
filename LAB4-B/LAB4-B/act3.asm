;
; LAB4-B.asm
;
; Created: 4/11/2567 23:23:42
; Author : User
;


; Replace with your application code
//act3
.org 0x200
seg7_lookup:
	.DB 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F //0-9
.org 0x00
main:
	LDI R16, 0xFF
	OUT DDRD, R16
	LDI ZH, HIGH(seg7_lookup*2)
	LDI ZL, LOW(seg7_lookup*2)
	LDI R21, 19 //can be 0-255
	LDI R17, 10 //counter
	CLR R19 //0
	RJMP mod_loop
	ADD ZL,R21
	LPM R21, Z
    OUT	PORTD, R21

display:
	ADD ZL,R21
	LPM R21, Z
	OUT	PORTD, R21
	CALL div10_loop
	CP R18,R19 //if 0 or not
	BREQ HERE
	RJMP move_z_back


mod_loop: //modulo
    cp r21, r17       ; Compare r21 (dividend) with r17 (divisor)
    brlo display         ; If r21 < r17, we're done
    sub r21, r17      ; r21 = r21 - r17 //r21 is the result of modulo
    rjmp mod_loop     ; Repeat until r21 < r17

move_z_back:
	LDI ZH, HIGH(seg7_lookup*2)
	LDI ZL, LOW(seg7_lookup*2)
	rjmp mod_loop

clr r18           ; Clear r18 to store the quotient

div10_loop:
    cp r21, r17   ; Compare r21 (dividend) with r17 (10)
    brlo RET    ; If r21 < 10, jump to done (remainder found)
    sub r21, r17  ; r21 = r16 - 10
    inc r18       ; Increment the quotient in r18
    rjmp div10_loop ; Repeat the loop

HERE: RJMP 	HERE
