;
; LAB4.asm
;
; Created: 4/11/2567 20:01:47
; Author : User
;

; Replace with your application code
//use 2 buttons to control leds to increment or dec
//Switch right, switch left
//0 1 = increment
//1 0 = decrement
//1 1 = freezes
//0 0 = freezes

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
    LDI R21, $00 //R21 represents current value
    call seven_seg

seven_seg:
    LDI R22,0b00001111
    AND R22,R21
    LDI R23,0b11110000
    AND R23,R21
    SWAP R23
    CHECK R22 //ones
    CHECK R23 //tens
    LDI R16,0b01 //first bit (ones)
    OUT PORTB,R16
infinte_display:
    OUT PORTD,R22
    CALL DELAY
    COM R16
    OUT PORTB,R16 //second bit (tens)
    OUT PORTD,R23 
    CALL DELAY
    COM R16
    OUT PORTB,R16 
    CALL button
freezing:
	SBIC PORTC,6 //if freeze, jump
	RJMP seven_seg
inc_dec:
    SBIS PORTC,5 
	DEC R21
	SBIC PORTC,5
	INC R21
    JMP seven_seg


//R17 is current state and previous state
//current state = bit 0. previous state = bit 1  of pinC
button:
    SBIS PINC,0;record current state
    CBR R17,1
    SBIC PINC,0
    SBR R17,1

	SBIS PINC,1
	CBR R17,2
    SBIC PINC,1
    SBR R17,2
    CPI R17,1 //compare R17 with 1
    BREQ increment//0x01
	CPI R17,2
	BREQ decrement//0x10

freeze:
	SBI PORTC, 6 //set portc6 to freeze
	RET
increment:
    CBI PORTC,6
	SBI PORTC,5 //portc5 = 1 is inc
    RET
decrement:
    CBI PORTC,6
	CBI PORTC,5 //portc5 = 0 dec
    RET

data7seg:
    .db 0b00111111,0b00000110; 0,1
    .db 0b01011011,0b01001111; 2,3
    .db 0b01100110,0b01101101; 4,5
    .db 0b01111101,0b00000111; 6,7
    .db 0b01111111,0b01101111; 8,9
    .db 0b01011111,0b01111100; a,b
    .db 0b00111001,0b01011110; c,d
    .db 0b01111001,0b01110001; E,F

DELAY:    LDI    R25, 8
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
