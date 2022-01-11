#include "IO.h"
#include "adc.h"

uint32_t sensor_value;

int main (void)
{
	uart2_tx_init ();
	pa1_adc_init ();
	start_conversion ();

	while (1)
	{
		sensor_value = adc_read ();
	}
}