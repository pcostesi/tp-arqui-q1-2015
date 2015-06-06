GLOBAL _cli
GLOBAL _sti
GLOBAL _halt
GLOBAL _lidt
GLOBAL _sidt
GLOBAL idt_pic_master_mask
GLOBAL idt_pic_slave_mask
GLOBAL idt_pic_master_set_map
GLOBAL idt_pic_slave_set_map
GLOBAL _irq_sys_handler

EXTERN irq_handler
EXTERN sys_handler


SECTION .text

%macro _idt_irq_master_handler 1
GLOBAL _irq_%1_handler

_irq_%1_handler:
    cli
    push rax
    mov rdi, %1
    call irq_handler
    
    ;signal master pic
    mov al, 20h
    out 20h, al
    
    pop rax
    sti
    iretq
%endmacro

%macro _idt_irq_slave_handler 1
GLOBAL _irq_%1_handler

_irq_%1_handler:
    cli
    push rax
    mov rdi, %1
    call irq_handler
    
    ;signal master pic
    mov al, 20h
    out 20h, al

    ;signal slave pic
    mov al, 0xA0
    out 0xA0, al
    
    pop rax
    sti
    iretq
%endmacro


GLOBAL sys_42
sys_42:
    push    rbp
    mov     rbp, rsp
    mov     rax, 42
    int     80h
    pop     rbp
    retn



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


idt_pic_master_set_map:
    push    rbp
    mov     rbp, rsp
    push	rax
    mov 	al, dil
    out		20h, al
    pop 	rax
    pop 	rbp
    retn


idt_pic_slave_set_map:
    push    rbp
    mov     rbp, rsp
    push	rax
    mov 	al, dil
    out		0A0h, al
    pop 	rax
    pop 	rbp
    retn


;Int 80h
_irq_sys_handler:
	cli
	call sys_handler
	sti
	iretq


; PIC Master ints
_idt_irq_master_handler 20h
_idt_irq_master_handler 21h
_idt_irq_master_handler 22h
_idt_irq_master_handler 23h
_idt_irq_master_handler 24h
_idt_irq_master_handler 25h
_idt_irq_master_handler 26h
_idt_irq_master_handler 27h

; PIC Slave ints
_idt_irq_slave_handler 70h
_idt_irq_slave_handler 71h
_idt_irq_slave_handler 72h
_idt_irq_slave_handler 73h
_idt_irq_slave_handler 74h
_idt_irq_slave_handler 75h
_idt_irq_slave_handler 76h
_idt_irq_slave_handler 77h


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