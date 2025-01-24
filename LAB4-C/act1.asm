//use to find which number to display in lookup
.macro sevenSeg
    ldi zl, low(0x200)
    ldi zh, high(0x200)
    add zl, @1 //move pointer how many times
    lpm @0, z
.endmacro
 //eg. sevenSeg r17, r16(5) ; Get 7-segment pattern for '5' and store in r17
.org 0x200
7seg_lookup:
	.DB 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F //0-9
main:
	LDI R16, 0xFF
	OUT DDRD, R16
	LDI	R20, 0b00000111
    OUT	PORTD, R20

HERE: RJMP 	HERE
