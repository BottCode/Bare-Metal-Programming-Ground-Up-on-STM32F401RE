#include "stm32f4xx.h"

// since our system clock is 16MHz -> 16000 cycles define a millisecond
#define SYSTICK_LOAD_VAL        16000
#define CTRL_ENABLE             (1U << 0)
// Setting processor clock as clock source
#define CRTL_CLKSRC             (1U << 2)
#define CTRL_COUNTFLAG          (1U << 16)

void systickDelayMs (int delay)
{
    /* Configure systick */
    /* Reload with number of clocks per millisecond */
    SysTick->LOAD = 16000;

    /* Clear systick current value register */
    SysTick->VAL = 0;

    /* Enable systick and select internal clk src */
    SysTick->CTRL = CTRL_ENABLE | CRTL_CLKSRC;

    for (int i = 0; i < delay; i++)
    {
        /* Wait until the COUNTFLAG is set*/
        while ((SysTick->CTRL & CTRL_COUNTFLAG) == 0)
        {
            ;
        }
    }

    SysTick->CTRL = 0;
}