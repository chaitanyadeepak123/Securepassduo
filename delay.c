#include "types.h"

/*---------------------------------------------------------
 Function Name : delay_us()
 Description   : Generates an approximate delay in
                 microseconds using a software delay loop.
 Input         : tdly - Delay time in microseconds.
 Return        : None
----------------------------------------------------------*/
void delay_us(u32 tdly)
{
    /* Adjust loop count for 1 microsecond delay */
    tdly *= 12;

    /* Execute empty loop to create delay */
    while(tdly--);
}


/*---------------------------------------------------------
 Function Name : delay_ms()
 Description   : Generates an approximate delay in
                 milliseconds using a software delay loop.
 Input         : tdly - Delay time in milliseconds.
 Return        : None
----------------------------------------------------------*/
void delay_ms(u32 tdly)
{
    /* Adjust loop count for 1 millisecond delay */
    tdly *= 12000;

    /* Execute empty loop to create delay */
    while(tdly--);
}


/*---------------------------------------------------------
 Function Name : delay_s()
 Description   : Generates an approximate delay in
                 seconds using a software delay loop.
 Input         : tdly - Delay time in seconds.
 Return        : None
----------------------------------------------------------*/
void delay_s(u32 tdly)
{
    /* Adjust loop count for 1 second delay */
    tdly *= 12000000;

    /* Execute empty loop to create delay */
    while(tdly--);
}
