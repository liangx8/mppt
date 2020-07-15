#include <stm32f0xx.h>
#include <strings.h>
// NOTE: 由于代码中使用了与取整，因此这个值必须是64
#define BUF_MAX 64




#if BUF_MAX != 64
    #error "BUF_MAX must be 64"
#endif
struct USART_DATA{
    uint8_t txhead,txtail;
    uint16_t _reversed;
    uint8_t buf[BUF_MAX];
} u1_data;


#define USART_INIT_VALUE USART_CR1_RE | USART_CR1_TE | USART_CR1_UE
#define USART_TX_EN USART_INIT_VALUE | USART_CR1_TXEIE

void usart1_init(void)
{
    
    //RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    NVIC_EnableIRQ(USART1_IRQn);

    // page 732                                                                                                                                                                                                                    
    //  USART1->CR1 = USART_CR1_M1|USAR_CR1_M0;                                                                                                                                                                                    
    // 根据 704页的表，用oversampling by 16, 115200 波特率填的数值                                                                                                                                                                 
    USART1->BRR = 0x1a1;
    // 使能 发送和接受，中断开启                                                                                                                                                                                                   
    // 8位宽， 1位停止， 无校验是缺省的设置                                                                                                                                                                                        
    //USART1->CR1 = USART_INIT_VALUE;

    //RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;                                                                                                                                                                                     
    USART1->CR1 = USART_INIT_VALUE;
    // matching compiler optimize
    u1_data.txhead=0;
    u1_data.txtail=0;
    //    ubuffer.rhead=0;
    //    ubuffer.rtail=0;
}
void USART1_handler(void)
{
    // USART_ISR page 746

    if(USART1->ISR & USART_ISR_RXNE){
//        u1_data.rxbyte=USART1->RDR;
    }
    // FIXME:发送中断不按预期发生。并且持续发生。查看汇编来排除
    if(USART1->ISR & USART_ISR_TXE){
        uint8_t idx=u1_data.txtail;
        uint8_t idx1;
        if(idx != u1_data.txhead){
            idx1=(idx+1) & 0x3f;
            u1_data.txtail=idx1;
            USART1->TDR=u1_data.buf[idx];
        } else {
            USART1->CR1=USART_INIT_VALUE | USART_CR1_TCIE;

        }
    }
    if(USART1->ISR & USART_ISR_TC){
        USART1->CR1=USART_INIT_VALUE;
    }
}

void _buff_add(uint8_t);

void usart1_puts(uint32_t size,const uint8_t *data)
{
    for(int idx=0;idx<size;idx++){
        _buff_add(data[idx]);
    }
    USART1->CR1=USART_INIT_VALUE | USART_CR1_TCIE | USART_CR1_TXEIE;
}
/**
 * return 0xffff if read nothing
 * */
uint32_t usart1_get(void)
{
    if(USART1->ISR & USART_ISR_RXNE){
        //toggle_b13();
        return USART1->RDR;
    } else {
        return 0xffff;
    }
}
/*
void usart1_hex(uint32_t);
void usart1_test(void)
{
    while(u1_data.rxbyte==0xffff);
    usart1_hex(usart1_get());
    for(int i=0;i<10;i++)
        usart1_putchar('0'+i);
    
}
*/