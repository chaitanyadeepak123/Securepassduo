#include <stdlib.h>
#include "lcd_defines.h"
#include "lcd.h"
#include "kpm.h"
#include "rtc.h"
#include "delay.h"

/*---------------------------------------------------------
 Function Name : rtc_edit()
 Description   : Displays the RTC editing menu and allows
                 the user to modify RTC parameters such as
                 Hour, Minute, Second, Date, Month, Year,
                 and Weekday using the keypad.
----------------------------------------------------------*/
void rtc_edit()
{
    u8 key1;          // Stores menu selection
    u8 hour;          // Hour (0-23)
    u8 minute;        // Minute (0-59)
    u8 second;        // Second (0-59)
    u8 date;          // Date (1-31)
    u8 month;         // Month (1-12)
    u32 year;         // Year
    u8 week;          // Weekday (0-6)

    while(1)
    {
        /* Display RTC editing menu */
        CmdLCD(CLEAR_LCD);
        CmdLCD(GOTO_LINE1_POS0);
        StrLCD("1.H 2.MI 3.S 4.D");

        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("5.M 6.YR 7.W 8.E");

        /* Read user menu choice */
        key1 = KeyScan();

        switch(key1)
        {
            /*--------------- Edit Hour ----------------*/
            case 1:

                CmdLCD(CLEAR_LCD);
                StrLCD("Enter Hour(0-23)");

                /* Read hour from keypad */
                hour = ReadNumber(23);

                /* Display entered value */
                CharLCD(hour);

                /* Update RTC hour */
                if(hour >= 0 && hour < 23)
                    sethour(hour);

                break;

            /*-------------- Edit Minute ---------------*/
            case 2:

                CmdLCD(CLEAR_LCD);
                StrLCD("MIN EDIT(0-59)");

                minute = ReadNumber(59);

                /* Update RTC minute */
                setminute(minute);

                break;

            /*-------------- Edit Second ---------------*/
            case 3:

                CmdLCD(CLEAR_LCD);
                StrLCD("SEC EDIT(0-59)");

                second = ReadNumber(59);

                /* Update RTC second */
                setsecond(second);

                delay_ms(1000);

                break;

            /*--------------- Edit Date ----------------*/
            case 4:

                CmdLCD(CLEAR_LCD);
                StrLCD("DATE EDIT(0-31)");

                date = ReadNumber(31);

                /* Update RTC date */
                setdate(date);

                delay_ms(1000);

                break;

            /*-------------- Edit Month ----------------*/
            case 5:

                CmdLCD(CLEAR_LCD);
                StrLCD("MONTH EDIT(0-12)");

                month = ReadNumber(12);

                /* Update RTC month */
                setmonth(month);

                delay_ms(1000);

                break;

            /*--------------- Edit Year ----------------*/
            case 6:

                CmdLCD(CLEAR_LCD);
                StrLCD("YEAR EDIT");

                /* Read four-digit year */
                year = Read4Number(4095);

                /* Update RTC year */
                setyear(year);

                delay_ms(1000);

                break;

            /*------------- Edit Weekday ---------------*/
            case 7:

                CmdLCD(CLEAR_LCD);
                StrLCD("WEEK EDIT(0-6)");

                week = ReadNumber(6);

                /* Update RTC weekday */
                SetRTCDay(week);

                delay_ms(1000);

                break;

            /*-------------- Exit RTC Menu -------------*/
            case 8:

                CmdLCD(CLEAR_LCD);

                /* Return to Admin Menu */
                return;

            /*----------- Invalid Menu Option ----------*/
            default:

                StrLCD("INVALID CHOICE");

                break;
        }
    }
}


/*---------------------------------------------------------
 Function Name : adminmode()
 Description   : Displays the Admin Menu and allows the
                 user to enter RTC editing mode or exit
                 back to the main program.
----------------------------------------------------------*/
void adminmode()
{
    u8 key;      // Stores menu option

    while(1)
    {
        /* Display Admin Menu */
        CmdLCD(CLEAR_LCD);

        CmdLCD(GOTO_LINE1_POS0);
        StrLCD("1.RTC 2.EXIT");

        delay_ms(100);

        /* Read keypad input */
        key = KeyScan();

        switch(key)
        {
            /*---------- Enter RTC Editing Menu --------*/
            case 1:

                CmdLCD(CLEAR_LCD);

                StrLCD("RTC EDIT");

                delay_ms(200);

                rtc_edit();

                break;

            /*-------------- Exit Admin Mode ----------*/
            case 2:

                CmdLCD(CLEAR_LCD);

                delay_ms(200);

                return;
        }
    }
}
