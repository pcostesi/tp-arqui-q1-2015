GLOBAL _cli
GLOBAL _sti
GLOBAL _halt
GLOBAL _lidt
GLOBAL _sidt
GLOBAL _int80h
GLOBAL idt_pic_master_mask
GLOBAL idt_pic_slave_mask
GLOBAL idt_pic_master_eoi
GLOBAL idt_pic_slave_eoi
GLOBAL _irq_syscall_handler


EXTERN irq_handler


SECTION .text


%macro _idt_irq_handler 1
GLOBAL _irq_%1_handler

_irq_%1_handler:
	cli
	mov rdi, %1
	call irq_handler
	
	;signal pic
	mov al, 20h
	out 20h, al
	
	sti
	iretq
%endmacro


idt_pic_master_mask:
    push    rbp
    mov     rbp, rsp
    push	rax
    mov 	al, dil
    out		21h, al
    pop 	rax
    pop 	rbp
    retn


idt_pic_slave_mask:
    push    rbp
    mov     rbp, rsp

    push	rax
    mov 	al, dil
    out		0A1h, al
    pop 	rax
    pop 	rbp
    retn


idt_pic_master_eoi:
    push    rbp
    mov     rbp, rsp
    push	rax
    mov 	al, dil
    out		20h, al
    pop 	rax
    pop 	rbp
    retn


idt_pic_slave_eoi:
    push    rbp
    mov     rbp, rsp
    push	rax
    mov 	al, dil
    out		0A0h, al
    pop 	rax
    pop 	rbp
    retn


;Int 80h
_irq_syscall_handler:
	push rdi
	mov rdi, 80h
	cli

	call irq_handler
	
	pop rdi
	sti
	iretq


_idt_irq_handler 20h
_idt_irq_handler 21h
_idt_irq_handler 22h
_idt_irq_handler 23h
_idt_irq_handler 24h
_idt_irq_handler 25h
_idt_irq_handler 26h
_idt_irq_handler 27h


_int80h:
    push    rbp
    mov     rbp, rsp
	int 	80h
    pop 	rbp
    ret

_lidt:
    push    rbp
    mov     rbp, rsp
    lidt 	[rdi]
    pop 	rbp
    retn


_sidt:
    push    rbp
    mov     rbp, rsp
    sidt 	[rdi]
    pop 	rbp
    retn


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