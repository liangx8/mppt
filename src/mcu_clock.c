#include <stm32f0xx.h>

/*------------------------------------------------------------
                      选择系统时钟
------------------------------------------------------------*/
void RCC_Init(void)
{
    /* disable all interruption */
    /* NVIC_ICER0 */
    NVIC->ICER[0]=0xffffffff;

    /* enable all interruption */
    //NVIC->ISER[0]=0xffffffff;
    //NVIC->ISER[1]=0xffffffff;
    //NVIC->ISER[2]=0xffffffff;
    /* SysTick setting */
    SysTick->CTRL = 0;
    SysTick->LOAD = 0xffffff;
    /* example code from reference manual
    *[PLL configuration modification code example]
    * 内部8M晶震，48M PLL输出
    */
    /* (1) Test if PLL is used as System clock */
    /* (2) Select HSI as system clock */
    /* (3) Wait for HSI switched */
    /* (4) Disable the PLL */
    /* (5) Wait until PLLRDY is cleared */
    /* (6) Set the PLL multiplier to 12 */
    /* (7) Enable the PLL */
    /* (8) Wait until PLLRDY is set */
    /* (9) Select PLL as system clock */
    /* (10) Wait until the PLL is switched on */
    if ((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL) /* (1) */
    {
        RCC->CFGR &= (uint32_t) (~RCC_CFGR_SW); /* (2) */
        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) /* (3) */
        {
            /* For robust implementation, add here time-out management */
        }
    }
    RCC->CR &= (uint32_t)(~RCC_CR_PLLON);/* (4) */
    while((RCC->CR & RCC_CR_PLLRDY) != 0) /* (5) */
    {
        /* For robust implementation, add here time-out management */
    }
    RCC->CFGR = (RCC->CFGR & (~RCC_CFGR_PLLMUL)) | (RCC_CFGR_PLLMUL12); /* (6) */
    RCC->CR |= RCC_CR_PLLON; /* (7) */
    while((RCC->CR & RCC_CR_PLLRDY) == 0) /* (8) */
    {
        /* For robust implementation, add here time-out management */
    }
    // 选择PLL 源,同时切换系统时钟到PLL RCC_CFGR_PLLSRC_HSI_DIV2
    // 对于F051,PLLSRC[0] 被强制保持0，因此只能选择 HSI/2 和 HSE/PREDIV
    RCC->CFGR |= (uint32_t) (RCC_CFGR_SW_PLL) | RCC_CFGR_PLLSRC_HSI_DIV2; /* (9) */
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) /* (10) */
    {
        /* For robust implementation, add here time-out management */
    }
    RCC->CIR = 0x00007f00;     //清除所有中断标记
}
