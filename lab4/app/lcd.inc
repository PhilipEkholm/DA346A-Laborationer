/*
 * lcd.inc
 *
 * This file contains a driver for communicating with a Philips PCD8544
 * LCD controller (48x84 pixels), 6 rows and 14 columns with 8x6 pixel
 * characters. This is the same display that was mounted in a
 * Nokia 5110 cell phone.
 * This driver is written for a LCD mounted on a "iBridge keypad shield",
 * which is mounted on a Arduino Mega board (ATmega2560).
 * SPI communication with the LCD is implemented by bit-banging the protocol.
 *
 * A character is 6 pixels wide, but only 5 pixels forms the character. The
 * last pixel is used as padding between characters.
 *
 * Created by Mathias Beckius, 25 June 2015, for the course DA346A at
 * Malmo University.
 */

;==============================================================================
; Character table, equivalent to a 2 dimensional array, 5 columns per row
;==============================================================================
chars:
	.DB				0x00, 0x00, 0x00, 0x00, 0x00,	/* SPACE */	\
					0x00, 0x00, 0x5f, 0x00, 0x00,	/* ! */		\
					0x00, 0x07, 0x00, 0x07, 0x00,	/* " */		\
					0x14, 0x7f, 0x14, 0x7f, 0x14,	/* # */		\
					0x24, 0x2a, 0x7f, 0x2a, 0x12,	/* $ */		\
					0x23, 0x13, 0x08, 0x64, 0x62,	/* % */		\
					0x36, 0x49, 0x55, 0x22, 0x50,	/* & */		\
					0x00, 0x05, 0x03, 0x00, 0x00,	/* ' */		\
					0x00, 0x1c, 0x22, 0x41, 0x00,	/* ( */		\
					0x00, 0x41, 0x22, 0x1c, 0x00,	/* ) */		\
					0x14, 0x08, 0x3e, 0x08, 0x14,	/* * */		\
					0x08, 0x08, 0x3e, 0x08, 0x08,	/* + */		\
					0x00, 0x50, 0x30, 0x00, 0x00,	/* , */		\
					0x08, 0x08, 0x08, 0x08, 0x08,	/* - */		\
					0x00, 0x60, 0x60, 0x00, 0x00,	/* . */		\
					0x20, 0x10, 0x08, 0x04, 0x02,	/* / */		\
					0x3e, 0x51, 0x49, 0x45, 0x3e,	/* 0 */		\
					0x00, 0x42, 0x7f, 0x40, 0x00,	/* 1 */		\
					0x42, 0x61, 0x51, 0x49, 0x46,	/* 2 */		\
					0x21, 0x41, 0x45, 0x4b, 0x31,	/* 3 */		\
					0x18, 0x14, 0x12, 0x7f, 0x10,	/* 4 */		\
					0x27, 0x45, 0x45, 0x45, 0x39,	/* 5 */		\
					0x3c, 0x4a, 0x49, 0x49, 0x30,	/* 6 */		\
					0x01, 0x71, 0x09, 0x05, 0x03,	/* 7 */		\
					0x36, 0x49, 0x49, 0x49, 0x36,	/* 8 */		\
					0x06, 0x49, 0x49, 0x29, 0x1e,	/* 9 */		\
					0x00, 0x36, 0x36, 0x00, 0x00,	/* : */		\
					0x00, 0x56, 0x36, 0x00, 0x00,	/* ; */		\
					0x08, 0x14, 0x22, 0x41, 0x00,	/* < */		\
					0x14, 0x14, 0x14, 0x14, 0x14,	/* = */		\
					0x00, 0x41, 0x22, 0x14, 0x08,	/* > */		\
					0x02, 0x01, 0x51, 0x09, 0x06,	/* ? */		\
					0x32, 0x49, 0x79, 0x41, 0x3e,	/* @ */		\
					0x7e, 0x11, 0x11, 0x11, 0x7e,	/* A */		\
					0x7f, 0x49, 0x49, 0x49, 0x36,	/* B */		\
					0x3e, 0x41, 0x41, 0x41, 0x22,	/* C */		\
					0x7f, 0x41, 0x41, 0x22, 0x1c,	/* D */		\
					0x7f, 0x49, 0x49, 0x49, 0x41,	/* E */		\
					0x7f, 0x09, 0x09, 0x09, 0x01,	/* F */		\
					0x3e, 0x41, 0x49, 0x49, 0x7a,	/* G */		\
					0x7f, 0x08, 0x08, 0x08, 0x7f,	/* H */		\
					0x00, 0x41, 0x7f, 0x41, 0x00,	/* I */		\
					0x20, 0x40, 0x41, 0x3f, 0x01,	/* J */		\
					0x7f, 0x08, 0x14, 0x22, 0x41,	/* K */		\
					0x7f, 0x40, 0x40, 0x40, 0x40,	/* L */		\
					0x7f, 0x02, 0x0c, 0x02, 0x7f,	/* M */		\
					0x7f, 0x04, 0x08, 0x10, 0x7f,	/* N */		\
					0x3e, 0x41, 0x41, 0x41, 0x3e,	/* O */		\
					0x7f, 0x09, 0x09, 0x09, 0x06,	/* P */		\
					0x3e, 0x41, 0x51, 0x21, 0x5e,	/* Q */		\
					0x7f, 0x09, 0x19, 0x29, 0x46,	/* R */		\
					0x46, 0x49, 0x49, 0x49, 0x31,	/* S */		\
					0x01, 0x01, 0x7f, 0x01, 0x01,	/* T */		\
					0x3f, 0x40, 0x40, 0x40, 0x3f,	/* U */		\
					0x1f, 0x20, 0x40, 0x20, 0x1f,	/* V */		\
					0x3f, 0x40, 0x38, 0x40, 0x3f,	/* W */		\
					0x63, 0x14, 0x08, 0x14, 0x63,	/* X */		\
					0x07, 0x08, 0x70, 0x08, 0x07,	/* Y */		\
					0x61, 0x51, 0x49, 0x45, 0x43,	/* Z */		\
					0x00							/* padding for .DB */

;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU			CHR_WIDTH	 =	5				; Char width (w/o padding)
	.EQU			ASCII_OFFSET =	32				; First char in 'chars'

;==============================================================================
; Macro for writing a command to the LCD.
; Uses registers:
;	R24				Command data / parameter to 'lcd_write_byte'
;
; Example: Write 0x20 to the LCD
;	LCD_WRITE_CMD	0x20
;==============================================================================
	.MACRO			LCD_WRITE_CMD
	CBI				PORTB,			4				; clear D/C pin
	LDI				R24,			@0				; set command as parameter
	RCALL			lcd_write_byte					; write byte to the LCD
	.ENDMACRO

;==============================================================================
; Macro for writing a character to the LCD.
; Uses registers:
;	R24				Character / parameter to 'lcd_write_char'
;
; Example: Write 'A' to the LCD
;	LDI				R24,			'A'
;	LCD_WRITE_CHR
; Example: Write current character stored in R24
;	LCD_WRITE_CHR
;==============================================================================
	.MACRO			LCD_WRITE_CHR
	SBI				PORTB,			4				; set D/C pin
	RCALL			lcd_write_char					; write char to the LCD
	.ENDMACRO

;==============================================================================
; Macro for writing a string of characters to the LCD.
; Uses registers:
;	ZH:ZL			High and Low part of Z register, for string pointer
;
; Example: Write the string 'my_string', stored in program memory
;	LCD_WRITE_STR	my_string
;==============================================================================
	.MACRO			PRINTSTRING
		LDI ZH, high(@0<<1)
		LDI ZL, low(@0<<1)
		RCALL lcd_write_string
	.ENDMACRO

;==============================================================================
; Initialize the LCD.
; Uses registers:
;	R24				Used when calling other subroutines.
;==============================================================================
lcd_init:
	LDI				R24,			20				; Wait after power-up,
	RCALL			delay_ms						; let Vcc stabilize!
	SBI				PORTB,			5				; Set LCD reset pin HIGH
	LDI				R24,			10				; Wait before...
	RCALL			delay_ms						; ...raising...
	SBI				PORTB,			6				; ...CS/SS pin (normal lvl)
	LCD_WRITE_CMD	0x21							; Function set (H=1)
	LCD_WRITE_CMD	0x13							; Set bias mode 1:48
	LCD_WRITE_CMD	0xC0							; Set Vop (contrast)
	LCD_WRITE_CMD	0x04							; Set temp coefficient
	LCD_WRITE_CMD	0x20							; Function set (H=0)
	LCD_WRITE_CMD	0x0C							; Set display control
	RET

;==============================================================================
; Write a string of characters to the LCD.
; Uses registers:
;	ZH:ZL			String pointer
;	R3:R2			Temporary storage of string pointer
;	R24				Used for writing characters
;==============================================================================
lcd_write_string:
iterate_str:
	MOVW			R3:R2,			ZH:ZL			; Store string pointer
	LPM				R24,			Z				; Copy character to reg
	CPI				R24,			0				; End of string?
	BREQ			end_of_str						; ...end subroutine!
	LCD_WRITE_CHR									; Write char to LCD
	MOVW			ZH:ZL,			R3:R2			; Restore string pointer
	ADIW			ZH:ZL,			1				; Increment string pointer
	RJMP			iterate_str						; keep on iterating...
end_of_str:
	RET

;==============================================================================
; Write a character to the LCD.
; Uses registers:
;	R1:R0			Initial pointer to character data in program memory,
;					this is where the result of R16xR17 is stored.
;   ZH:ZL			"Moving pointer" to character data
;	R16				Copy of parameter data (character)
;	R17				Character width (without padding)
;	R24				Parameter data/char (input to this subroutine)
;					also used by 'lcd_write_byte'.
;==============================================================================
lcd_write_char:
	MOV				R16,			R24				; copy char to temp reg
	SUBI			R16,			ASCII_OFFSET	; subtract ASCII-OFFSET
	LDI				R17,			CHR_WIDTH		; set multiplier
	MUL				R16,			R17				; (ASCII-OFFSET)xCHR_WIDTH
	LDI				ZH,				HIGH(chars << 1); Init pointer
	LDI				ZL,				LOW(chars << 1)
	ADD				ZL,				R0				; Set pointer with result from MUL
	ADC				ZH,				R1
	LPM				R24,			Z				; Write 1st segment of char
	RCALL			lcd_write_byte
	ADIW			ZH:ZL,			1				; Increment pointer
	LPM				R24,			Z				; Write 2nd segment of char
	RCALL			lcd_write_byte
	ADIW			ZH:ZL,			1				; Increment pointer
	LPM				R24,			Z				; Write 3rd segment of char
	RCALL			lcd_write_byte
	ADIW			ZH:ZL,			1				; Increment pointer
	LPM				R24,			Z				; Write 4th segment of char
	RCALL			lcd_write_byte
	ADIW			ZH:ZL,			1				; Increment pointer
	LPM				R24,			Z				; Write 5th segment of char
	RCALL			lcd_write_byte
	LDI				R24,			0x00			; Write 6th segment of char
	RCALL			lcd_write_byte					; (padding)
	RET

;==============================================================================
; Write a byte of data to the LCD, start with the most significant bit.
; Uses registers:
;	R16				Copy of parameter data
;	R17				Bit mask (for filtering MSB)
;	R18				Counter (number of bits written to LCD)
;	R24				Parameter data/byte (input to this subroutine)
;					also used by SET_IO_BIT and CLR_IO_BIT macros.
;==============================================================================
lcd_write_byte:
	CBI				PORTB,			6				; Lower CS/SS pin
	MOV				R16,			R24				; Copy data to temp reg
	LDI				R18,			0				; Reset counter
mask_bit:
	LDI				R17,			0x80			; Store bit mask
	AND				R17,			R16				; Mask out MSB
	CPI				R17,			0				; If the MSB is..
	BRNE			bit_is_1						; ..not a 0, branch!
	CLR_IO_BIT		PORTH,			BIT6_LOW		; Clear data pin
	RJMP			write_to_lcd					; Get ready to write data
bit_is_1:
	SET_IO_BIT		PORTH,			BIT6_HIGH		; Set data pin
write_to_lcd:
	SET_IO_BIT		PORTH,			BIT5_HIGH		; Shift out data..
	RCALL			delay_1_micros					; ..by bit-banging..
	CLR_IO_BIT		PORTH,			BIT5_LOW		; ..a clock pulse!
	LSL				R16								; Shift data to the left
	INC				R18								; Increase counter
	CPI				R18,			8				; Shifted all bits?
	BRNE			mask_bit						; Move on to next bit
	SBI				PORTB,			6				; Raise CS/SS pin
	RET												; (normal mode)

;==============================================================================
; Clear screen of the LCD
; Uses registers:
;	R16				Copy of parameter data
;	R24				contain ' ' to be written on screen
;==============================================================================

lcd_clear:
	LCD_WRITE_CMD		0x80 ;Reset cursor to start of LCD
	LCD_WRITE_CMD		0x40
	ldi r19, 150
lcd_clear_loop:
	ldi r24, ' '
	LCD_WRITE_CHR
	dec r19
	brne lcd_clear_loop

	LCD_WRITE_CMD		0x80 ;Reset cursor to start of LCD
	LCD_WRITE_CMD		0x40

	RET