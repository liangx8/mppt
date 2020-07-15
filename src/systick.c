#include <stm32f0xx.h>
void SysTick_handler(void)
{
    if(GPIOC->IDR & GPIO_IDR_13){
        GPIOA->BRR = GPIO_ODR_5 | GPIO_ODR_6;
        GPIOC->BRR = GPIO_ODR_13;
        return;
    } 
    GPIOA->BSRR = GPIO_ODR_5 | GPIO_ODR_6;
    GPIOC->BSRR = GPIO_ODR_13;
}