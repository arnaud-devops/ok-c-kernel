/*
 * linker.ld
 */

/*
 * The linker merges all text sections of the object files to the executable text section
 * Similarly, the data and bss sections are merged and placed at the then values of location-counter.
 */

OUTPUT_FORMAT(elf32-i386)	/* Output format of our executablee*/
ENTRY(start)				/* Specify the entry point of our exexutable */
SECTIONS					/* Layout of our executable */
 {
	. = 1M;					/* Kernel's code start at 1M */
	.boot : { *(.multiboot_header) }
	.text : { *(.text) }	/* The asterisk (*) is a wildcard character that matches any file name */
	.data : { *(.data) }
	.bss  : { *(.bss) }
 }
