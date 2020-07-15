#include <stm32f0xx.h>

/*
 * page 269
 **/
void dac_config(void)
{
    DAC->CR = DAC_CR_EN1 | DAC_CR_TSEL1_0 | DAC_CR_TSEL1_1 | DAC_CR_TSEL1_2 | DAC_CR_TEN1;
}
void dac_set(uint32_t data)
{
    while(DAC->SWTRIGR & DAC_SWTRIGR_SWTRIG1 );
    DAC->DHR12R1=data;
    DAC->SWTRIGR = DAC_SWTRIGR_SWTRIG1;
}
void dac_cycle(void)
{
    uint32_t wav=(DAC->DHR12R1+1) & 0xfff;
    dac_set(wav);
    /*
    if(GPIOA->IDR & GPIO_IDR_5)
        GPIOA->BRR=GPIO_ODR_5;
    else
        GPIOA->BSRR=GPIO_ODR_5;
        */
}