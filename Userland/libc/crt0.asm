SECTION .text

EXTERN main

%macro ENTER 0
    push    rbp
    mov     rbp, rsp
%endmacro

%macro LEAVE 0
    pop     rbp
    ret
%endmacro

;kinda like crt0 but hacky
GLOBAL _start
_start:
    ENTER
    call main
    LEAVE