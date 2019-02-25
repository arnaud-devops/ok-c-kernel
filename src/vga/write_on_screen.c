//
// Created by oxynux on 2/20/19.
//

#include "kernel/vga.h"

void write_on_screen(const char *str, char *vidptr)
{
    unsigned int i = 0, j = 0;

    /*
     * This loop write the string to video memory
     */
    while (str[j] != '\0')
    {
        /* ASCII character */
        vidptr[i] = str[j];
        /* Color character */
        vidptr[i+1] = RED;
        /* Next character of our string 'Hello World' */
        j++;
        /* Next character written on kernel screen on 2 bytes */
        i = i + 2;
    }
}