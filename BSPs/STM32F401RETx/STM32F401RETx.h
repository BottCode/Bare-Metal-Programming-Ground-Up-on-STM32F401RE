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

typedef struct main
{
	uint32_t DUMMY[12];
	__IO uint32_t AHB1ENR;		// RCC AHB1 peripheral clock register,		Adress offset: 0x30
} RCC_TypeDef;

#define RCC		((RCC_TypeDef*) RCC_BASE)
#define GPIOA 	((GPIO_TypeDef*) GPIOA_BASE)