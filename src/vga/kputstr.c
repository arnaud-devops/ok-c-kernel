//
// Created by oxynux on 2/24/19.
//

#include "kernel/vga.h"

void kputstr(char *s)
{
    int i = 0;
    while (s[i] != 0)
    {
        kputchar(s[i]);
        i++;
    }
}