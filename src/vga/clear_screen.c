//
// Created by oxynux on 2/20/19.
//

#include "kernel/vga.h"

void clear_screen(void)
{
    char *video = (char*)VID_MEMORY;
    unsigned int i = 0;

    /*
     * This loop clears the screen
     * There are 25 lines each of 80 colums, each element takes 2 bytes
     */
    while (i < MAX_COLUMNS * MAX_LINES * 2)
    {
        *video++ = ' '; /* Blank character on all screen */
        *video++ = LIGHT_GREY; /* Each character on two bytes - character + colors */
        i = i + 2;
    }
}