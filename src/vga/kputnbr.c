//
// Created by oxynux on 2/20/19.
//

#include "kernel/vga.h"

void	kputnbr(int n)
{
    unsigned int i;

    i = n;
    if (n < 0)
    {
        kputchar('-');
        i = -n;
    }
    if (i < 10)
    {
        if (i == 0)
            kputchar('0');
        kputchar(kbdus[0][i + 1]);
    }
    else
    {
        kputnbr(i / 10);
        kputnbr(i % 10);
    }
}