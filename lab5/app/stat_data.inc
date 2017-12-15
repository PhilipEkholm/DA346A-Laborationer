/*
 * stat_data.inc
 *
 *  Created: 2017-01-09 03:57:20
 *  Author: Hanna Björk & Sara Billberg
 *	Hämta, rensa och lagra statistik över tärningskast
 */ 
;=======================================================================
; 7 Byte på startadress 0x200
;=======================================================================
init_stat_data:
.DSEG
.ORG		0x200
STAT:		.BYTE		7
.CSEG


;=======================================================================
; Lagra statistik över tärningskasten
; R16 = temp register för värde från och till STAT
; R24 = tärningens värde
;=======================================================================
store_stat:
	LDI			XL,			LOW(STAT) 
	LDI			XH,			HIGH(STAT)	
	LD			R16,		X
	INC			R16
	ST			X,			R16
	ADD			XL,			R24
	LD			R16,		X 
	INC			R16
	ST			X,			R16
	RET
;=======================================================================
; Hämta statistik över alla tärningskast
; R24 - statistik/resultat
;=======================================================================
 get_stat:
	LDI				XL,		LOW(STAT) 
	LDI				XH,		HIGH(STAT)	
	ADD				XL,		R24	
	LD				R24,	X
	RET

			

;=======================================================================
; Rensa all sparad statistik
;=======================================================================
 clear_stat:
	LDI				R16,	0
	LDI				R24,	6
 clearloop:	
 	LDI				XL,		LOW(STAT) 
	LDI				XH,		HIGH(STAT)	
	ADD				XL,		R24
	ST				X,		R16
	DEC				R24
	CPI				R24,	-1
	BRNE			clearloop
	RET
