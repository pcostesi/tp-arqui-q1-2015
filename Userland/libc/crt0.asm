SECTION .text

EXTERN main

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
    push 	RDI
    push 	RSI
    push 	RDX
    push 	RCX
    push 	R8
    push 	R9
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
    pop 	R9
    pop 	R8
    pop 	RCX
    pop 	RDX
    pop 	RSI
    pop 	RDI
%endmacro

%macro ENTER 0
    push    rbp
    mov     rbp, rsp
%endmacro

%macro LEAVE 0
    mov     rsp, rbp
    pop     rbp
    ret
%endmacro


;kinda like crt0 but hacky
GLOBAL _start
_start:
    ENTER
    PUSHALL
    call 	main
    POPALL
    LEAVE
