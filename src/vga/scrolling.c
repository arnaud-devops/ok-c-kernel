//
// Created by oxynux on 3/12/19.
//

#include "kernel/vga.h"

void scroll(void) {
    unsigned int i = 0;

    memmove((char *)VID_MEMORY, (char *)(VID_MEMORY + MAX_COLUMNS * 2), MAX_COLUMNS * (MAX_LINES - 1) * 2);

    vidptr = (char *)(VID_MEMORY + MAX_COLUMNS * (MAX_LINES - 1) * 2);
    while (i < MAX_COLUMNS * 2) {
        vidptr[i++] = ' ';
        vidptr[i++] = WHITE;
    }
}