/*
 * keyboard.inc
 *
 * This file contains a driver for reading the keypad on the
 * "iBridge keypad shield". The driver is adapted for a shield mounted
 * on a Arduino Mega board (ATmega2560).
 *
 * Key mapping:
 *					-----------------
 *					| 1 | 2 | 3 | A |
 *					-----------------
 *					| 4 | 5 | 6 | B |
 *					-----------------
 *					| 7 | 8 | 9 | C |
 *					-----------------
 *					| * | 0 | # | D |
 *					-----------------
 *
 * Created by Mathias Beckius, 25 June 2015, for the course DA346A at
 * Malmo University.
 *
 * Edited by Sara Billberg, Hanna Björk
 * Vi har implementerad read_keyboard_num. Nu sätts R24 till viss siffra beroende på vilken tangent man trycker på.
 * vi har även lagt in table och characters: 147*2580369#ABCD
 *
 *
 */

;==============================================================================
; Table of characters, for mapping with keys
;==============================================================================
keys:
	.DB				"147*2580369#ABCD", NO_KEY, 0

;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU			NO_KEY		=	16				; no key was pressed!
	.EQU			TWO_KEY		=	4				; two is pressed
	.EQU			THREE_KEY		=	8				; three is pressed
	.EQU			EIGHT_KEY		=	6				; eight is pressed
	.EQU			NINE_KEY		=	10				; nine is pressed

;==============================================================================
; Read keyboard
; Returns the corresponding character for the pressed key. If no key is
; pressed, then NO_KEY is returned.
;
; Uses registers:
;	R19			Counter to use as pointer 
;   R24			Register when returning key
;
; Important! A minimum delay of 2 NOP's is necessary after setting port,
; before pin can be read.
;==============================================================================
read_keyboard_num:
	LDI				R19,			0				; Reset counter
	
	SBI				PORTG,			5				// Set column 0
	CBI				PORTE,			3				// Clear column 1
	CLR_IO_BIT		PORTH,			BIT3_LOW		// Clear column 2
	CLR_IO_BIT		PORTH,			BIT4_LOW		// Clear column 3
	RCALL			delay_1_micros
	RCALL			delay_1_micros
	RCALL			delay_1_micros
	RCALL			delay_1_micros
	RCALL			delay_1_micros
	RCALL			delay_1_micros
	SBIC			PINF,			5
	RJMP			return_key
	INC				R19 //1
	SBIC			PINF,			4
	RJMP			return_key
	INC				R19 //2
	SBIC			PINE,			4
	RJMP			return_key	
	INC				R19 //3
	SBIC			PINE,			5
	RJMP			return_key
	
	CBI				PORTG,			5				// Clear column 0
	SBI				PORTE,			3				// Set column 1
	CLR_IO_BIT		PORTH,			BIT3_LOW		// Clear column 2
	CLR_IO_BIT		PORTH,			BIT4_LOW		// Clear column 3
	RCALL			delay_1_micros
	RCALL			delay_1_micros
	RCALL			delay_1_micros	
	RCALL			delay_1_micros

	INC				R19 //4
	SBIC			PINF,			5
	RJMP			return_key
	INC				R19	//5
	SBIC			PINF,			4
	RJMP			return_key
	INC				R19	//6
	SBIC			PINE,			4
	RJMP			return_key 
	INC				R19	//7
	SBIC			PINE,			5
	RJMP			return_key	

	CBI				PORTG,			 5					// Clear column 0
	CBI				PORTE,			 3					// Clear column 1
	SET_IO_BIT		PORTH,			 BIT3_HIGH			// Set column 2
	CLR_IO_BIT		PORTH,			 BIT4_LOW			// Clear column 3
	RCALL			delay_1_micros
	RCALL			delay_1_micros
	RCALL			delay_1_micros
	RCALL			delay_1_micros


	INC				R19	//8
	SBIC			PINF,			5
	RJMP			return_key
	

	INC				R19	//9
	SBIC			PINF,			4
	RJMP			return_key

	INC				R19	//10
	SBIC			PINE,			4
	RJMP			return_key

	INC				R19	//11
	SBIC			PINE,			5
	RJMP			return_key
	

	CBI				PORTG,			5				// Clear column 0
	CBI				PORTE,			3				// Clear column 1
	CLR_IO_BIT		PORTH,			BIT3_LOW		// Clear column 2
	SET_IO_BIT		PORTH,			BIT4_HIGH		// set column 3
	RCALL			delay_1_micros
	RCALL			delay_1_micros
	RCALL			delay_1_micros
	RCALL			delay_1_micros


	INC				R19	//12
	SBIC			PINF,			5
	RJMP			return_key

	INC				R19	//13
	SBIC			PINF,			4
	RJMP			return_key

	INC				R19	//14
	SBIC			PINE,			4
	RJMP			return_key

	INC				R19	//15
	SBIC			PINE,			5
	RJMP			return_key
	
	INC				R19	//16	 	
return_key:
	MOV				R24,			R19
	RET

;=======================================================================
; Assume RVAL contains keyboard key number
; Returns ASCII value in RVAL
;=======================================================================
convert_to_ASCII:
	LDI				ZH,				HIGH(keys << 1)	; Init pointer
	LDI				ZL,				LOW(keys << 1)
	ADD				ZL,				R24				; Point to character
	LDI				R24,			0
	ADC				ZH,				R24
	LDI				R24,			50				; Delay of 50 ms
	RCALL			delay_ms
	LPM				R24,			Z				; Return character
	RET