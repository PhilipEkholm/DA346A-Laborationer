/*
 * delay.inc
 *
 * This file contains delay routines.
 *
 * Created by Mathias Beckius, 25 June 2015, for the course DA346A at
 * Malmo University.
 *
 * Edited by Sara Billberg, Hanna Björk
 * Vi har implementerat två delay funktioner delay_s och delay_ms
 */

;==============================================================================
; Delay of 1 µs (including RCALL)
;==============================================================================
delay_1_micros:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	RET

;==============================================================================
; Delay of X µs
;	LDI + RCALL = 4 cycles
; Uses registers:
;	R24				Input parameter data (X µs)
;==============================================================================
delay_micros:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	DEC				R24
	CPI				R24,			0				; more loops to do?
	BRNE			delay_micros					; continue!
	RET

;==============================================================================
; Delay of X ms
;	LDI + RCALL = 4 cycles
; Uses registers:
;	R18				Copy of parameter data (X ms)
;	R24				Input parameter data (X ms) and
;					also input to 'delay_micros'.
;==============================================================================
delay_ms:
	MOV				R18,			R24

loop_dms:
	LDI				R24,			250
	RCALL			delay_micros
	LDI				R24,			250
	RCALL			delay_micros
	LDI				R24,			250
	RCALL			delay_micros
	LDI				R24,			250
	RCALL			delay_micros
	DEC				R18
	CPI				R18,			0
	BRNE			loop_dms
	RET

;==============================================================================
; Delay of X s
;	LDI + RCALL = 4 cycles
; Uses registers:
;	R17				Copy of parameter data (X s)
;	R24				Input parameter data (X s) and
;					also input to 'delay_micros'.
;==============================================================================
delay_s:
	MOV				R17,			R24
loop_ds:
	LDI				R24,			250
	RCALL			delay_ms
	LDI				R24,			250
	RCALL			delay_ms
	LDI				R24,			250
	RCALL			delay_ms
	LDI				R24,			250
	RCALL			delay_ms
	DEC				R17
	CPI				R17,			0
	BRNE			loop_ds


	RET

;==============================================================================
; Delay 1 s
;
; Uses registers:
;	R17				Copy of parameter data (X s)
;	R24				Input parameter data (X s) and
;					also input to 'delay_micros'.
;==============================================================================
delay_1_s:
	LDI				R24,			250
	RCALL			delay_ms
	LDI				R24,			250
	RCALL			delay_ms
	LDI				R24,			250
	RCALL			delay_ms
	LDI				R24,			250
	RCALL			delay_ms
	RET