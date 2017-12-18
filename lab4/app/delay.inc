/*
 * delay.inc
 *
 * This file contains delay routines.
 *
 * Created by Mathias Beckius, 25 June 2015, for the course DA346A at
 * Malmo University.
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
	ldi r24, 250
	rcall delay_micros
	ldi r24, 250
	rcall delay_micros
	ldi r24, 250
	rcall delay_micros
	ldi r24, 250
	rcall delay_micros

	dec r18
	brne loop_dms

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
	ldi r24, 250
	rcall delay_ms
	ldi r24, 250
	rcall delay_ms
	ldi r24, 250
	rcall delay_ms
	ldi r24, 250
	rcall delay_ms
	dec r17
	brne loop_ds

	RET
