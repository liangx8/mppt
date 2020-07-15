#ifndef USART_H_KJADF3JH432
#define USART_H_KJADF3JH432
#include <stm32f0xx.h>
void usart1_init(void);
//void usart1_disable(void);
//void usart1_putchar(uint8_t);

void usart1_hex(uint32_t); // usart_asm.S
void usart1_puts(uint32_t ,const char *);

#define usart1_putsz(x) usart1_puts(sizeof(x),x)
uint16_t usart1_get(void);


#endif