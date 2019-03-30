;boot.asm

global start					; our entry point
global stack_top
extern kmain					; kmain is defined in kmain.c

section .multiboot_header
header_start:
    dd 0xe85250d6                   ; magic number (multiboot 2 spec)
    dd 0                            ; architecture 0 (x86_32 bit)
    dd header_end - header_start    ; header length

    ; checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    ; required end tag
    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size
header_end:

section .text
start:
	cli					        ; block interrupts - clear interrupt flag
	mov esp, stack_top  	    ; set stack pointer - GRUB does this for us and stack pointer is already set,
	                            ; but just to be sure we allocate some memory in BSS section
	call kmain				    ; call our main function
	hlt					        ; halt the CPU
start_end:

section .bss
stack_bottom:
	resb 4096				    ; 4Kbits for stack
stack_top:
