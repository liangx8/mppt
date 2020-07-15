ENTRY(Reset_handler)

MEMORY
{
    ram (rwx) : ORIGIN = 0x20000000, LENGTH = 8K
    rom (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
}
SECTIONS
{

    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector)) /* Startup code */
		*(.adv_main)	/*前置main方法，防止引导程序跳main的时候超出范围*/
        . = ALIGN(4);
    } >rom

    /* The program code and other data into ROM memory */
    .text : 
    {
        . = ALIGN(4);
        *(.text)      /* Program code */
		. = ALIGN(4);
        _etext = .;
    } >rom
    /* Constant data into ROM memory */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } >rom
    _sidata = LOADADDR(.data);

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)      /* Data memory */
        *(.data*)      /* Data memory */
        . = ALIGN(4);
        _edata = .;
    } >ram AT > rom

    .bss :
    {
        _sbss = .;
        __bss_start__ = _sbss;
        *(.bss)       /* Zero-filled run time allocate data memory */
        *(.bss*)       /* Zero-filled run time allocate data memory */
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
    } >ram AT > rom
	.stack   0x20002000 :
	{
		_estack = .;
		*(.stack)
	}
    /* Remove information from the compiler libraries */
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }

} 