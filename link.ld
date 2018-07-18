/*
 * link.ld
 */

/*
 * The linker merges all text sections of the object files to the executable text section
 * Similarly, the data and bss sections are merged and placed at the then values of location-counter.
 */

OUTPUT_FORMAT(elf32-i386) 		/* Output format of our executablee*/
ENTRY(start)				/* Specify the entry point of our exexutable */
SECTIONS				/* Layout of our executable */
 {
	. = 0x100000;			/* Kernel's code start at the adresses 0x100000 */
	.text : { *(.text) }		/* The asterisk (*) is a wildcard character that matches any file name */
	.data : { *(.data) }
	.bss  : { *(.bss)  }
 }
