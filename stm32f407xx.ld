MEMORY {
    FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 1M
    SRAM1(rwx) : ORIGIN = 0x20000000, LENGTH = 128K
    SRAM2(rwx) : ORIGIN = 0x10000000, LENGTH = 64K
}

STACK_SIZE = 0x0400;

SECTIONS {
    .vectors :
    {
        KEEP(*(.vectors))
    } > FLASH

    .text :
    {
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH

    .bss (NOLOAD) :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM1

    .stack (NOLOAD) :
    {
        . = ALIGN(8);
        . = . + STACK_SIZE;
        . = ALIGN(8);
    } > SRAM1

    .data : 
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > SRAM1 AT > FLASH
}

INIT_SP = 0x20000000 + STACK_SIZE;