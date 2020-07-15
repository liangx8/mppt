	.syntax unified
	.text
	.global delay,hex2bcd

    .func   delay
    .thumb_func
    .type delay, %function
    .align
delay:
1:
    subs    r0,#1
    bcs     1b
    @b       toggle_b13
    bx      lr
   .align
    .size delay, . - delay
    .endfunc

    .func   hex2bcd
    .thumb_func
    .type hex2bcd, %function
    .align
hex2bcd:
    adr     r1,matrix
    ldr     r2,[r1]
    cmp     r0,r2
    bhi     9f
    movs    r2,#0
1:
    adds    r1,#4
    adr     r3,matrix_end
    cmp     r3,r1
    beq     3f

    ldr     r3,[r1]
2:
    cmp     r0,r3
    bhi     1f
    @ r0 小于 matrix[x]
    lsls    r2,#4
    b       1b
1:
    adds    r2,#1
    subs    r0,r3
    b       2b
3:
    adds    r0,r2
    bx      lr
9:
    ldr     r0,=0x99999999
    bx      lr
    .align
    .size hex2bcd, . - hex2bcd
    .endfunc

matrix:
    .word 99999999,10000000,1000000,100000,10000,1000,100,10
matrix_end:
