;
; LAB4.asm
;
; Created: 4/11/2567 20:01:47
; Author : User
;

; Replace with your application code
.MACRO CHECK
    LDI ZH,high(data7seg*2)
    LDI ZL,low(data7seg*2)
    ADD ZL,@0
    LPM @0,Z
.ENDMACRO

start:
    LDI R16,$FF
    OUT DDRD,R16
    OUT DDRB,R16
    LDI R21,$00
    call seven_seg

seven_seg:
    LDI R22,0b00001111 //lower nibble
    AND R22,R21 //get ones
    LDI R23,0b11110000 //higher nibble
    AND R23,R21 //get tens (but still in higher nibbles)
    SWAP R23 //swap higher and lower nibbles to move the result to lower nibbles (tens)
    CHECK R22
    CHECK R23
    LDI R16,0b01
    OUT PORTB,R16
infinte_display:
    OUT PORTD,R22
    CALL DELAY
    COM R16
    OUT PORTB,R16
    OUT PORTD,R23
    CALL DELAY
    COM R16
    OUT PORTB,R16
    INC R21
    JMP seven_seg
data7seg:
    .db 0b00111111,0b00000110; 0,1
    .db 0b01011011,0b01001111; 2,3
    .db 0b01100110,0b01101101; 4,5
    .db 0b01111101,0b00000111; 6,7
    .db 0b01111111,0b01101111; 8,9
    .db 0b01011111,0b01111100; a,b
    .db 0b00111001,0b01011110; c,d
    .db 0b01111001,0b01110001; E,F

DELAY:    LDI    R25, 10
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