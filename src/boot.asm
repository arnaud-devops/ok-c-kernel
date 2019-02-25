;boot.asm

global start					; set symbols from source code - our entry point
extern kmain					; kmain defined in kmain.c

section .multiboot_header
header_start:
    dd 0xe85250d6                ; magic number (multiboot 2 spec)
    dd 0                         ; architecture 0
    dd header_end - header_start ; header length

    ; checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    ; required end tag
    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size
header_end:

start:
	cli					        ; block interrupts - clear interrupt flag
	mov esp, stack_space	    ; set stack pointer - GRUB does this for us and stack pointer is already set,
	                            ; but just to be sure we allocate some memory in BSS section
	call kmain				    ; call our main function
	hlt					        ; halt the CPU

section .bss align=16
	resb 8192				    ; 8KB for stack

stack_space:
