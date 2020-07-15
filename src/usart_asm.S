/*  -*- mode: arm-asm -*-  */
	.syntax unified
	.text
	.global usart1_hex,_buff_add

	# USART_CR1_RE |  USART_CR1_TE | USART_CR1_UE | USART_CR1_TXEIE | USART_CR1_TCIE
.equ USART_TX_EN, 0xcd
.equ USART_CR1_TXEIE, 0b10000000

.equ USART1 ,0x40013800
.equ CR1    ,0
.equ ISR    ,0x1c
.equ TDR    ,0x28

.equ txhead ,0
.equ txtail ,1
.equ buf    ,4



	.func	_buff_add
	.thumb_func
	.type _buff_add, %function
	.align


_buff_add:
	push    {r4,lr}
	ldr		r4,=USART1
	ldr		r3, =u1_data
	ldrb	r1, [r3,#txhead]

 	adds    r1, #1
	movs    r2, #0x3f
 	ands    r2, r1
@	ldr		r1, =USART1
	# r2:head+1 r1: head,r4: tail,r3: u1_data
@	movs	r4,#USART_TX_EN
@	str		r4,[r1,#CR1] 		@ USART1->CR1 = USART_TX_EN
1:
 	ldrb    r1, [r3, #txtail]
 	cmp     r1, r2
	bne		1f

	@USART1->CR1=USART_INIT_VALUE | USART_CR1_TCIE | USART_CR1_TXEIE;
	movs	r1,#205
	str     r1, [r4, #CR1]

	b		1b
 1:
	ldrb	r1,[r3,#txhead]
	strb	r2,[r3,#txhead]
	adds	r3,r1
	strb	r0,[r3,#buf]


	pop		{r4,pc}
	
	.size _buff_add, . - _buff_add
	.endfunc


	/*
	 * 用adr 可以直接赋值在代码区的常量。
	 * 如: adr r4,hex_table,实际会被编译成 add r4,pc, #<偏移>
	 */
	
	.func	usart1_hex
	.thumb_func
	.type usart1_hex, %function
	.align
usart1_hex:
	push	{r4}
	ldr		r3,=hex_buf
	movs	r1,#8
	adr		r4,hex_table
1:
	movs	r2,#0x0f
	ands	r2,r0
	lsrs	r0,r0,#4
	ldrb	r2,[r4,r2]
	subs	r1,#1
	strb	r2,[r3,r1]
	bne		1b
	movs	r0,#8
	mov		r1,r3
	pop		{r4}
	b		usart1_puts

	.align
	.size usart1_hex, . - usart1_hex
	.endfunc
	.pool

hex_table:
	.ascii "0123456789abcdef"

	.data
hex_buf:
	.space		8						@ keep 8 bytes,
