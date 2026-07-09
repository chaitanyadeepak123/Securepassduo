#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "delay.h"
#include "uart_interuppt.h"
#include "lcd.h"
#include "lcd_defines.h"

/*---------------------------------------------------------
 Global Variables
----------------------------------------------------------*/
extern char buff[200];        // UART receive buffer
extern unsigned char i;       // Buffer index

u32 cnt;                      // Timeout counter
int gsm_flag;                 // GSM status flag
                               // 1 = Connected
                               // 0 = Not Connected


/*---------------------------------------------------------
 Function Name : gsm_init()

 Description   : Initializes the GSM module by sending
                 AT commands through UART. The function
                 checks whether the GSM module is
                 responding correctly and configures it
                 for SMS Text Mode.

 Initialization Sequence:
    1. Send "AT"
    2. Disable command echo (ATE0)
    3. Enable SMS Text Mode (AT+CMGF=1)

 Return        : None
----------------------------------------------------------*/
void gsm_init(void)
{
    /*---------------- Send AT Command ----------------*/

    CmdLCD(0x01);                     // Clear LCD
    CmdLCD(0x80);                     // Move cursor to Line 1
    StrLCD("AT");                     // Display command

    delay_ms(100);

    /* Send AT command to GSM module */
    UART0_Str("AT\r\n");

    /* Clear UART receive buffer */
    i = 0;
    memset(buff, '\0', 200);

    /* Wait for GSM response or timeout */
    while(cnt < 5000)
    {
        if(strstr(buff, "OK"))
            break;

        if(i > 0)
            break;

        delay_ms(1);
        cnt++;
    }

    delay_ms(500);

    buff[i] = '\0';

    /* Display received response */
    CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD(buff);

    delay_ms(2000);

    /* Check timeout */
    if(cnt >= 5000)
    {
        StrLCD("Gsm not connected");

        gsm_flag = 0;

        delay_ms(500);

        CmdLCD(0x01);

        return;
    }

    /* Verify GSM response */
    if(strstr(buff, "OK"))
    {
        CmdLCD(0xC0);
        StrLCD("OK");

        delay_ms(1000);
    }
    else
    {
        CmdLCD(0xC0);
        StrLCD("ERROR");

        delay_ms(1000);

        return;
    }


    /*---------------- Disable Echo ----------------*/

    CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD("ATE0");

    delay_ms(1000);

    /* Disable command echo */
    UART0_Str("ATE0\r\n");

    i = 0;
    memset(buff, '\0', 200);

    while(cnt < 5000)
    {
        if(strstr(buff, "OK"))
            break;

        if(i > 0)
            break;

        delay_ms(1);
        cnt++;
    }

    delay_ms(500);

    buff[i] = '\0';

    CmdLCD(0x02);
    CmdLCD(0x80);
    StrLCD(buff);

    delay_ms(2000);

    if(cnt >= 5000)
    {
        StrLCD("Gsm not connected");

        gsm_flag = 0;

        delay_ms(500);

        CmdLCD(0x01);

        return;
    }

    if(strstr(buff, "OK"))
    {
        CmdLCD(0xC0);
        StrLCD("OK");

        delay_ms(1000);
    }
    else
    {
        CmdLCD(0xC0);
        StrLCD("ERROR");

        delay_ms(1000);

        return;
    }


    /*------------- Enable SMS Text Mode -------------*/

    CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD("AT+CMGF=1");

    delay_ms(1000);

    /* Configure GSM for SMS Text Mode */
    UART0_Str("AT+CMGF=1\r\n");

    i = 0;
    memset(buff, '\0', 200);

    while(cnt < 5000)
    {
        if(strstr(buff, "OK"))
            break;

        if(i > 0)
            break;

        delay_ms(1);
        cnt++;
    }

    delay_ms(500);

    buff[i] = '\0';

    CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD(buff);

    delay_ms(2000);

    if(cnt >= 5000)
    {
        StrLCD("Gsm not connected");

        gsm_flag = 0;

        delay_ms(500);

        CmdLCD(0x01);

        return;
    }

    if(strstr(buff, "OK"))
    {
        CmdLCD(0xC0);
        StrLCD("OK");

        delay_ms(1000);
    }
    else
    {
        CmdLCD(0xC0);
        StrLCD("ERROR");

        delay_ms(1000);

        return;
    }

    /* GSM Initialization Successful */
    gsm_flag = 1;
}
