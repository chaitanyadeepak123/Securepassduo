#include <LPC214x.H>          /* LPC2148 Register Definitions */
#include "uart_interuppt.h"
#include <string.h>
#include <time.h>
#include "lcd.h"
#include "rtc.h"

#define UART_INT_ENABLE 1     /* Enable UART1 Interrupt */

/*---------------------------------------------------------
 Global Variables
----------------------------------------------------------*/

/* UART1 Receive Buffer */
char buff1[200];

/* Dummy variable used to clear interrupt */
char dummy1;

/* UART1 Variables */
unsigned char i1 = 0;         /* Receive Buffer Index */
unsigned char ch1;            /* Received Character */
unsigned char r_flag1;        /* RFID Reception Status Flag */


/*---------------------------------------------------------
 Function Name : UART1_isr()

 Description   : UART1 Interrupt Service Routine.
                 Receives RFID tag data from UART1 and stores
                 it in the receive buffer. The RFID frame
                 starts with STX (0x02) and ends with ETX
                 (0x03).

                 r_flag1 Status:
                 0 -> Waiting for RFID
                 1 -> Receiving RFID Data
                 2 -> RFID Reception Completed
----------------------------------------------------------*/
void UART1_isr(void) __irq
{
    /* Check Receive Interrupt */
    if(U1IIR & 0x04)
    {
        /* Read Received Character */
        ch1 = U1RBR;

        /* Start of RFID Frame (STX) */
        if(ch1 == 0x02)
        {
            r_flag1 = 1;
        }

        /* Store RFID Data */
        else if((ch1 != 0x03) && (r_flag1 == 1))
        {
            buff1[i1++] = ch1;
        }

        /* End of RFID Frame (ETX) */
        else
        {
            buff1[i1] = '\0';

            i1 = 0;

            r_flag1 = 2;
        }
    }
    else
    {
        /* Clear Transmit Interrupt */
        dummy1 = U1IIR;
    }

    /* Notify VIC that ISR execution is complete */
    VICVectAddr = 0;
}


/*---------------------------------------------------------
 Function Name : InitUART1()

 Description   : Initializes UART1 for communication with
                 the RFID Reader.

 Configuration:
     • Baud Rate : 9600
     • Data Bits : 8
     • Stop Bits : 1
     • Parity    : None
     • Interrupt : Enabled
----------------------------------------------------------*/
void InitUART1(void)
{
    /* Configure UART1 TXD1 and RXD1 Pins */
    PINSEL0 |= 0x00050000;

    /* 8-bit Data, No Parity, 1 Stop Bit */
    U1LCR = 0x83;

    /* Baud Rate = 9600 */
    U1DLL = 97;

    /* Disable Divisor Latch Access */
    U1LCR = 0x03;

#if UART_INT_ENABLE > 0

    /* Configure UART1 Interrupt */
    VICIntSelect = 0x00000000;

    VICVectAddr1 = (unsigned)UART1_isr;

    VICVectCntl1 = 0x20 | 7;

    VICIntEnable |= (1 << 7);

    /* Enable Receive and THRE Interrupts */
    U1IER = 0x03;

#endif
}


/*---------------------------------------------------------
 Function Name : UART1_Tx()

 Description   : Transmits a single character through UART1.

 Input :
      ch - Character to transmit.
----------------------------------------------------------*/
void UART1_Tx(char ch)
{
    /* Wait until transmitter is ready */
    while(!(U1LSR & 0x20));

    /* Send Character */
    U1THR = ch;
}


/*---------------------------------------------------------
 Function Name : UART1_Rx()

 Description   : Receives a single character from UART1.

 Return :
      Received Character
----------------------------------------------------------*/
char UART1_Rx(void)
{
    /* Wait until data is received */
    while(!(U1LSR & 0x01));

    return U1RBR;
}


/*---------------------------------------------------------
 Function Name : UART1_Str()

 Description   : Sends a null-terminated string through
                 UART1.

 Input :
      s - Pointer to string.
----------------------------------------------------------*/
void UART1_Str(char *s)
{
    while(*s)
    {
        UART1_Tx(*s++);
    }
}


/*---------------------------------------------------------
 Function Name : UART1_Int()

 Description   : Sends an unsigned integer through UART1.

 Input :
      n - Integer to transmit.
----------------------------------------------------------*/
void UART1_Int(unsigned int n)
{
    unsigned char a[10] = {0};

    int i = 0;

    if(n == 0)
    {
        UART1_Tx('0');

        return;
    }

    while(n > 0)
    {
        a[i++] = (n % 10) + '0';

        n /= 10;
    }

    while(--i >= 0)
    {
        UART1_Tx(a[i]);
    }
}


/*---------------------------------------------------------
 Function Name : UART1_Float()

 Description   : Sends a floating-point number through
                 UART1.

 Input :
      f - Floating-point value.
----------------------------------------------------------*/
void UART1_Float(float f)
{
    int x;

    float temp;

    x = f;

    UART1_Int(x);

    UART1_Tx('.');

    temp = (f - x) * 100;

    x = temp;

    UART1_Int(x);
}


/**************************************************************
 The code below is a sample test program (currently commented)
 demonstrating RFID tag reading and OTP generation. It is
 intended only for development and testing purposes.
**************************************************************/
