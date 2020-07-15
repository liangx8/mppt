#ifndef IO_INIT_H_JLAD768934JA
#define IO_INIT_H_JLAD768934JA
#define RCC_AHBENR_VALUE (RCC_AHBENR_GPIOAEN \
                        | RCC_AHBENR_GPIOBEN \
                        | RCC_AHBENR_GPIOCEN \
                        | RCC_AHBENR_GPIOFEN \
                        | RCC_AHBENR_SRAMEN );//先使能外设IO PORTa,b,c,f时钟, SRAM 时钟

#define RCC_APB2ENR_VALUE RCC_APB2ENR_USART1EN
#define RCC_APB1ENR_VALUE RCC_APB1ENR_DACEN
#define GPIOA_MODER_VALUE (0b1010 << 26) | (0b010111 << 8)
//                           | |              | | `------------PA4 Analog
//                           | |              | `--------------PA5
//                           | |              `----------------PA6
//                           | |
//                           | |
//                           | |
//                           | |
//                           | |
//                           | `------------------------------- PA13 SWDIO(default setting)
//                           `--------------------------------- PA14 SWCLK(default setting)


// pc13 LED light
#define GPIOC_MODER_VALUE (0b01 << 26)
#define GPIOC_OSPEEDR_VALUE (0b11 << 26)
#define GPIOB_MODER_VALUE (0b1010 << 12) | 0b1010
//                           | `------------------------ PB 6 USART1_TX AF
//                           `-------------------------- PB 7 USART1_RX AF

#define GPIOB_OTYPER_VALUE (0b10 << 6)
//                            |`------------------------PB 6 USART1_TX PP
//                            `-------------------------PB 7 USART1_RX OD
// 在网上看到一些帖说RX要设置为 INPUT FLOAT MODER=0b00，先用自己理解的模式， TX 用 AF PP, RX 用 AF OD
// idle状态下，RX是高电平, TX是低电平(因为把TX关闭了)


#endif