#ifndef __LCD_DEFINES_H__
#define __LCD_DEFINES_H__

/*---------------------------------------------------------
 LCD Pin Definitions
----------------------------------------------------------*/

/* LCD Data Bus connected to Port 0 Pins P0.16 to P0.23 */
#define LCD_DATA            16

/* Register Select (RS) pin connected to P0.28
   RS = 0 -> Command Register
   RS = 1 -> Data Register */
#define RS                  28

/* Read/Write (RW) pin connected to P0.30
   RW = 0 -> Write Operation
   RW = 1 -> Read Operation */
#define RW                  30

/* Enable (EN) pin connected to P0.29
   Generates the enable pulse for LCD communication */
#define EN                  29


/*---------------------------------------------------------
 LCD Command Definitions
----------------------------------------------------------*/

/* Clear the LCD display and move cursor to home position */
#define CLEAR_LCD           0x01

/* Return cursor to the home position */
#define RET_CUR_HOME        0x02

/* Configure LCD in 4-bit, single-line mode */
#define MODE_4BIT_1LINE     0x20

/* Configure LCD in 4-bit, two-line mode */
#define MODE_4BIT_2LINE     0x28

/* Configure LCD in 8-bit, single-line mode */
#define MODE_8BIT_1LINE     0x30

/* Configure LCD in 8-bit, two-line mode */
#define MODE_8BIT_2LINE     0x38

/* Turn OFF LCD display */
#define DISP_OFF            0x08

/* Turn ON display and hide cursor */
#define DISP_ON_CUR_OFF     0x0C

/* Turn ON display and show cursor */
#define DISP_ON_CUR_ON      0x0E

/* Turn ON display with blinking cursor */
#define DISP_ON_CUR_BLINK   0x0F

/* Move cursor to Line 1, Position 0 */
#define GOTO_LINE1_POS0     0x80

/* Move cursor to Line 2, Position 0 */
#define GOTO_LINE2_POS0     0xC0

/* Select CGRAM for creating custom characters */
#define GOTO_CGRAM          0x40

/* Move cursor one position to the right after each character */
#define SHIFT_CUR_RIGHT     0x06

#endif
