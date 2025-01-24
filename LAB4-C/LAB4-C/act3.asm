;
; LAB4-B.asm
;
; Created: 4/11/2567 23:23:42
; Author : User
;


; Replace with your application code
//act3
.equ DELAY_INNER = 255 	; Inner loop count
.equ DELAY_OUTER = 255 	; Outer loop count
.org 0x200
seg7_lookup:
    .db 0b00111111,0b00000011; 0,1
    .db 0b01011011,0b01001111; 2,3
    .db 0b01100110,0b01101101; 4,5
    .db 0b01111101,0b00000111; 6,7
    .db 0b01111111,0b01101111; 8,9
    .db 0b01011111,0b01111100; a,b
    .db 0b00111001,0b01011110; c,d
    .db 0b01111001,0b01110001; E,F
.org 0x00
main:
	LDI R16, 0xFF
	OUT DDRD, R16
    LDI R16, 0x03 //controlling 7seg display
    OUT DDRB, R16
	LDI ZH, HIGH(seg7_lookup*2)
	LDI ZL, LOW(seg7_lookup*2)
	LDI R21, 0x23 //can be 0-0xFF
	LDI R17, 16 //counter
	CLR R19 //0
	CLR R18

    MOV R23, R21//R23= temp for R21    
    CALL div16          
    MOV R24, R18//R24=tens      
    MOV R21, R23        
    RJMP mod_loop 
ones:    
	MOV R23, R21 //R23=ones
    RJMP display

mod_loop: //modulo
    CP r21, r17  
    BRLO ones  
    SUB r21, r17 
    RJMP mod_loop  

div16:
    CLR R18                  
div16_loop:
    CP R21, R17          
    BRLO done_div16         
    SUB R21, R17             
    INC R18 //R18++    
    RJMP div16_loop
done_div16:
    RET

HERE: RJMP 	HERE
display:
    //tens
    LDI ZL, LOW(seg7_lookup*2)   
    LDI ZH, HIGH(seg7_lookup*2)
	ADD ZL, R24
    LPM R22, Z
    OUT PORTD, R22                   
    //tens = portb.0 (d3)
    SBI PORTB, 0
    CBI PORTB, 1               
    CALL delay                    

    //ones
    LDI ZL, LOW(seg7_lookup*2)  
    LDI ZH, HIGH(seg7_lookup*2)
	ADD ZL, R23
    LPM R22, Z                        
    OUT PORTD, R22                   
    //ones = portb.1 (d4)
    CBI PORTB, 0
    SBI PORTB, 1     
    CALL delay        

    RJMP display                

delay:
	LDI R18, DELAY_OUTER   ; Load outer loop counter (800)
L1:
	LDI R19, DELAY_INNER   ; Load inner loop counter (100)
L2:
	NOP                	; Each NOP takes 1 cycle //used to add small delays by taking one CPU cycle
	DEC R19            	; Decrement inner loop counter
	BRNE L2     	   	; Branch if not zero, takes 2 cycles if branch.  taken, 1 cycle if not
	DEC R18            	; Decrement outer loop counter
	BRNE L1       	 	; Branch if not zero
	RET                	; Return from subroutine