#include "stm32f4xx.h"

#define ADC1EN          (1U << 8)
#define GPIOAEN         (1U << 0)
#define ADC_CH1         (1U << 0)
#define ADC_SEQ_LEN_1   0x00
#define CR2_AD0N        (1U << 0)
#define CR2_SWSTART     (1U << 30)
#define SR_EOC          (1U << 1)
#define CR2_CONT        (1U << 1)

void pa1_adc_init (void)
{
    /**** Configure the ADC GPIO pin ****/
    
    /* Enable clock access to GPIOA port */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set the mode of PA1 to analog */
    GPIOA->MODER |= (1U << 2);
    GPIOA->MODER |= (1U << 3);

    /**** Configure the ADC module ****/
    /* Enable clock access to ADC */
    RCC->APB2ENR |= ADC1EN;

    /* Configure ADC parameters*/
    /* Conversion sequence start */
    ADC1->SQR3 = ADC_CH1;
    /* Conversion sequence length */
    ADC1->SQR1 = ADC_SEQ_LEN_1;
    /* Enable ADC module */
    ADC1->CR2 |= CR2_AD0N;
}

void start_conversion (void)
{
    /* Enable continuos conversion */
    ADC1->CR2 |= CR2_CONT;
    /* Start adc conversion */
    ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read (void)
{
    /* Wait for conversion to be complete */
    while (!(ADC1->SR & SR_EOC))
    {
        ;
    }

    /* Read converted result */
    return ADC1->DR;
}