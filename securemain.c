#include <stdio.h>
#include <lpc21xx.h>
#include <string.h>
#include "lcd.h"
#include "rtc.h"
#include "uart_interuppt.h"
#include "gsm.h"
#include "kpm.h"
#include "delay.h"

/*---------------------------------------------------------
 Global Variables
----------------------------------------------------------*/

/* Valid RFID Tag Number */
char vaildtag[] = "12603355";

/* RTC Variables */
s32 hour, min, sec;
s32 date, month, year, day;

/* OTP Variables */
char otp[5];
char enter_otp[5];

/* OTP Generation and Validation Time */
s32 otp_time;
s32 now_time;

/* Wrong OTP Attempt Counter */
int attempts;

/* Function Prototypes */
void generate_otp(void);
void send_otp(void);
int validate_otp(void);
int check_otp(void);


/*---------------------------------------------------------
 Function Name : main()

 Description   : Initializes all peripherals and executes
                 the main authentication process.

 Flow:
   1. Initialize LCD, UART, RTC, GSM and Keypad.
   2. Wait for RFID card.
   3. Validate RFID.
   4. Generate OTP.
   5. Send OTP through GSM.
   6. Verify OTP.
   7. Open Door if OTP is valid.
----------------------------------------------------------*/
int main()
{
    /* Configure Door Lock Pin as Output */
    IODIR0 |= (1 << 12);

    /* Initialize UART0 (GSM) */
    InitUART0();

    /* Initialize UART1 (RFID) */
    InitUART1();

    /* Initialize LCD */
    InitLCD();

    /* Initialize RTC */
    RTC_Init();

    /* Initialize GSM Module */
    gsm_init();

    /* Initialize Matrix Keypad */
    InitKPM();

    /* Enable External Interrupt */
    enable_ent1();

    while(1)
    {
        /* Reset RFID Receive Flag */
        r_flag = 0;

        /* Wait until RFID tag is received */
        do
        {
            /* Read Current RTC Information */
            GetRTCTimeInfo(&hour,&min,&sec);
            GetRTCDateInfo(&date,&month,&year);
            GetRTCDay(&day);

            /* Display RTC Information */
            DisplayRTCTime(hour,min,sec);
            DisplayRTCDate(date,month,year);
            DisplayRTCDay(day);

        } while(r_flag1 != 2);

        /* Display Received RFID Tag */
        CmdLCD(CLEAR_LCD);
        StrLCD("RFID TAG:");

        CmdLCD(GOTO_LINE2_POS0);
        StrLCD(buff1);

        delay_ms(2000);

        CmdLCD(CLEAR_LCD);

        r_flag1 = 0;

        /* Compare RFID Tag with Stored Tag */
        if(strcmp(vaildtag,buff1) == 0)
        {
            CmdLCD(CLEAR_LCD);

            StrLCD("VALID TAG");

            delay_ms(1000);

            /* Record OTP Generation Time */
            GetRTCTimeInfo(&hour,&min,&sec);

            otp_time = (hour * 3600) + (min * 60) + sec;

            /* Generate OTP */
            generate_otp();

            /* Send OTP to User */
            send_otp();

            attempts = 0;

            /* Allow Maximum Three Attempts */
            while(attempts < 3)
            {
                /* Validate Entered OTP */
                if(validate_otp())
                {
                    /* Check OTP Expiry */
                    if(check_otp())
                    {
                        CmdLCD(CLEAR_LCD);
                        StrLCD("ACCESS GRANTED");

                        delay_ms(500);

                        CmdLCD(CLEAR_LCD);
                        StrLCD("DOOR OPEN");

                        /* Activate Door Lock */
                        IOSET0 = (1 << 12);

                        delay_ms(500);

                        CmdLCD(CLEAR_LCD);
                        StrLCD("DOOR CLOSE");

                        /* Close Door */
                        IOCLR0 = (1 << 12);

                        delay_ms(2000);

                        break;
                    }
                    else
                    {
                        CmdLCD(CLEAR_LCD);

                        StrLCD("OTP EXPIRED");

                        delay_ms(1000);

                        break;
                    }
                }
                else
                {
                    attempts++;

                    CmdLCD(CLEAR_LCD);

                    StrLCD("WRONG OTP");

                    delay_ms(500);

                    /* Maximum Attempts Reached */
                    if(attempts >= 3)
                    {
                        CmdLCD(CLEAR_LCD);

                        StrLCD("ACCESS DENIED");

                        delay_ms(2000);
                    }
                }
            }
        }
        else
        {
            /* Invalid RFID Tag */
            CmdLCD(CLEAR_LCD);

            StrLCD("INVALID CARD");

            delay_ms(500);
        }

        CmdLCD(CLEAR_LCD);
    }
}


/*---------------------------------------------------------
 Function Name : generate_otp()

 Description   : Generates a four-digit OTP using the
                 current RTC time.
----------------------------------------------------------*/
void generate_otp(void)
{
    otp[0] = (hour % 10) + '0';
    otp[1] = (min % 10) + '0';
    otp[2] = (sec % 10) + '0';
    otp[3] = ((hour + min + sec) % 10) + '0';

    otp[4] = '\0';
}


/*---------------------------------------------------------
 Function Name : send_otp()

 Description   : Sends the generated OTP to the user's
                 mobile number using the GSM module.
----------------------------------------------------------*/
void send_otp(void)
{
    if(gsm_flag == 1)
    {
        /* Send SMS Command */
        UART0_Str("AT+CMGS=\"8096261977\"\r\n");

        delay_ms(1000);

        /* Send OTP Message */
        UART0_Str("YOUR OTP IS: ");

        UART0_Str(otp);

        UART0_Str(" Valid for 3 mins");

        /* End SMS Transmission */
        UART0_Tx(0x1A);

        delay_ms(1000);
    }
}


/*---------------------------------------------------------
 Function Name : validate_otp()

 Description   : Reads OTP entered from keypad and compares
                 it with the generated OTP.

 Return :
      1 -> OTP Correct
      0 -> OTP Incorrect
----------------------------------------------------------*/
int validate_otp(void)
{
    int i = 0;

    u8 key;

    CmdLCD(CLEAR_LCD);

    CmdLCD(GOTO_LINE1_POS0);

    StrLCD("ENTER OTP");

    CmdLCD(GOTO_LINE2_POS0);

    while(1)
    {
        if(ColScan() == 1)
        {
            key = KeyScan();

            /* Backspace */
            if(key == 10)
            {
                if(i > 0)
                {
                    i--;

                    enter_otp[i] = '\0';

                    CmdLCD(0xC0 + i);

                    CharLCD(' ');

                    CmdLCD(0xC0 + i);
                }
            }

            /* Enter Key */
            else if(key == 16)
            {
                if(i == 4)
                    break;
            }

            /* Numeric Keys */
            else
            {
                if(i < 4)
                {
                    enter_otp[i] = key + '0';

                    CharLCD(key + '0');

                    i++;
                }
            }
        }
    }

    enter_otp[4] = '\0';

    /* Compare OTP */
    if(strcmp(otp, enter_otp) == 0)
        return 1;

    return 0;
}


/*---------------------------------------------------------
 Function Name : check_otp()

 Description   : Checks whether the OTP is still valid.

 Return :
      1 -> OTP Valid
      0 -> OTP Expired
----------------------------------------------------------*/
int check_otp(void)
{
    /* Read Current RTC Time */
    GetRTCTimeInfo(&hour,&min,&sec);

    now_time = (hour * 3600) + (min * 60) + sec;

    /* OTP Validity Check (60 Seconds) */
    if((now_time - otp_time) > 60)
    {
        return 0;
    }

    return 1;
}
