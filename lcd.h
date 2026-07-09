#ifndef __LCD_H__
#define __LCD_H__

#include "types.h"

/*---------------------------------------------------------
 Function Name : WriteLCD()
 Description   : Writes a byte (command or data) to the LCD.
 Input         : data - Byte to be written.
----------------------------------------------------------*/
void WriteLCD(u8 data);

/*---------------------------------------------------------
 Function Name : CmdLCD()
 Description   : Sends a command to the LCD.
 Input         : cmd - LCD command.
----------------------------------------------------------*/
void CmdLCD(u8 cmd);

/*---------------------------------------------------------
 Function Name : CharLCD()
 Description   : Displays a single ASCII character on the LCD.
 Input         : ascii - Character to be displayed.
----------------------------------------------------------*/
void CharLCD(u8 ascii);

/*---------------------------------------------------------
 Function Name : InitLCD()
 Description   : Initializes the 16×2 LCD in 8-bit mode.
----------------------------------------------------------*/
void InitLCD(void);

/*---------------------------------------------------------
 Function Name : StrLCD()
 Description   : Displays a null-terminated string on the LCD.
 Input         : str - Pointer to the string.
----------------------------------------------------------*/
void StrLCD(char *str);

/*---------------------------------------------------------
 Function Name : U32LCD()
 Description   : Displays an unsigned 32-bit integer.
 Input         : n - Unsigned integer.
----------------------------------------------------------*/
void U32LCD(u32 n);

/*---------------------------------------------------------
 Function Name : S32LCD()
 Description   : Displays a signed 32-bit integer.
 Input         : n - Signed integer.
----------------------------------------------------------*/
void S32LCD(s32 n);

/*---------------------------------------------------------
 Function Name : BinLCD()
 Description   : Displays a number in binary format.
 Input         :
      n   - Number to display.
      nbd - Number of bits to display.
----------------------------------------------------------*/
void BinLCD(u32 n, u8 nbd);

/*---------------------------------------------------------
 Function Name : BuildCGRAM()
 Description   : Creates custom characters in the LCD CGRAM.
 Input         :
      p      - Pointer to custom character pattern.
      nBytes - Number of bytes in the pattern.
----------------------------------------------------------*/
void BuildCGRAM(u8 *p, u8 nBytes);

/*---------------------------------------------------------
 Function Name : f32LCD()
 Description   : Displays a floating-point number with the
                 specified number of decimal places.
 Input         :
      fnum - Floating-point number.
      ndp  - Number of decimal places.
----------------------------------------------------------*/
void f32LCD(f32 fnum, u8 ndp);

/*---------------------------------------------------------
 Function Name : OctLCD()
 Description   : Displays a number in octal format.
 Input         : n - Unsigned integer.
----------------------------------------------------------*/
void OctLCD(u32 n);

/*---------------------------------------------------------
 Function Name : HexLCD()
 Description   : Displays a number in hexadecimal format.
 Input         : n - Unsigned integer.
----------------------------------------------------------*/
void HexLCD(u32 n);

/*---------------------------------------------------------
 Function Name : ScrollLCD()
 Description   : Scrolls a message across the LCD display.
 Input         : msg - Pointer to the message string.
----------------------------------------------------------*/
void ScrollLCD(const char *msg);

#endif
