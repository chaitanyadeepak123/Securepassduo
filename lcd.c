#include "DEFINES.H"
#include "types.h"
#include <lpc21xx.h>
#include "lcd_defines.h"
#include "delay.h"

/*---------------------------------------------------------
 Function Name : WriteLCD()
 Description   : Writes one byte (command or data) to the
                 LCD data bus.
 Input         : data - Byte to be written.
----------------------------------------------------------*/
void WriteLCD(u8 data)
{
    /* Select Write Operation */
    SCLRBIT(IOCLR0,RW);

    /* Place data on LCD data bus */
    WRITEBYTE(IOPIN0,LCD_DATA,data);

    /* Generate Enable Pulse */
    SSETBIT(IOSET0,EN);
    delay_us(1);
    SCLRBIT(IOCLR0,EN);

    /* Wait for LCD internal processing */
    delay_ms(2);
}


/*---------------------------------------------------------
 Function Name : CmdLCD()
 Description   : Sends a command to the LCD.
 Input         : cmd - LCD command.
----------------------------------------------------------*/
void CmdLCD(u8 cmd)
{
    /* Select Command Register */
    SCLRBIT(IOCLR0,RS);

    /* Send command */
    WriteLCD(cmd);
}


/*---------------------------------------------------------
 Function Name : CharLCD()
 Description   : Displays a single ASCII character on LCD.
 Input         : ascii - Character to display.
----------------------------------------------------------*/
void CharLCD(u8 ascii)
{
    /* Select Data Register */
    SSETBIT(IOSET0,RS);

    /* Send character */
    WriteLCD(ascii);
}


/*---------------------------------------------------------
 Function Name : InitLCD()
 Description   : Initializes the 16×2 LCD in 8-bit mode.
                 Configures GPIO pins and sends the required
                 initialization commands.
----------------------------------------------------------*/
void InitLCD(void)
{
    /* Configure LCD Data Pins (P0.8-P0.15) as Outputs */
    WRITEBYTE(IODIR0,LCD_DATA,0xFF);

    /* Configure Control Pins as Outputs */
    SETBIT(IODIR0,RS);
    SETBIT(IODIR0,RW);
    SETBIT(IODIR0,EN);

    delay_ms(15);

    /* LCD Initialization Sequence */
    CmdLCD(MODE_8BIT_1LINE);
    delay_ms(5);

    CmdLCD(MODE_8BIT_1LINE);
    delay_us(100);

    CmdLCD(MODE_8BIT_1LINE);

    CmdLCD(MODE_8BIT_2LINE);
    CmdLCD(DISP_ON_CUR_OFF);
    CmdLCD(CLEAR_LCD);
    CmdLCD(SHIFT_CUR_RIGHT);
}


/*---------------------------------------------------------
 Function Name : StrLCD()
 Description   : Displays a null-terminated string on LCD.
 Input         : str - Pointer to string.
----------------------------------------------------------*/
void StrLCD(u8 *str)
{
    while(*str)
    {
        CharLCD(*str++);
    }
}


/*---------------------------------------------------------
 Function Name : U32LCD()
 Description   : Displays an unsigned 32-bit integer.
 Input         : n - Unsigned integer.
----------------------------------------------------------*/
void U32LCD(u32 n)
{
    u8 a[10];
    s32 i = 0;

    if(n == 0)
    {
        CharLCD('0');
    }
    else
    {
        while(n)
        {
            a[i++] = (n % 10) + '0';
            n /= 10;
        }

        for(--i; i >= 0; i--)
        {
            CharLCD(a[i]);
        }
    }
}


/*---------------------------------------------------------
 Function Name : S32LCD()
 Description   : Displays a signed 32-bit integer.
 Input         : n - Signed integer.
----------------------------------------------------------*/
void S32LCD(s32 n)
{
    if(n < 0)
    {
        CharLCD('-');
        n = -n;
    }

    U32LCD(n);
}


/*---------------------------------------------------------
 Function Name : BinLCD()
 Description   : Displays a number in binary format.
 Input         :
      n   - Number to display.
      nbd - Number of bits.
----------------------------------------------------------*/
void BinLCD(u32 n, u8 nbd)
{
    s32 i;

    for(i = nbd - 1; i >= 0; i--)
    {
        CharLCD(((n >> i) & 1) + '0');
    }
}


/*---------------------------------------------------------
 Function Name : BuildCGRAM()
 Description   : Creates custom characters in LCD CGRAM.
 Input         :
      p      - Pointer to character pattern.
      nBytes - Number of bytes.
----------------------------------------------------------*/
void BuildCGRAM(u8 *p, u8 nBytes)
{
    s32 i;

    /* Select CGRAM */
    CmdLCD(GOTO_CGRAM);

    /* Write custom character data */
    for(i = 0; i < nBytes; i++)
    {
        CharLCD(p[i]);
    }

    /* Return to DDRAM */
    CmdLCD(GOTO_LINE2_POS0);
}


/*---------------------------------------------------------
 Function Name : f32LCD()
 Description   : Displays a floating-point number with
                 specified decimal places.
 Input         :
      fnum - Floating-point number.
      ndp  - Number of decimal places.
----------------------------------------------------------*/
void f32LCD(f32 fnum, u8 ndp)
{
    u32 inum;

    if(fnum < 0.0)
    {
        CharLCD('-');
        fnum = -fnum;
    }

    inum = fnum;

    U32LCD(inum);

    CharLCD('.');

    while(ndp)
    {
        fnum = (fnum - inum) * 10;

        inum = fnum;

        CharLCD(inum + '0');

        ndp--;
    }
}


/*---------------------------------------------------------
 Function Name : HexLCD()
 Description   : Displays a number in hexadecimal format.
 Input         : n - Unsigned integer.
----------------------------------------------------------*/
void HexLCD(u32 n)
{
    u8 a[8], rem;
    s32 i = 0;

    if(n == 0)
    {
        CharLCD('0');
    }
    else
    {
        while(n)
        {
            rem = n % 16;

            (rem < 10) ? (rem += '0') : (rem += 55);

            a[i++] = rem;

            n /= 16;
        }

        for(--i; i >= 0; i--)
        {
            CharLCD(a[i]);
        }
    }
}


/*---------------------------------------------------------
 Function Name : OctLCD()
 Description   : Displays a number in octal format.
 Input         : n - Unsigned integer.
----------------------------------------------------------*/
void OctLCD(u32 n)
{
    s32 i = 0;
    u8 a[12];

    if(n == 0)
    {
        CharLCD('0');
    }
    else
    {
        while(n)
        {
            a[i++] = (n % 8) + '0';

            n /= 8;
        }

        for(--i; i >= 0; i--)
        {
            CharLCD(a[i]);
        }
    }
}
