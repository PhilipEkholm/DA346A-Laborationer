/*
 * lab5.asm
 *
 *  Created: 2016-12-15 13:32:27
 *   Author: Spellabbet
 *
 *	Edited by: Sara Billberg, Hanna Björk
 *	Implementerat Main part of program
 */ 


  
;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU			RESET		 =	0x0000			; reset vector
	.EQU			PM_START	 =	0x0072			; start of program

	; Bit masks, to be used together with SET_IO_BIT and CLR_IO_BIT
	.EQU			BIT3_HIGH	 =	0x08	; 0b00001000
	.EQU			BIT3_LOW	 =	0xF7	; 0b11110111
	.EQU			BIT4_HIGH	 =	0x10	; 0b00010000
	.EQU			BIT4_LOW	 =	0xEF	; 0b11101111
	.EQU			BIT5_HIGH	 =	0x20	; 0b00100000
	.EQU			BIT5_LOW	 =	0xDF	; 0b11011111
	.EQU			BIT6_HIGH	 =	0x40	; 0b01000000
	.EQU			BIT6_LOW	 =	0xBF	; 0b10111111
	
	; strings
	MYINTRO: .DB "WELCOME! ",0
	MYSTART: .DB "PRESS 2",0
	MYSTART1: .DB "TO ROLL",0
	MY2PRESSED: .DB "ROLLING....",0
	MYVALUE: .DB "VALUE: ",0

;==============================================================================
; Macro for setting a bit in I/O register, located in the extended I/O space.
; Uses registers:
;	R24				Store I/O data
;
; Example: Set bit 6 in PORTH
;	SET_IO_BIT		PORTH,			BIT6_HIGH
;==============================================================================
	.MACRO			SET_IO_BIT
	LDS				R24,			@0
	ORI				R24,			@1
	STS				@0,				R24
	

	.ENDMACRO

;==============================================================================
; Macro for clearing a bit in I/O register, located in the extended I/O space.
; Uses registers:
;	R24				Store I/O data
;
; Example: Clear bit 6 in PORTH
;	CLR_IO_BIT		PORTH,			BIT6_LOW
;==============================================================================
	.MACRO			CLR_IO_BIT
	LDS				R24,			@0
	ANDI			R24,			@1
	STS				@0,				R24

		;UPPGIFT: Implementera MACROT

	.ENDMACRO

;==============================================================================
; Start of program
;==============================================================================
	.CSEG
	.ORG			RESET
	RJMP			init

	.ORG			PM_START
	.INCLUDE		"delay.inc"
	.INCLUDE		"lcd.inc"					; avkommenteras i moment 3
	.INCLUDE		"keyboard.inc"				; avkommenteras i moment 5
	.INCLUDE		"tarning.inc"
	.INCLUDE		"stats.inc"
	.INCLUDE		"monitor.inc"
	.INCLUDE		"stat_data.inc"

;==============================================================================
; Basic initializations of stack pointer, I/O pins, etc.
;==============================================================================
init:
	LDI				R16,			LOW(RAMEND)		; Set stack pointer
	OUT				SPL,			R16				; at the end of RAM.
	LDI				R16,			HIGH(RAMEND)
	OUT				SPH,			R16
	RCALL			init_pins						; Initialize pins
	RCALL			init_pins_led
	RCALL			lcd_init
	RCALL			init_stat
	RCALL			init_monitor						; Initialize LCD - avkommenteras i moment 3
	RJMP			main							; Jump to main

;==============================================================================
; Initialize I/O pins
;==============================================================================
init_pins:
	; PORT B
	; output:	4, 5 and 6 (LCD command/character, reset, CS/SS)
	LDI				R16,			0x70
	OUT				DDRB,			R16
	; PORT H
	; output:	3 and 4 (keypad col 2 and 3)
	;			5 and 6 (LCD clock and data)
	LDI				R16,			0x78
	STS				DDRH,			R16
	; PORT E
	; output:	3 (keypad col 1)
	; input:	4 and 5 (keypad row 2 and 3)
	LDI				R16,			0x08
	OUT				DDRE,			R16
	; PORT F
	; input:	4 and 5 (keypad row 1 and 0)
	LDI				R16,			0x00
	OUT				DDRF,			R16
	; PORT G
	; output:	5 (keypad col 0)
	LDI				R16,			0x20
	OUT				DDRG,			R16
	RET

init_pins_led:
	SBI				DDRB,			7			; enable LED as output
	RET

;==============================================================================
; Main part of program
; Uses registers:
;	R20				temporary storage of pressed key
;	R24				input / output values
;==============================================================================

main:
	RCALL			lcd_clear
	PRINTSTRING MYINTRO
	RCALL			delay_1_s
	RCALL			lcd_clear
	PRINTSTRING MYSTART
	LCD_WRITE_CMD 0x80 
	LCD_WRITE_CMD 0x41
	PRINTSTRING MYSTART1

main_loop:
	RCALL			read_keyboard_num	

no_key_pressed:	
	RCALL			read_keyboard_num	
	CPI				R24,					NO_KEY
	BREQ			no_key_pressed	

		
	MOV				R20,					R24		
	CPI				R20,					TWO_KEY
	BREQ			if_two_pressed	
	CPI				R20,					THREE_KEY
	BREQ			if_three_pressed	
	CPI				R20,					EIGHT_KEY
	BREQ			if_eight_pressed	
	CPI				R20,					NINE_KEY
	BREQ			if_nine_pressed	

if_two_pressed:
	RCALL			lcd_clear
	PRINTSTRING		MY2PRESSED
	RCALL			roll_dice
	MOV				R24,					R21
	RCALL			store_stat
	RCALL			lcd_clear
	PRINTSTRING		MYVALUE
	MOV				R24,					R21
	SUBI			R24,					-48
	LCD_WRITE_CHR
	RJMP			main_loop

if_three_pressed:
	RCALL			lcd_clear
	RCALL			showstat
	RJMP			main

if_eight_pressed:
	RCALL			lcd_clear
	RCALL			clearstat
	RCALL			delay_1_s
	RJMP			main

if_nine_pressed:
	RCALL			lcd_clear
	RCALL			monitor
	RJMP			main
