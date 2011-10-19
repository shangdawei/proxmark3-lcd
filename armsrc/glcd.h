/**
 * \file glcd.h
 * Header: Graphic LCD
 * 
 * Interface and communication handling for Nokia 6610/7250 graphic LCD
 * 
 * Mictronics yamppPod firmware
 * Copyright (C) 2008 by Michael Wolf
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */
#ifndef GLCD_H_
#define GLCD_H_

/**
 * \name LCD commands
 * 
*/
//@{
#ifdef EPSON_CMD
	// EPSON LCD command set
	#define LCD_CMD_CASET		0x15
	#define LCD_CMD_PWRCTR		0x20
	#define LCD_CMD_NOP			0x25
	#define LCD_CMD_RAMWR		0x5C
	#define LCD_CMD_RAMRD		0x5D
	#define LCD_CMD_PASET		0x75
	#define LCD_CMD_EPSRRD1		0x7C
	#define LCD_CMD_EPSRRD2		0x7D
	#define LCD_CMD_VOLCTR		0x81
	#define LCD_CMD_TMPGRD		0x82
	#define LCD_CMD_SLPOUT		0x94
	#define LCD_CMD_SLPIN		0x95
	#define LCD_CMD_DISNOR		0xA6
	#define LCD_CMD_DISINV		0xA7
	#define LCD_CMD_PTLIN		0xA8
	#define LCD_CMD_PTLOUT		0xA9
	#define LCD_CMD_ASCSET		0xAA
	#define LCD_CMD_SCSTART		0xAB
	#define LCD_CMD_DISOFF		0xAE
	#define LCD_CMD_DISON		0xAF
	#define LCD_CMD_COMSCN		0xBB
	#define LCD_CMD_DATCTL		0xBC
	#define LCD_CMD_DISCTL		0xCA
	#define LCD_CMD_EPCOUT		0xCC
	#define LCD_CMD_EPCTIN		0xCD
	#define LCD_CMD_RGBSET8		0xCE
	#define LCD_CMD_OSCON		0xD1
	#define LCD_CMD_OSCOFF		0xD2
	#define LCD_CMD_VOLUP		0xD6
	#define LCD_CMD_VOLDOWN		0xD7
	#define LCD_CMD_RMWIN		0xE0
	#define LCD_CMD_RMWOUT		0xEE
	#define LCD_CMD_EPMWR		0xFC
	#define LCD_CMD_EPMRD		0xFD
#else
	// PHILIPS LCD command set
	#define LCD_CMD_NOP			0x00
	#define LCD_CMD_SWRESET		0x01
	#define LCD_CMD_BSTROFF		0x02
	#define LCD_CMD_BSTRON		0x03
	#define LCD_CMD_RDDIDIF		0x04
	#define LCD_CMD_RDDST		0x09
	#define LCD_CMD_SLEEPIN		0x10
	#define LCD_CMD_SLEEPOUT	0x11
	#define LCD_CMD_PTLON		0x12
	#define LCD_CMD_NORON		0x13
	#define LCD_CMD_INVOFF		0x20
	#define LCD_CMD_INVON		0x21
	#define LCD_CMD_DALO		0x22
	#define LCD_CMD_DAL			0x23
	#define LCD_CMD_SETCON		0x25
	#define LCD_CMD_DISPOFF		0x28
	#define LCD_CMD_DISPON		0x29
	#define LCD_CMD_CASET		0x2A
	#define LCD_CMD_PASET		0x2B
	#define LCD_CMD_RAMWR		0x2C
	#define LCD_CMD_RGBSET		0x2D
	#define LCD_CMD_PTLAR		0x30
	#define LCD_CMD_VSCRDEF		0x33
	#define LCD_CMD_TEOFF		0x34
	#define LCD_CMD_TEON		0x35
	#define LCD_CMD_MADCTL		0x36
	#define LCD_CMD_SEP			0x37
	#define LCD_CMD_IDMOFF		0x38
	#define LCD_CMD_IDMON		0x39
	#define LCD_CMD_COLMOD		0x3A
	#define LCD_CMD_SETVOP		0xB0
	#define LCD_CMD_BRS			0xB4
	#define LCD_CMD_TRS			0xB6
	#define LCD_CMD_FINV		0xB9
	#define LCD_CMD_DOR			0xBA
	#define LCD_CMD_TCDFE		0xBD
	#define LCD_CMD_TCVOPE		0xBF
	#define LCD_CMD_EC			0xC0
	#define LCD_CMD_SETMUL		0xC2
	#define LCD_CMD_TCVOPAB		0xC3
	#define LCD_CMD_TCVOPCD		0xC4
	#define LCD_CMD_TCDF		0xC5
	#define LCD_CMD_DF8C		0xC6
	#define LCD_CMD_SETBS		0xC7
	#define LCD_CMD_RDTEMP		0xC8
	#define LCD_CMD_NLI			0xC9
	#define LCD_CMD_RDID1		0xDA
	#define LCD_CMD_RDID2		0xDB
	#define LCD_CMD_RDID3		0xDC
	#define LCD_CMD_SFD			0xEF
	#define LCD_CMD_ECM			0xF0
#endif

#define CMD                 0x0000
#define DATA                0x0100
//@}


/**
 * \note
 * MADCTR register bits
 *
 *  7   6   5   4   3   2   1   0
 *  MY  MX  MV  ML  RGB -   -   -
 * 
 * ML is Line Scan order up/down
 * 
 */

/**
 * \def MADCTL_HORIZ
 * MY, RGB
 * 
 */
#define MADCTL_HORIZ        0xC0

/**
 * \def MADCTL_VERT
 * MY, MV, RGB
 * 
 */
#define MADCTL_VERT         0xE0

/** \name Some Color Constants
 *
*/
//@{
#define RGB(r,g,b)  ((uint16_t)((uint16_t)(r>>3)<<11) | ((uint16_t)(g>>2)<<6) | ((uint16_t)(b>>3)))
#define RED     RGB(255,0,0)
#define BLACK   RGB(0,0,0)
#define BLUE    RGB(0,0,255)
#define GREEN   RGB(0,255,0)
#define WHITE   RGB(255,255,255)
#define CYAN    RGB(0,255,255)
#define MAGENTA RGB(255,0,255)
#define YELLOW  RGB(255,255,0)
//@}

/**
 * \def PIXEL_OFFSET
 * Offset to compensate tolerances on pixel area 
 */
#define PIXEL_OFFSET  2

/** 
 * \def WINDOW_HEIGHT
 * Set used display window height in pixel
 * 
 */
#define WINDOW_HEIGHT     131
/** 
 * \def WINDOW_WIDTH
 * Set used display window width in pixel
 * 
 */
#define WINDOW_WIDTH      131

/**
 * \def LINE(line)
 * Set line with character positioning and lcd_gotoxy
 * Takes full lines, not pixels.
 * Depends on font height.
 * 
 */
#define LINE(line)  line*lcd_font_height

/**
 * \def POS(pos)
 * Set line with character positioning and lcd_gotoxy
 * Takes full characters, not pixels.
 * Depends on font width.
 * 
 */
#define POS(pos)    pos*lcd_font_width

extern volatile uint8_t lcd_xpos;
extern volatile uint8_t lcd_ypos;
extern volatile uint8_t lcd_font_height;
extern volatile uint8_t lcd_font_width;
extern volatile uint8_t lcd_font_firstchar;
extern volatile uint8_t lcd_font_vertical;
extern volatile uint8_t lcd_invert;
extern volatile uint16_t lcd_text_color;
extern volatile uint16_t lcd_back_color;


/**
 * \def LCD
 * Function name used for LCD output stream
 * 
 */
#define LCD     lcd_putchar

void lcd_reset(void);
void lcd_send(unsigned int data);
uint8_t lcd_getcontrast(void);
void lcd_setcontrast(uint8_t ctr);
void lcd_init(void);
void lcd_window(uint8_t xs, uint8_t ys, uint8_t xe, uint8_t ye);
void lcd_clear(void);
void lcd_gotoxy (uint8_t x, uint8_t y);
void lcd_newline (void);
void lcd_clrline (uint8_t ypos);
void lcd_puts(const char * string);
void lcd_putchar (char data);
void lcd_setcolor(uint16_t back, uint16_t text);
void lcd_off(void);

#endif /*GLCD_H_*/
