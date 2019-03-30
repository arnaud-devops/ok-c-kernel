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
        kputchar(i + 48);
    }
    else
    {
        kputnbr(i / 10);
        kputnbr(i % 10);
    }
}