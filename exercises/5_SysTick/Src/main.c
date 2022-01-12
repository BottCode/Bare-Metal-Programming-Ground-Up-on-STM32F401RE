#include "IO.h"
#include "adc.h"
#include "systick.h"

int main (void)
{
	uart2_tx_init ();
	LedInit ();

	while (1)
	{
		LedToggle ();
		systickDelayMs (1000);
	}
}