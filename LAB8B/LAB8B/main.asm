.EQU	KEY_PORT = PORTD		
.EQU	KEY_PIN = PIND
.EQU	KEY_DDR = DDRD
 		
	LDI 	R20,HIGH(RAMEND)
	OUT 	SPH,R20
	LDI 	R20,LOW(RAMEND)
	OUT 	SPL,R20
	
	LDI 	R21,0xFF
	OUT 	DDRB,R21

	LDI 	R20,0xF0
	OUT 	KEY_DDR,R20

GROUND_ALL_ROWS:
	LDI 	R20,0x0F
	OUT 	KEY_PORT,R20

WAIT_FOR_RELEASE:
	NOP
	IN  	R21,KEY_PIN 		;Read Key Pins
	ANDI	R21,0x0F    		;Mask unused bits
	CPI 	R21,0x0F    		;(equal if no key)
	BRNE	WAIT_FOR_RELEASE	;Do again till keys released

WAIT_FOR_KEY:
	NOP
	IN  	R21,KEY_PIN		;Read Key Pins
	ANDI	R21,0x0F		;Mask unused bits
	CPI 	R21,0x0F		;(equal if no key)
	BREQ	WAIT_FOR_KEY	;Do again till a key pressed

	CALL	WAIT15MS		;Wait 15ms

	IN  	R21,KEY_PIN		;Read Key Pins
	ANDI	R21,0x0F		;Mask unused bits
	CPI 	R21,0x0F		;(equal if no key)
	BREQ	WAIT_FOR_KEY	;Do again till a key pressed


	LDI 	R21,0b01111111	;Ground row 0
	OUT 	KEY_PORT,R21	
	NOP
	IN  	R21,KEY_PIN		;Read all columns
	ANDI	R21,0x0F		;Mask unused bits
	CPI 	R21,0x0F		;(equal if no key)
	BRNE	ROW0			;row 0, find the coloum

	LDI 	R21,0b10111111	;Ground row 1
	OUT 	KEY_PORT,R21	
	NOP
	IN  	R21,KEY_PIN		;Read all columns
	ANDI	R21,0x0F		;Mask unused bits
	CPI 	R21,0x0F		;(equal if no key)
	BRNE	ROW1			;row 1, find the colomn

	LDI 	R21,0b11011111	;Ground row 2
OUT 	KEY_PORT,R21	
	NOP
	IN  	R21,KEY_PIN		;Read all columns
	ANDI	R21,0x0F		;Mask unused bits
	CPI 	R21,0x0F		;(equal if no key)
	BRNE	ROW2			;row 2, find the column

	LDI 	R21,0b11101111	;Ground row 3
	OUT 	KEY_PORT,R21	
	NOP
	IN  	R21,KEY_PIN		;Read all columns
	ANDI	R21,0x0F		;Mask unused bits
	CPI 	R21,0x0F		;(equal if no key)
	BRNE	ROW3			;row 3, find the column

ROW0:
	LDI 	R30,LOW(KCODE0<<1)
	LDI 	R31,HIGH(KCODE0<<1)
	RJMP	FIND

ROW1:
	LDI 	R30,LOW(KCODE1<<1)
	LDI 	R31,HIGH(KCODE1<<1)
	RJMP	FIND

ROW2:
	LDI 	R30,LOW(KCODE2<<1)
	LDI 	R31,HIGH(KCODE2<<1)
	RJMP	FIND

ROW3:
	LDI 	R30,LOW(KCODE3<<1)
	LDI 	R31,HIGH(KCODE3<<1)
	RJMP	FIND

FIND:
	ldi	r29,0
FIND1:
	inc	r29

	LSR 	R21
	BRCC	MATCH			;if Carry is low goto match
	LPM 	R20,Z+			;INC Z
	RJMP	FIND1	
MATCH:
	out	portc,r29

	LPM 	R20,Z
	OUT 	PORTB,R20

	RJMP	GROUND_ALL_ROWS

WAIT15MS:	;place a code to wait 15 ms here
	RET

.ORG 0x300
KCODE0:	.DB '0','1','2','3'		;ROW 0
KCODE1:	.DB '4','5','6','7'		;ROW 1
KCODE2:	.DB '8','9','A','B'		;ROW 2
KCODE3:	.DB 'C','D','E','F'		;ROW 3
