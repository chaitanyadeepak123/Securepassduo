#ifndef __UART_INTERRUPT_H__
#define __UART_INTERRUPT_H__

/*---------------------------------------------------------
 UART0 Function Prototypes
----------------------------------------------------------*/

/* Initializes UART0 for serial communication. */
void InitUART0(void);

/* Transmits a single character through UART0. */
void UART0_Tx(char ch);

/* Receives a single character from UART0. */
char UART0_Rx(void);

/* Transmits a null-terminated string through UART0. */
void UART0_Str(char *s);

/*---------------------------------------------------------
 UART0 External Variables
----------------------------------------------------------*/

/* UART0 receive buffer */
extern char buff[];

/* UART0 receive complete flag */
extern unsigned char r_flag;


/*---------------------------------------------------------
 UART1 Function Prototypes
----------------------------------------------------------*/

/* Transmits a single character through UART1. */
void UART1_Tx(char ch);

/* Receives a single character from UART1. */
char UART1_Rx(void);

/* Transmits a null-terminated string through UART1. */
void UART1_Str(char *s);

/*---------------------------------------------------------
 UART1 External Variables
----------------------------------------------------------*/

/* UART1 receive buffer */
extern char buff1[];

/* UART1 receive complete flag */
extern unsigned char r_flag1;


/*---------------------------------------------------------
 External Interrupt (EINT1) Function Prototypes
----------------------------------------------------------*/

/* External Interrupt 1 Interrupt Service Routine (ISR). */
void eint1_isr(void)__irq;

/* Configures and enables External Interrupt 1 (EINT1). */
void enable_ent1(void);


/*---------------------------------------------------------
 Admin Mode Function Prototypes
----------------------------------------------------------*/

/* Displays the Admin Mode menu. */
void adminmode(void);

/* Displays the RTC editing menu for updating RTC values. */
void rtc_edit(void);


/*---------------------------------------------------------
 GSM Status Variable
----------------------------------------------------------*/

/* GSM module status
   1 = GSM Connected
   0 = GSM Not Connected */
extern int gsm_flag;

#endif
