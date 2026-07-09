#ifndef _RTC_H
#define _RTC_H

#include "types.h"

/*---------------------------------------------------------
 Function Name : RTC_Init()
 Description   : Initializes the Real Time Clock (RTC)
                 module of the LPC2148.
----------------------------------------------------------*/
void RTC_Init(void);

/*---------------------------------------------------------
 Function Name : GetRTCTimeInfo()
 Description   : Reads the current RTC time.

 Parameters :
      hour - Pointer to hour variable.
      min  - Pointer to minute variable.
      sec  - Pointer to second variable.
----------------------------------------------------------*/
void GetRTCTimeInfo(s32 *hour, s32 *min, s32 *sec);

/*---------------------------------------------------------
 Function Name : DisplayRTCTime()
 Description   : Displays the RTC time on the LCD in
                 HH:MM:SS format.
----------------------------------------------------------*/
void DisplayRTCTime(u32 hour, u32 min, u32 sec);

/*---------------------------------------------------------
 Function Name : GetRTCDateInfo()
 Description   : Reads the current RTC date.

 Parameters :
      date  - Pointer to date variable.
      month - Pointer to month variable.
      year  - Pointer to year variable.
----------------------------------------------------------*/
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year);

/*---------------------------------------------------------
 Function Name : DisplayRTCDate()
 Description   : Displays the RTC date on the LCD in
                 DD/MM/YYYY format.
----------------------------------------------------------*/
void DisplayRTCDate(u32 date, u32 month, u32 year);

/*---------------------------------------------------------
 Function Name : SetRTCTimeInfo()
 Description   : Sets the RTC time by updating the
                 Hour, Minute, and Second registers.
----------------------------------------------------------*/
void SetRTCTimeInfo(u32 hour, u32 min, u32 sec);

/*---------------------------------------------------------
 Function Name : SetRTCDateInfo()
 Description   : Sets the RTC date by updating the
                 Date, Month, and Year registers.
----------------------------------------------------------*/
void SetRTCDateInfo(u32 date, u32 month, u32 year);

/*---------------------------------------------------------
 Function Name : GetRTCDay()
 Description   : Reads the current day of the week.

 Parameter :
      dow - Pointer to day variable.
----------------------------------------------------------*/
void GetRTCDay(s32 *dow);

/*---------------------------------------------------------
 Function Name : DisplayRTCDay()
 Description   : Displays the current day of the week
                 on the LCD.
----------------------------------------------------------*/
void DisplayRTCDay(u32 dow);

/*---------------------------------------------------------
 Function Name : SetRTCDay()
 Description   : Updates the RTC Day of Week register.
----------------------------------------------------------*/
void SetRTCDay(u32 dow);

/*---------------------------------------------------------
 Function Name : sethour()
 Description   : Updates the RTC Hour register.
----------------------------------------------------------*/
void sethour(u32 hour);

/*---------------------------------------------------------
 Function Name : setminute()
 Description   : Updates the RTC Minute register.
----------------------------------------------------------*/
void setminute(u32 minute);

/*---------------------------------------------------------
 Function Name : setsecond()
 Description   : Updates the RTC Second register.
----------------------------------------------------------*/
void setsecond(u32 second);

/*---------------------------------------------------------
 Function Name : setdate()
 Description   : Updates the RTC Date register.
----------------------------------------------------------*/
void setdate(u32 date);

/*---------------------------------------------------------
 Function Name : setmonth()
 Description   : Updates the RTC Month register.
----------------------------------------------------------*/
void setmonth(u32 month);

/*---------------------------------------------------------
 Function Name : setweek()
 Description   : Updates the RTC Day of Week register.
----------------------------------------------------------*/
void setweek(u32 week);

/*---------------------------------------------------------
 Function Name : setyear()
 Description   : Updates the RTC Year register.
----------------------------------------------------------*/
void setyear(u32 year);

#endif
