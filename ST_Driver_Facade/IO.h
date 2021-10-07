#include "stm32f4xx.h"

#define GPIOAEN     (1U << 0)
#define PIN5        (1U << 5)
#define LED_PIN     (PIN5)

void LedInit ()
{
	// 1. Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// 2. Set PA5 as output pin
	
	// GPIOA->MODER |= (1U << 10); // Set bit 10 to 1
	// GPIOA->MODER &=~(1U << 11); // Set bit 11 to 0

	// combining the previous two instructions
	GPIOA->MODER = (GPIOA->MODER | (1U << 10)) & (~(1U << 11));
}

void LedToggle ()
{
	GPIOA->ODR ^= LED_PIN;
}

void LedOn ()
{
	GPIOA->ODR |= LED_PIN;
}

void LedOff ()
{
	GPIOA->ODR &= ~LED_PIN;
}
