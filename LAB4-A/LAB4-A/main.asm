;
; LAB4-A.asm
;
; Created: 4/11/2567 21:51:25
; Author : User
;


; Replace with your application code
//act3.2
main:
     CLR   R10
     COM   R10
     LDI   R16, $AA
     EOR   R10, R16

	RJMP main