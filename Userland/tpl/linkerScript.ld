OUTPUT_FORMAT("binary")
ENTRY(_start)
SECTIONS
{
	.text 0x800000 :
	{
		*(.text*)
		. = ALIGN(0x4000);
		*(.rodata*)
	}
	.data ALIGN(0x4000) :
	{
		*(.data*)
	}
	.bss ALIGN(0x4000) :
	{
		bss = .;
		*(.bss*)
	}
	endOfBinary = .;
}