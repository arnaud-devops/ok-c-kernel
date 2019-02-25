//
// Created by oxynux on 2/20/19.
//

#include "kernel.h"

void kmain(void)
{
    const char *str = "Hello World!"; /* Message which will be displayed on Kernel screen */
    char *vidptr = (char*)VID_MEMORY; /* Videos memory begin here */
    char c;

    init_serial();
    print_to_serial("BONJOUR!");

    // TODO implement init_gdt()

    clear_screen();
    enable_cursor(0, 15);
    while (1) {
        write_on_screen(str, vidptr);
//      kputstr((char *) str);
        reset_cursor();
        c = getchar(0);
        if (c != 0) {
            clear_screen();
            basic_kbd();
        }
    }
}
