#include "defines.h"
#include "lcd_defines.h"
#include "delay.h"
#include <lpc21xx.h>
#include "types.h"
#include "lcd.h"
#include "kpm.h"

/*---------------------------------------------------------
 Keypad Lookup Table
 Maps Row and Column positions to corresponding key values.

 Layout:
      C0   C1   C2   C3
R0 -> 1    2    3    +
R1 -> 4    5    6    -
R2 -> 7    8    9    *
R3 -> BS   0   ENT  EXIT

 BS   = Backspace (15)
 ENT  = Enter (16)
----------------------------------------------------------*/
u8 KpmLUT[4][4] =
{
    {1,2,3,'+'},
    {4,5,6,'-'},
    {7,8,9,'*'},
    {10,0,15,16}
};

/*---------------------------------------------------------
 Function Name : InitKPM()

 Description   : Configures keypad row pins (P1.16-P1.19)
                 as output pins.
----------------------------------------------------------*/
void InitKPM(void)
{
    // Configure Row Pins as Outputs
    WRITENIBBLE(IODIR1,ROW0,15);
}


/*---------------------------------------------------------
 Function Name : ColScan()

 Description   : Checks whether any key is pressed by
                 reading the column pins.

 Return :
     0 -> Key Pressed
     1 -> No Key Pressed
----------------------------------------------------------*/
u8 ColScan(void)
{
    if((READNIBBLE(IOPIN1,COL0)) < 15)
        return 0;
    else
        return 1;
}


/*---------------------------------------------------------
 Function Name : RowCheck()

 Description   : Identifies the row in which the key
                 has been pressed.

 Return :
      Row Number (0-3)
----------------------------------------------------------*/
u8 RowCheck(void)
{
    u8 rno;

    for(rno = 0; rno <= 3; rno++)
    {
        // Activate one row at a time
        WRITENIBBLE(IOPIN1,ROW0,~(1<<rno));

        if(ColScan() == 0)
        {
            break;
        }
    }

    // Disable all rows
    WRITENIBBLE(IOPIN1,ROW0,0x0);

    return rno;
}


/*---------------------------------------------------------
 Function Name : ColCheck()

 Description   : Identifies which column contains the
                 pressed key.

 Return :
      Column Number (0-3)
----------------------------------------------------------*/
u8 ColCheck(void)
{
    u8 cno;

    for(cno = 0; cno <= 3; cno++)
    {
        if(STATUSBIT(IOPIN1,(COL0+cno)) == 0)
        {
            break;
        }
    }

    return cno;
}


/*---------------------------------------------------------
 Function Name : KeyScan()

 Description   : Detects a key press and returns the
                 corresponding key value from the lookup
                 table.

 Return :
      Key Value
----------------------------------------------------------*/
u8 KeyScan(void)
{
    u8 keyv;
    u8 rno;
    u8 cno;

    // Wait until any key is pressed
    while(ColScan());

    // Identify row
    rno = RowCheck();

    // Identify column
    cno = ColCheck();

    // Read key value from lookup table
    keyv = KpmLUT[rno][cno];

    // Wait until key is released
    while(!ColScan());

    return keyv;
}


/*---------------------------------------------------------
 Function Name : ReadNumber()

 Description   : Reads a two-digit number from the keypad.
                 Supports Backspace and Enter keys.
                 Ensures the entered value does not exceed
                 the specified maximum value.

 Input :
      max - Maximum allowed number

 Return :
      Valid number entered by the user
----------------------------------------------------------*/
u32 ReadNumber(int max)
{
    s8 k;
    u32 num = 0;
    u32 cnt = 0;

    CmdLCD(GOTO_LINE2_POS0);

    while(1)
    {
        // Read keypad value
        k = KeyScan();

        /* Numeric Keys */
        if(k >= 0 && k <= 9)
        {
            if(cnt < 2)
            {
                num = (num * 10) + k;

                // Display digit on LCD
                CharLCD(k + '0');

                cnt++;
            }
        }

        /* Backspace Key */
        else if(k == 15)
        {
            if(cnt > 0)
            {
                // Remove last digit
                num = num / 10;

                cnt--;

                // Erase character on LCD
                CmdLCD(0x10);
                CharLCD(' ');
                CmdLCD(0x10);
            }
        }

        /* Enter Key */
        else if(k == 16)
        {
            // No input entered
            if(cnt == 0)
            {
                CmdLCD(CLEAR_LCD);

                StrLCD("NO INPUT");

                delay_ms(1000);

                CmdLCD(CLEAR_LCD);

                StrLCD("ENTER AGAIN");

                CmdLCD(GOTO_LINE2_POS0);

                continue;
            }

            // Validate entered number
            if(num <= max)
            {
                return num;
            }
            else
            {
                CmdLCD(CLEAR_LCD);

                StrLCD("INVALID");

                delay_ms(1000);

                CmdLCD(CLEAR_LCD);

                StrLCD("TRY AGAIN");

                num = 0;
                cnt = 0;

                CmdLCD(GOTO_LINE2_POS0);
            }
        }
    }
}


/*---------------------------------------------------------
 Function Name : Read4Number()

 Description   : Reads a four-digit number from the keypad.
                 Supports Backspace and Enter keys.
                 Used mainly for entering the RTC year.

 Input :
      max - Maximum allowed number

 Return :
      Valid four-digit number
----------------------------------------------------------*/
u32 Read4Number(int max)
{
    s8 k;
    u32 num = 0;
    u32 cnt = 0;

    CmdLCD(GOTO_LINE2_POS0);

    while(1)
    {
        // Read keypad value
        k = KeyScan();

        /* Numeric Keys */
        if(k >= 0 && k <= 9)
        {
            if(cnt < 4)
            {
                num = (num * 10) + k;

                CharLCD(k + '0');

                cnt++;
            }
        }

        /* Backspace Key */
        else if(k == 15)
        {
            if(cnt > 0)
            {
                num = num / 10;

                cnt--;

                CmdLCD(0x10);
                CharLCD(' ');
                CmdLCD(0x10);
            }
        }

        /* Enter Key */
        else if(k == 16)
        {
            if(num <= max && cnt > 0)
            {
                return num;
            }
            else
            {
                CmdLCD(CLEAR_LCD);

                StrLCD("INVALID");

                delay_ms(1000);

                CmdLCD(CLEAR_LCD);

                StrLCD("TRY AGAIN");

                num = 0;
                cnt = 0;

                CmdLCD(GOTO_LINE2_POS0);
            }
        }
    }
}
