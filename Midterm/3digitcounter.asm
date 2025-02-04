;
; LAB4.asm
;
; Created: 4/11/2567 20:01:47
; Author : User
;

//COUNTER 3 digits!!
//portb,0 = ones
//portb,1 = tens
//portb,2 = hundreds

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
    LDI R16,$F0
    OUT DDRC,R16 //for switch
    LDI R28, $00//R28 is PORTY, use portY to store
	LDI R29, $0
    call seven_seg

seven_seg:
    LDI R22,0b00001111
    AND R22,R28
    LDI R23,0b11110000
    AND R23,R28
    SWAP R23
	LDI R24, 0b00001111
	AND R24, R29
    CHECK R22 //ones
    CHECK R23 //tens
	CHECK R24 //hundreds
    LDI R16,0b00000001 //first bit (ones)
    OUT PORTB,R16
infinte_display:
    OUT PORTD,R22
    CALL DELAY
	ldi R16,0b00000010
    OUT PORTB,R16 //second bit (tens)
    OUT PORTD,R23 
    CALL DELAY
    LDI R16,0b00000100 //third bit (hundreds)
    OUT PORTB, R16 
	OUT PORTD, R24
	CALL DELAY
	CBI PORTB,2
	INC R28
	BRNE seven_seg
	LDI R28, $00
	INC R29
	RJMP seven_seg

data7seg:
    .db 0b00111111,0b00000110; 0,1
    .db 0b01011011,0b01001111; 2,3
    .db 0b01100110,0b01101101; 4,5
    .db 0b01111101,0b00000111; 6,7
    .db 0b01111111,0b01101111; 8,9
    .db 0b01011111,0b01111100; a,b
    .db 0b00111001,0b01011110; c,d
    .db 0b01111001,0b01110001; E,F

DELAY:    LDI    R25, 9
DL1:    LDI    R26, 175
DL2:    LDI    R27, 200
DL3:    NOP
        NOP
        DEC    R27
        BRNE DL3
        DEC    R26
        BRNE DL2
        DEC    R25
        BRNE DL1
        RET
