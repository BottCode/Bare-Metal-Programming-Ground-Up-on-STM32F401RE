#include "stm32f4xx.h"

#define GPIOAEN     	(1U << 0)
#define PIN5        	(1U << 5)
#define LED_PIN     	(PIN5)

#define CR1_TE 			(1U << 3)
#define CR1_RE 			(1U << 2)
#define CR1_UE 			(1U << 13)
#define SR_TXE 			(1U << 7)
#define SR_RXNE 			(1U << 5)

#define SYS_FREQ		16000000
#define APB1_CLK		SYS_FREQ

#define UART_BAUDRATE	115200

#define UART2EN     (1U << 17)
static void uart_set_baudrate (USART_TypeDef * USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd (uint32_t PeriphClk, uint32_t BaudRate);


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

void uart2_tx_init (void)
{
	/* configure uart gpio pin */
	// enable clock access to gpioa
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA2 to alternate function mode
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	// Set PA2 alternate function type to UART_TX (AF07)
	GPIOA->AFR[0] |= (1U << 8);
	GPIOA->AFR[0] |= (1U << 9);
	GPIOA->AFR[0] |= (1U << 10);
	GPIOA->AFR[0] &= ~(1U << 11);

	/* configure uart module */
	// enable clock access to uart2
	RCC->APB1ENR |= UART2EN;

	// configure baudrate
	uart_set_baudrate (USART2, APB1_CLK, UART_BAUDRATE);

	// configure the transfer direction. No OR operator: we want to clean the whole CR1 register.
	USART2->CR1 = CR1_TE;

	// enable uart module
	USART2->CR1 |= CR1_UE;
}

void uart2_write (int ch)
{
	// Make sure the trasmit data register is empty
	while (!(USART2->SR & SR_TXE))
	{
		;// Make sure the trasmit data register is empty
	}
	// Write to transmit data register
	USART2->DR = (ch & 0xFF);
}

static void uart_set_baudrate (USART_TypeDef * USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	// BRR = BaudRate Register
	USARTx->BRR = compute_uart_bd (PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd (uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
}

/* Initialize both RX and TX functionalities */
void uart2_rxtx_init (void)
{
	/* configure uart gpio pin */
	// enable clock access to gpioa
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA2 to alternate function mode
	GPIOA->MODER &= ~(1U << 4);
	GPIOA->MODER |= (1U << 5);

	// Set PA2 alternate function type to UART_TX (AF07)
	GPIOA->AFR[0] |= (1U << 8);
	GPIOA->AFR[0] |= (1U << 9);
	GPIOA->AFR[0] |= (1U << 10);
	GPIOA->AFR[0] &= ~(1U << 11);

	// Set PA3 alternate function mode
	GPIOA->MODER &= ~(1U << 6);
	GPIOA->MODER |= (1U << 7);

	// Set PA3 alternate function type to UART_RX (AF07)
	GPIOA->AFR[0] |= (1U << 12);
	GPIOA->AFR[0] |= (1U << 13);
	GPIOA->AFR[0] |= (1U << 14);
	GPIOA->AFR[0] &= ~(1U << 15);

	/* configure uart module */
	// enable clock access to uart2
	RCC->APB1ENR |= UART2EN;

	// configure baudrate
	uart_set_baudrate (USART2, APB1_CLK, UART_BAUDRATE);

	// configure the transfer direction. No OR operator: we want to clean the whole CR1 register.
	USART2->CR1 = (CR1_TE | CR1_RE);

	// enable uart module
	USART2->CR1 |= CR1_UE;
}

char uart2_read (void)
{
	// Make sure the receive data register is NOT empty
	while (!(USART2->SR & SR_RXNE))
	{
		;// Make sure the trasmit data register is empty
	}

	// Read data
	return USART2->DR;
}