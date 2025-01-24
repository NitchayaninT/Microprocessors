;
; LAB4.asm
;
; Created: 4/11/2567 20:01:47
; Author : User
;

; Replace with your application code
//previous state & current state
//0 0 = not pressing
//0 1 = press
//1 1 = long press
//1 0 = stop pressing (put finger off)

//when pressed and pull finger off:
	//state is 0 1 when pressed, and check current state (if freezing or not)
	//if not, set to freeze
	//if its freezing, set to unfreeze and return to default mode
	//1.user presses to stop
	//0 1 -> freezing ( 1 1 if user pressed long ) or ( 1 0 user stop pressing ) 
	//2.user presses again ( o continue)
	//0 1 -> unfreezing ( 1 1 user pressed long ) or ( 1 0 user stop pressing )
	//if state is something else other than 0 1, no need to check
	//just check when state is 0 1 (when user presses)

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
    OUT DDRC,R16
    LDI R21,$FF
    call seven_seg

seven_seg:
    LDI R22,0b00001111
    AND R22,R21
    LDI R23,0b11110000
    AND R23,R21
    SWAP R23
    CHECK R22
    CHECK R23
    LDI R16,0b01
    OUT PORTB,R16
;infinte_display:
    OUT PORTD,R22
    CALL DELAY
    COM R16
    OUT PORTB,R16
    OUT PORTD,R23
    CALL DELAY
    COM R16
    OUT PORTB,R16
    CALL button //check button if pressed or not
	//finished checking
    SBIS PORTC,6 //if bit 6 of port C is set, that means we have to freeze that number
    DEC R21
    JMP seven_seg
//R17 stores current state and previous state
//current state = bit 0. previous state = bit 1  of pinC
button:
    SBRS R17,0;move old CS to PS
    CBR R17,2
    SBRC R17,0
    SBR R17,2
    SBIS PINC,0;record current state
    CBR R17,1
    SBIC PINC,0
    SBR R17,1
    CPI R17,1 //compare R17 with 1 (if the state is 01)
    BREQ press //if they're equal, go to press*** (currently in 0,1 state)
    RET //otherwise, return to previous function and continue the state (not change state)
press:
//check current state (on or off) to set next state
    SBIC PORTC,6 //if portC, 6 is set, that means its current state is FREEZE (we have to unfreeze it)
    RJMP unfreeze
    SBIS PORTC,6 //if port C is cleared, its in UNFREEZING state (we have to freeze it)
    RJMP freeze
unfreeze:
    CBI PORTC,6 //clear it to be off (not freezing)
    RET
freeze:
    SBI PORTC,6 //clear it to be on (Freezing)
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
