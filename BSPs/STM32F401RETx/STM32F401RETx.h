// User led is connected to port A, pin 5

#include <stdint.h>

#define PERIPH_BASE 		(0x40000000UL)
#define AHB1PERIPH_OFFSET	(0x00020000UL)
#define AHB1PERIPH_BASE 	(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET		(0x0000UL)
#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET			(0x3800UL)
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIOAEN				(1U << 0) // 0000 0000 0000 0000 0000 0000 0000 0001

#define PIN5				(1U << 5)
#define LED_PIN      		PIN5

#define __IO volatile
/*
typedef struct
{
	__IO uint32_t MODER; 	// GPIO port mode register						Address offset: 0x00
	__IO uint32_t OTYPER;	// GPIO port output type register				Address offset: 0x04
	__IO uint32_t OSPEEDR;  // GPIO port output speed register				Address offset: 0x08
	__IO uint32_t PUPDR;	// GPIO port pull-up/pull-down register			Address offset: 0x0C
	__IO uint32_t IDR;		// GPIO port input data register				Address offset: 0x10
	__IO uint32_t ODR;		// GPIO port output data register				Address offset: 0x14
	__IO uint32_t BSRR;		// GPIO port bit set/reset register				Address offset: 0x18
	__IO uint32_t LCKR;		// GPIO port confogiration lock register		Address offset: 0x1C
	__IO uint32_t AFR[2];	// GPIO port alternate function registers		Address offset: 0x20-0x24
} GPIO_TypeDef;
*/

typedef struct
{
	__IO uint32_t MODER; 		// GPIO port mode register						Address offset: 0x00
	// __IO uint32_t OTYPER;	// GPIO port output type register				Address offset: 0x04
	// __IO uint32_t OSPEEDR;   // GPIO port output speed register				Address offset: 0x08
	// __IO uint32_t PUPDR;		// GPIO port pull-up/pull-down register			Address offset: 0x0C
	// __IO uint32_t IDR;		// GPIO port input data register				Address offset: 0x10
	uint32_t DUMMY[4];
	__IO uint32_t ODR;			// GPIO port output data register				Address offset: 0x14
} GPIO_TypeDef;

typedef struct
{
	uint32_t DUMMY[12];
	__IO uint32_t AHB1ENR;		// RCC AHB1 peripheral clock register,		Adress offset: 0x30
} RCC_TypeDef;

#define RCC		((RCC_TypeDef*) RCC_BASE)
#define GPIOA 	((GPIO_TypeDef*) GPIOA_BASE)

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