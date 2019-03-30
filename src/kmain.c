//
// Created by oxynux on 2/20/19.
//

#include "kernel.h"

char *vidptr;

void kmain(void)
{
    vidptr = (char*)VID_MEMORY;
    gdt_init();
    com1_init();
    cursor_init(14, 15);
    khello();
    kenv();
}

void khello(void)
{
    kputstr("Hello World from VGA!");
    com1_print_to_serial("Hello World from COM1!\n");
}

void kenv(void)
{
    char c;

    while (1) {
        c = getchar(0);
        if (c != 0) {
            cursor_reset();
            clear_screen();
            vidptr = (char*)VID_MEMORY;
            kshell();
        }
    }
}
