OUTPUT_ARCH(riscv)
ENTRY(kernel_entry)

SECTIONS
{
    . = 0x80200000,
    .text :
    {
        _text_begin = .;
        *(.text.boot)
        *(.text)
        _text_end = .;
    }
    .rodata :
    {
        _rodata_begin = .;
        *(.rodata)
        _rodata_end = .;
    }
    .data :
    {
        _data_begin = .;
        *(.data)
        _data_end = .;
    }
    .bss :
    {
        _bss_begin = .;
        *(.bss)
        _bss_end = .;
    }

    . = ALIGN(0x1000),
    _end = .;
}