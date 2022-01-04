#include "IO.h"

int main (void)
{
	uart2_tx_init ();

	while (1)
	{
		uart2_write ('Y');
	}
}