OUTPUT_FORMAT("binary")
ENTRY(_start)
SECTIONS
{
	.text 0x400000 :
	{
		*(.text*)
		. = ALIGN(0x8000);
		*(.rodata*)
	}
	.data ALIGN(0x8000) :
	{
		*(.data*)
	}
	.bss ALIGN(0x8000) :
	{
		bss = .;
		*(.bss*)
	}
	endOfBinary = .;
}