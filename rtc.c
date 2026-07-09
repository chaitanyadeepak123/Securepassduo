#include <lpc214x.h>
#include "types.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "rtc.h"

/*---------------------------------------------------------
 System Clock Configuration
----------------------------------------------------------*/

/* Oscillator Frequency (12 MHz Crystal) */
#define FOSC            12000000

/* CPU Clock Frequency */
#define CCLK            (5 * FOSC)

/* Peripheral Clock Frequency */
#define PCLK            (CCLK / 4)

/* RTC Prescaler Integer Value */
#define PREINT_VAL      (int)((PCLK / 32768) - 1)

/* RTC Prescaler Fractional Value */
#define PREFRAC_VAL     (PCLK - ((PREINT_VAL + 1) * 32768))


/*---------------------------------------------------------
 RTC Control Register Bit Definitions
----------------------------------------------------------*/

/* Enable RTC Counter */
#define RTC_ENABLE      (1 << 0)

/* Reset RTC Counter */
#define RTC_RESET       (1 << 1)

/* Select External RTC Clock Source */
#define RTC_CLKSRC      (1 << 4)


/*---------------------------------------------------------
 Day of Week Definitions
----------------------------------------------------------*/

#define SUN     0
#define MON     1
#define TUE     2
#define WED     3
#define THU     4
#define FRI     5
#define SAT     6


/* Define LPC2148 Device */
#define _LPC2148


/*---------------------------------------------------------
 Function Name : RTC_Init()

 Description   : Initializes the RTC module by enabling
                 the RTC clock and configuring the
                 prescaler values if required.
----------------------------------------------------------*/
void RTC_Init(void)
{
    /* Reset RTC */
    CCR = RTC_RESET;

#ifndef _LPC2148

    /* Configure RTC Prescalers */
    PREINT = PREINT_VAL;
    PREFRAC = PREFRAC_VAL;

    /* Enable RTC */
    CCR = RTC_ENABLE;

#else

    /* Enable RTC using external clock source */
    CCR = RTC_ENABLE | RTC_CLKSRC;

#endif
}


/*---------------------------------------------------------
 Weekday String Table
----------------------------------------------------------*/
char week[][4] =
{
    "SUN",
    "MON",
    "TUE",
    "WED",
    "THU",
    "FRI",
    "SAT"
};


/*---------------------------------------------------------
 Function Name : GetRTCTimeInfo()

 Description   : Reads the current RTC time.

 Input         :
      hour - Pointer to hour variable
      min  - Pointer to minute variable
      sec  - Pointer to second variable
----------------------------------------------------------*/
void GetRTCTimeInfo(s32 *hour, s32 *min, s32 *sec)
{
    *hour = HOUR;
    *min  = MIN;
    *sec  = SEC;
}


/*---------------------------------------------------------
 Function Name : DisplayRTCTime()

 Description   : Displays the current time on the LCD
                 in HH:MM:SS format.

 Input :
      hour, min, sec
----------------------------------------------------------*/
void DisplayRTCTime(u32 hour, u32 min, u32 sec)
{
    CmdLCD(GOTO_LINE1_POS0);

    CharLCD(hour/10 + '0');
    CharLCD(hour%10 + '0');
    CharLCD(':');

    CharLCD(min/10 + '0');
    CharLCD(min%10 + '0');
    CharLCD(':');

    CharLCD(sec/10 + '0');
    CharLCD(sec%10 + '0');
}


/*---------------------------------------------------------
 Function Name : GetRTCDateInfo()

 Description   : Reads the current RTC date.

 Input :
      date
      month
      year
----------------------------------------------------------*/
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
    *date  = DOM;
    *month = MONTH;
    *year  = YEAR;
}


/*---------------------------------------------------------
 Function Name : DisplayRTCDate()

 Description   : Displays the current date on the LCD
                 in DD/MM/YYYY format.

 Input :
      date
      month
      year
----------------------------------------------------------*/
void DisplayRTCDate(u32 date, u32 month, u32 year)
{
    CmdLCD(GOTO_LINE2_POS0);

    CharLCD(date/10 + '0');
    CharLCD(date%10 + '0');

    CharLCD('/');

    CharLCD(month/10 + '0');
    CharLCD(month%10 + '0');

    CharLCD('/');

    U32LCD(year);
}


/*---------------------------------------------------------
 Function Name : SetRTCTimeInfo()

 Description   : Sets Hour, Minute and Second registers.

 Input :
      hour
      min
      sec
----------------------------------------------------------*/
void SetRTCTimeInfo(u32 hour, u32 min, u32 sec)
{
    HOUR = hour;
    MIN  = min;
    SEC  = sec;
}


/*---------------------------------------------------------
 Function Name : SetRTCDateInfo()

 Description   : Sets Date, Month and Year registers.

 Input :
      date
      month
      year
----------------------------------------------------------*/
void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
    DOM   = date;
    MONTH = month;
    YEAR  = year;
}


/*---------------------------------------------------------
 Function Name : GetRTCDay()

 Description   : Reads the current Day of Week.

 Input :
      dow - Pointer to weekday variable.
----------------------------------------------------------*/
void GetRTCDay(s32 *dow)
{
    *dow = DOW;
}


/*---------------------------------------------------------
 Function Name : DisplayRTCDay()

 Description   : Displays the day of the week on the LCD.

 Input :
      dow - Day Number (0-6)
----------------------------------------------------------*/
void DisplayRTCDay(u32 dow)
{
    CmdLCD(GOTO_LINE1_POS0 + 10);

    StrLCD(week[dow]);
}


/*---------------------------------------------------------
 Function Name : SetRTCDay()

 Description   : Updates the RTC Day of Week register.

 Input :
      dow - Day Number (0-6)
----------------------------------------------------------*/
void SetRTCDay(u32 dow)
{
    DOW = dow;
}


/*---------------------------------------------------------
 Function Name : sethour()

 Description   : Updates the RTC Hour register.
----------------------------------------------------------*/
void sethour(u32 hour)
{
    HOUR = hour;
}


/*---------------------------------------------------------
 Function Name : setminute()

 Description   : Updates the RTC Minute register.
----------------------------------------------------------*/
void setminute(u32 minute)
{
    MIN = minute;
}


/*---------------------------------------------------------
 Function Name : setsecond()

 Description   : Updates the RTC Second register.
----------------------------------------------------------*/
void setsecond(u32 second)
{
    SEC = second;
}


/*---------------------------------------------------------
 Function Name : setdate()

 Description   : Updates the RTC Date register.
----------------------------------------------------------*/
void setdate(u32 date)
{
    DOM = date;
}


/*---------------------------------------------------------
 Function Name : setmonth()

 Description   : Updates the RTC Month register.
----------------------------------------------------------*/
void setmonth(u32 month)
{
    MONTH = month;
}


/*---------------------------------------------------------
 Function Name : setweek()

 Description   : Updates the RTC Day of Week register.
----------------------------------------------------------*/
void setweek(u32 week)
{
    DOW = week;
}


/*---------------------------------------------------------
 Function Name : setyear()

 Description   : Updates the RTC Year register.
----------------------------------------------------------*/
void setyear(u32 year)
{
    YEAR = year;
}
