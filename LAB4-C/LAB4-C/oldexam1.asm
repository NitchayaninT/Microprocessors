;
; LAB4-B.asm
;
; Created: 4/11/2567 23:23:42
; Author : User
;


; Replace with your application code
//COUNTER


start:
    LDI R16,$FF
	LDI R19, $00
    OUT DDRD,R16
	LDI ZL, LOW(seg7_lookup*2)
	LDI ZH, HIGH(seg7_lookup*2)
    call seven_seg

seven_seg:
    LPM R22, Z+
    OUT PORTD,R22

infinte_display:
    CALL DELAY
	LPM R23, Z
	CP R23, R19
    BREQ move_z
    JMP seven_seg

move_z:
	LDI ZL, LOW(seg7_lookup*2)
	LDI ZH, HIGH(seg7_lookup*2)
	JMP seven_seg



DELAY:    LDI    R25, 32
DL1:    LDI    R26, 200
DL2:    LDI    R27, 250
DL3:    NOP
        NOP
        DEC    R27
        BRNE DL3
        DEC    R26
        BRNE DL2
        DEC    R25
        BRNE DL1
        RET

.ORG 0x200
seg7_lookup:
    .db 0b01111111,0b11111101; 
    .db 0b01111110,0b10111111; 
    .db 0b01101111,0b11110111; 
    .db 0b01111011,0b01111111; 
    .db 0b00111101,0b00011111; 
    .db 0b00101111,0b00110111; 
    .db 0b00111011,0b00111100; 
    .db 0b00011101,0b00101101; 
    .db 0b00110101,0b00111001;
    .db 0b00011100,0b00101100; 
	.db 0b00110100,0b00111000;
	.db 0b00001100,0b00010100;
	.db 0b00011000,0b00000100; 
	.db 0b00001000,0b00000000; 