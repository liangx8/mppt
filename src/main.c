#include <stdint.h>
#include <stm32f0xx.h>
#include "usart.h"
const char cr[]={0x0d,0x0a};
uint32_t hex2bcd(uint32_t);
void dac_set(uint32_t data);
void dac_cycle(void);
int main(void) __attribute__ ((section(".adv_main"))) __attribute__((naked));
int main(void)
{
    SysTick_Config(0x1000000);
    GPIOC->BSRR=GPIO_ODR_13;
    usart1_hex(hex2bcd(0x80000000));
    usart1_puts(2,cr);
    usart1_hex(hex2bcd(12345678));
    usart1_puts(2,cr);
    uint32_t dac_value=0;
    while (1)
    {
        dac_cycle();
        uint16_t ch=usart1_get();
        switch (ch)
        {
        case 0xffff:
            /* code */
            break;
        case 'q':
            {
                uint32_t tmp=dac_value + 1;
                if(tmp <= 4095) dac_value=tmp;
                usart1_hex(hex2bcd(dac_value));
                usart1_puts(2,cr);
                dac_set(dac_value);
            }
            break;
        case 'w':
            {
                uint32_t tmp=dac_value + 10;
                if(tmp <= 4095) dac_value=tmp;
                usart1_hex(hex2bcd(dac_value));
                usart1_puts(2,cr);
                dac_set(dac_value);
            }
            break;
        case 'e':
            {
                uint32_t tmp=dac_value + 100;
                if(tmp <= 4095) dac_value=tmp;
                usart1_hex(hex2bcd(dac_value));
                usart1_puts(2,cr);
                dac_set(dac_value);

            }
            break;
        case 'r':
            {
                uint32_t tmp=dac_value + 1000;
                if(tmp <= 4095) dac_value=tmp;
                usart1_hex(hex2bcd(dac_value));
                usart1_puts(2,cr);
                dac_set(dac_value);

            }
            break;
        case 'z':
            if(dac_value >0) dac_value--;
            usart1_hex(hex2bcd(dac_value));
            usart1_puts(2,cr);
            dac_set(dac_value);
            break;
        case 'x':
            if(dac_value >10) dac_value-=10;
            usart1_hex(hex2bcd(dac_value));
            usart1_puts(2,cr);
            dac_set(dac_value);
            break;
        case 'c':
            if(dac_value >100) dac_value-=100;
            usart1_hex(hex2bcd(dac_value));
            usart1_puts(2,cr);
            dac_set(dac_value);
            break;
        case 'v':
            if(dac_value >1000) dac_value-=1000;
            usart1_hex(hex2bcd(dac_value));
            usart1_puts(2,cr);
            dac_set(dac_value);
            break;
        
        default:
            usart1_hex(ch);
            usart1_puts(2,cr);
        }
    }
    
}
void io_init(void);
void delay(uint32_t);

void dac_config(void);
void ic_init(void)
{
    io_init();
    dac_config();
    for(int i=0;i<10;i++){
        delay(0xfffff);
        GPIOC->BRR=GPIO_ODR_13;
        delay(0xfffff);
        GPIOC->BSRR=GPIO_ODR_13;
    }
    usart1_init();
}
const uint32_t h2d_matrix[]={10000000,1000000,100000,10000,1000,100,10};
uint32_t h2d(uint32_t h)
{
    uint32_t val=0;
    if(h > 99999999)return 99999999;
    while(h > 10000000){
        val++;
        h-=10000000;
    }
    val = val <<4;
    while(h > 1000000){
        val++;
        h-=1000000;
    }
    val = val <<4;
    while(h > 100000){
        val++;
        h-=100000;
    }
    val = val <<4;
    while(h > 10000){
        val++;
        h-=10000;
    }
    val = val <<4;
    while(h > 1000){
        val++;
        h-=1000;
    }
    val = val <<4;
    while(h > 100){
        val++;
        h-=100;
    }
    val = val <<4;
    while(h > 10){
        val++;
        h-=10;
    }
    val = (val <<4) + h;

    return val;
}