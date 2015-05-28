global loader
extern main
extern initializeKernelBinary

loader:
	call initializeKernelBinary	; Set up the kernel binary, and get thet stack address
	mov rsp, rax				; Set up the stack with the returned address
	push rax
	call main
hang:
	hlt							; halt machine should kernel return
	cli
	jmp hang
