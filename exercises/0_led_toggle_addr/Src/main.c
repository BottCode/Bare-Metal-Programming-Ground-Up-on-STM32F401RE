#include "BSP.h"

int main (void)
{
	LedInit ();

	for (int i = 0; i < 10000000; i++)
	{
		if (i%1000000 == 0)
		{
			LedToggle ();
		}
	}

	LedOn ();
}