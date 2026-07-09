#include <stdio.h>
#include <lpc21xx.h>

/*---------------------------------------------------------
 Function Name : eint1_isr()
 Description   : Interrupt Service Routine (ISR) for
                 External Interrupt 1 (EINT1).
                 When the interrupt occurs, the system
                 enters Admin Mode. After servicing the
                 interrupt, the interrupt flag is cleared
                 and the interrupt controller is informed
                 that the ISR execution is complete.
----------------------------------------------------------*/
void eint1_isr(void)__irq
{
    /* Enter Admin Mode */
    adminmode();

    /* Clear EINT1 interrupt flag */
    EXTINT = (1 << 1);

    /* Notify VIC that interrupt servicing is completed */
    VICVectAddr = 0;
}


/*---------------------------------------------------------
 Function Name : enable_ent1()
 Description   : Configures External Interrupt 1 (EINT1)
                 on LPC2148.
                 - Selects EINT1 function for the pin.
                 - Enables EINT1 interrupt in VIC.
                 - Assigns ISR to the interrupt vector.
                 - Configures EINT1 as edge-triggered.
----------------------------------------------------------*/
void enable_ent1(void)
{
    /* Configure P0.14 as EINT1 function */
    PINSEL0 &= ~(3 << 28);     // Clear function bits
    PINSEL0 |=  (2 << 28);     // Select EINT1

    /* Enable EINT1 interrupt in VIC */
    VICIntEnable = (1 << 15);

    /* Assign ISR address to Vector Slot 2 */
    VICVectAddr2 = (unsigned)eint1_isr;

    /* Enable Vector Slot 2 and assign interrupt number 15 (EINT1) */
    VICVectCntl2 = (1 << 5) | 15;

    /* Configure EINT1 as Edge Triggered */
    EXTMODE |= (1 << 1);

    /* Uncomment below to configure falling/rising edge if required */
    // EXTPOLAR = 0 << 1;
}
