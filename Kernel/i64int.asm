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


; see https://msdn.microsoft.com/en-us/library/6t169e9c.aspx
%macro PUSHALL 0
    push    RBX
    push    RDI
    push    RSI
    push    RSP
    push    R12
    push    R13
    push    R14
    push    R15
%endmacro

%macro POPALL 0
    pop     R15
    pop     R14
    pop     R13
    pop     R12
    pop     RSP
    pop     RSI
    pop     RDI
    pop     RBX
%endmacro

%macro ENTER 0
    push    rbp
    mov     rbp, rsp
    PUSHALL
%endmacro

%macro LEAVE 0
    POPALL
    pop     rbp
    ret
%endmacro

%macro _idt_irq_master_handler 1
GLOBAL _irq_%1_handler

_irq_%1_handler:
    cli
    push rax
    push rdi
    mov rdi, %1
    call irq_handler
    
    ;signal master pic
    mov al, 20h
    out 20h, al
    
    pop rdi
    pop rax
    sti
    iretq
%endmacro

%macro _idt_irq_slave_handler 1
GLOBAL _irq_%1_handler

_irq_%1_handler:
    cli
    push rax
    push rdi
    mov rdi, %1
    call irq_handler
    
    ;signal master pic
    mov al, 20h
    out 20h, al

    ;signal slave pic
    mov al, 0xA0
    out 0xA0, al
    
    pop rdi
    pop rax
    sti
    iretq
%endmacro


idt_pic_master_mask:
    ENTER
    mov 	al, dil
    out		21h, al
    LEAVE


idt_pic_slave_mask:
    ENTER
    mov 	al, dil
    out		0A1h, al
    LEAVE


idt_pic_master_set_map:
    ENTER
    mov 	al, dil
    out		20h, al
    LEAVE


idt_pic_slave_set_map:
    ENTER
    mov 	al, dil
    out		0A0h, al
    LEAVE


;Int 80h
_irq_sys_handler:
	cli
    push    RBP
    PUSHALL
	call sys_handler
    POPALL
    pop     RBP
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
    ENTER
    lidt 	[rdi]
    LEAVE


_sidt:
    ENTER
    sidt 	[rdi]
    LEAVE


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