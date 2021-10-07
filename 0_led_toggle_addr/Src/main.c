#include "STM32F401RETx.h"

int main (void)
{
	// 1. Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// 2. Set PA5 as output pin
	
	GPIOA->MODER |= (1U << 10); // Set bit 10 to 1
	GPIOA->MODER &=~(1U << 11); // Set bit 11 to 0

	for (int i = 0; i < 11; i++)
	{
		// 4. Set PA5 high
		// GPIOA_OD_R |= LED_PIN;
		// 5. toggle PA5
		GPIOA->ODR ^= LED_PIN;
	}
}
