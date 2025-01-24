//act 6
.SET RAM = 0x100
.ORG  $120
DATA_1:  .DB   $54,$76,$65,$98   ;number 0x98657654
DATA_2:  .DB   $93,$56,$77,$38   ;number 0x38775693
.ORG 0x00
main:
	LDI ZH, HIGH(DATA_1*2)
	LDI ZL, LOW(DATA_1*2)
	LDI YH, HIGH(DATA_2*2)
	LDI YL, LOW(DATA_2*2)
	LDI XL, LOW(RAM)
	LDI XH, HIGH(RAM)
	LDI R20, 4
//add low bytes first and handle carry
addbyte:
	//read from program memory
	LPM R16,Z
	MOV R21, R30 //store temp value for ZL
	MOV R22, R31//store temp value for ZH
	MOVW R30, R28 //move from Y to Z register (R30 gets replaced by Y)
	LPM R17,Z
	MOV R30, R21 //store back to Z
	MOV R31, R22
	ADD R17,R16
	ST X+,R17
	ADIW ZL, 1     ; Increment Z pointer
    ADIW YL, 1     ; Increment Y pointer
	BRCS addwithcarry
	DEC R20
	BRNE addbyte
	BREQ END
	//add 1 to higher byte
addwithcarry:
	LPM R16, Z
	MOVW R30, R28 //move from Y to Z register
	LPM R17, Z
	MOVW R28, R30 //move back to Y register
	ADC R17, R16 // add with carry
	ST X+, R17
	ADIW ZL, 1     ; Increment Z pointer
    ADIW YL, 1     ; Increment Y pointer
	DEC R20
	BREQ END
	BRCC addbyte
	RJMP addwithcarry

END:
	rjmp END

