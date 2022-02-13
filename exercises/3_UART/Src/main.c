#include "IO.h"

int main (void)
{
	uart2_tx_init ();

	for (int i = 0; i < 10000000; i++)
	{
		if (i%1000000 == 0)
		{
			uart2_write ('P');
			uart2_write ('I');
			uart2_write ('N');
			uart2_write ('G');
			uart2_write ('-');
		}
	}
}