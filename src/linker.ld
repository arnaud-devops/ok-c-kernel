/*
 * linker.ld
 */

/*
 * The linker merges all text sections of the object files to the executable text section
 * Similarly, the data and bss sections are merged and placed at the then values of location-counter.
 */

OUTPUT_FORMAT(elf32-i386)	/* Output format of our executable */
ENTRY(start)				/* Specify the entry point of our executable */
SECTIONS					/* Layout of our executable */
 {
	. = 0x100000;		    /* Kernel's code start at 1M */
	.boot : { *(.multiboot_header) }
	.text : { *(.text) }
	.data : { *(.data) }
	.bss  : { *(.bss) }
 }
