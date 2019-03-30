//
// Created by oxynux on 2/24/19.
//

#include "kernel/kshell.h"

int cmd_parse(char *buf)
{
    if (strncmp(buf, "reboot", 6) == 0) {
        reboot();
    } else if (strncmp(buf, "draw", 4) == 0) {
        draw_mode();
    } else if (strncmp(buf, "stackdump_com1", 14) == 0) {
        com1_print_to_serial(buf);
        com1_write_serial('\n');
        unsigned int addr = (unsigned int)&stack_top;
        for (int i = 0; i < 4096 / 16; i++) {
            hexdump_com1((void *) addr);
            addr -= 16;
        }
    } else if (strncmp(buf, "stackdump_vga", 13) == 0) {
        unsigned int addr = (unsigned int)&stack_top;
        for (int i = 0; i < 4096 / 16; i++) {
            hexdump_vga((void *) addr);
            addr -= 16;
        }
    } else if (strncmp(buf, "espdump_vga", 11) == 0) {
        unsigned int addr = (unsigned int)getsp();
        for (int i = 0; i < 64 / 16; i++) {
            hexdump_vga((void *) addr);
            addr -= 16;
        }
    } else if (strncmp(buf, "espdump_com1", 12) == 0) {
        com1_print_to_serial(buf);
        com1_write_serial('\n');
        unsigned int addr = (unsigned int)getsp();
        for (int i = 0; i < 64 / 16; i++) {
            hexdump_com1((void *) addr);
            addr -= 16;
        }
    } else if (strncmp(buf, "gdtdump", 7) == 0) {
        unsigned int addr = 0x800;
        for (int i = 0; i < 64 / 16; i++) {
            hexdump_vga((void *) addr);
            addr += 16;
        }
    }
}