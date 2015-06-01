GLOBAL _cli
GLOBAL _sti
GLOBAL _halt

SECTION .text



_cli:
	cli
	ret


_sti:
	sti
	ret


_halt:
	cli
	hlt
	ret