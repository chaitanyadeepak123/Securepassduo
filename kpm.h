#ifndef __KPM_H__
#define __KPM_H__

#include "types.h"

/* Initializes the Matrix Keypad by configuring the row pins
   as output pins. */
void InitKPM(void);

/* Scans the keypad columns to detect whether any key
   is pressed.
   Return:
      0 - Key Pressed
      1 - No Key Pressed */
u8 ColScan(void);

/* Identifies the row number of the pressed key.
   Return:
      Row number (0–3) */
u8 RowCheck(void);

/* Identifies the column number of the pressed key.
   Return:
      Column number (0–3) */
u8 ColCheck(void);

/* Scans the keypad and returns the corresponding
   key value from the lookup table. */
u8 KeyScan(void);

/* Reads a numeric value (up to two digits) from the keypad.
   Input:
      max - Maximum allowed value.
   Return:
      Valid number entered by the user. */
u32 ReadNumber(int max);

/* Reads a four-digit numeric value from the keypad.
   Used mainly for entering the RTC year.
   Input:
      max - Maximum allowed value.
   Return:
      Valid four-digit number. */
u32 Read4Number(int max);

#endif
