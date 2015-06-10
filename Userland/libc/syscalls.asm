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

%macro _int80h 2
GLOBAL %1
%1:
    ENTER
	mov rax, %2
	int 80h
    LEAVE
%endmacro


_int80h	write, 0
_int80h read, 1
_int80h ioctl, 6
_int80h pause, 34
_int80h halt, 48
_int80h shutdown, 48
_int80h towel, 32
_int80h gettime, 300
_int80h settime, 301
