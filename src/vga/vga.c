//
// Created by oxynux on 2/20/19.
//

#include "kernel/vga.h"

int column(void)
{
    return (int)(((vidptr - (char *)VID_MEMORY) / 2) % 80);
}

int line(void)
{
    return (int)(((vidptr - (char *)VID_MEMORY) / 2) / 80);
}

void enter(void)
{
    vidptr = (char *)VID_MEMORY + 80 * 2 * (line() + 1);
}

void del(void)
{
    if (vidptr - 2 < (char *)VID_MEMORY)
        vidptr = vidptr - 2 + (MAX_COLUMNS * MAX_LINES * 2);
    vidptr--;
    *vidptr = WHITE;
    vidptr--;
    *vidptr = ' ';
}

void arrow_up(void)
{
    if ((int)vidptr - MAX_COLUMNS * 2 < (int)VID_MEMORY)
        vidptr = vidptr - MAX_COLUMNS * 2 + (80 * 25 * 2);
    else
        vidptr -= MAX_COLUMNS * 2;
}

void arrow_down(void)
{
    if ((int)vidptr + MAX_COLUMNS * 2 > (int)VID_MEMORY + (80 * 25 * 2))
        vidptr = vidptr + MAX_COLUMNS * 2 - (80 * 25 * 2);
    else
        vidptr += MAX_COLUMNS * 2;
}

void arrow_right(void)
{
    if ((int)vidptr + 2 > (int)VID_MEMORY + (80 * 25 * 2))
        vidptr = vidptr + 2 - (80 * 25 * 2);
    else
        vidptr += 2;
}

void arrow_left(void)
{
    if ((int)vidptr - 2 < (int)VID_MEMORY)
        vidptr = vidptr - 2 + (80 * 25 * 2);
    else
        vidptr -= 2;
}