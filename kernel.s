;;kernel.s

bits 32						; compile in 32 bits - explicit
section .text					; begin text section, where we'll put all of our code
	; multiboot spec
	align 4					; multiboot header must contain 3 fields that are 4 byte aligned namely
	dd 0x1BADB002				; multiboot magic number
	dd 0x0					; architecture 0 - i386 - 32bits
	dd - (0x1BADB002 + 0x00)		; the checksum field when added to the fields magic and flags must give zero.

global start					; set symbols from source code - our entry point
extern kmain					; kmain defined in kmain.c

start:
	cli					; block interrupts - clear interrupt flag
	mov esp, stack_space			; set stack pointer - GRUB does this for us and stack pointer is already set, but just to be sure we allocate some memory in BSS section
	call kmain				; call our main function
	hlt					; halt the CPU

section .bss align=16
	resb 8192				; 8KB for stack

stack_space:
