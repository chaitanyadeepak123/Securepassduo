#include <LPC214x.H>          /* LPC2148 Register Definitions */
#include "uart_interuppt.h"
#include <string.h>
#include <time.h>
#include "lcd.h"
#include "rtc.h"

#define UART_INT_ENABLE 1      /* Enable UART Interrupt */

/*---------------------------------------------------------
 Global Variables
----------------------------------------------------------*/

/* UART Receive Buffer */
char buff[200];

/* Dummy variable used to clear interrupt */
char dummy;

/* UART Variables */
unsigned char i = 0;      /* Buffer Index */
unsigned char ch;          /* Received Character */
unsigned char r_flag;      /* Reception Complete Flag */


/*---------------------------------------------------------
 Function Name : UART0_isr()

 Description   : UART0 Interrupt Service Routine.
                 Receives incoming characters and stores
                 them into the receive buffer until a
                 carriage return (0x0D) is detected.
----------------------------------------------------------*/
void UART0_isr(void) __irq
{
    /* Check Receive Interrupt */
    if(U0IIR & 0x04)
    {
        /* Read received character */
        ch = U0RBR;

        /* Ignore Carriage Return */
        if(ch != 0x0D)
        {
            buff[i++] = ch;
        }
        else if(i > 7)
        {
            /* End of RFID Tag */
            buff[8] = '\0';

            i = 0;

            /* Set Receive Complete Flag */
            r_flag = 1;
        }
    }
    else
    {
        /* Clear Transmit Interrupt */
        dummy = U0IIR;
    }

    /* Notify VIC that ISR execution is complete */
    VICVectAddr = 0;
}


/*---------------------------------------------------------
 Function Name : InitUART0()

 Description   : Initializes UART0 for serial communication.
                 Configures:
                    • 9600 Baud Rate
                    • 8 Data Bits
                    • No Parity
                    • 1 Stop Bit
                    • UART Interrupt
----------------------------------------------------------*/
void InitUART0(void)
{
    /* Configure P0.0 as TxD0 and P0.1 as RxD0 */
    PINSEL0 = 0x00000005;

    /* 8-bit Data, No Parity, 1 Stop Bit */
    U0LCR = 0x83;

    /* Baud Rate = 9600 */
    U0DLL = 97;

    /* Disable Divisor Latch Access */
    U0LCR = 0x03;

#if UART_INT_ENABLE > 0

    /* Configure UART0 Interrupt */
    VICIntSelect = 0x00000000;

    VICVectAddr0 = (unsigned)UART0_isr;

    VICVectCntl0 = 0x20 | 6;

    VICIntEnable = (1 << 6);

    /* Enable Receive and THRE Interrupts */
    U0IER = 0x03;

#endif
}


/*---------------------------------------------------------
 Function Name : UART0_Tx()

 Description   : Transmits one character through UART0.

 Input :
      ch - Character to transmit.
----------------------------------------------------------*/
void UART0_Tx(char ch)
{
    /* Wait until transmitter is ready */
    while(!(U0LSR & 0x20));

    /* Send character */
    U0THR = ch;
}


/*---------------------------------------------------------
 Function Name : UART0_Rx()

 Description   : Receives one character through UART0.

 Return :
      Received Character
----------------------------------------------------------*/
char UART0_Rx(void)
{
    /* Wait until data is received */
    while(!(U0LSR & 0x01));

    return U0RBR;
}


/*---------------------------------------------------------
 Function Name : UART0_Str()

 Description   : Sends a null-terminated string through
                 UART0.

 Input :
      s - Pointer to string.
----------------------------------------------------------*/
void UART0_Str(char *s)
{
    while(*s)
    {
        UART0_Tx(*s++);
    }
}


/*---------------------------------------------------------
 Function Name : UART0_Int()

 Description   : Sends an unsigned integer through UART0.

 Input :
      n - Integer to transmit.
----------------------------------------------------------*/
void UART0_Int(unsigned int n)
{
    unsigned char a[10] = {0};

    int i = 0;

    if(n == 0)
    {
        UART0_Tx('0');

        return;
    }

    while(n > 0)
    {
        a[i++] = (n % 10) + '0';

        n /= 10;
    }

    while(--i >= 0)
    {
        UART0_Tx(a[i]);
    }
}


/*---------------------------------------------------------
 Function Name : UART0_Float()

 Description   : Sends a floating-point number through
                 UART0.

 Input :
      f - Floating-point value.
----------------------------------------------------------*/
void UART0_Float(float f)
{
    int x;

    float temp;

    x = f;

    UART0_Int(x);

    UART0_Tx('.');

    temp = (f - x) * 100;

    x = temp;

    UART0_Int(x);
}


/*---------------------------------------------------------
 Function Name : DelayS()

 Description   : Generates an approximate software delay
                 in seconds.

 Input :
      dly - Delay in seconds.
----------------------------------------------------------*/
void DelayS(unsigned int dly)
{
    unsigned int i;

    for(; dly > 0; dly--)
    {
        for(i = 1200000; i > 0; i--);
    }
}


/**************************************************************
 The code below is a sample test program (currently commented)
 demonstrating RFID tag reading, OTP generation using RTC
 values, and displaying authentication status on the LCD.
 It can be used for testing UART-RFID communication and
 OTP generation during development.
**************************************************************/
