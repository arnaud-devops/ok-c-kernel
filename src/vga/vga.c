//
// Created by oxynux on 2/20/19.
//

#include "kernel/vga.h"

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void update_cursor(int x, int y)
{
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

int column(char *video)
{
    return (((video - (char *)VID_MEMORY) / 2) % 80);
}

int line(char *video)
{
    return (((video - (char *)VID_MEMORY) / 2) / 80);
}

void enter(char **video)
{
    *video = (char *)VID_MEMORY + 80 * 2 * (line(*video) + 1);
}

void del(char **video)
{
    if ((int)*video - 2 < (int)VID_MEMORY)
        *video = *video - 2 + (80 * 25 * 2);
    else
        *video -= 2;
    **video = ' ';
}

void arrow_up(char **video)
{
    if ((int)*video - MAX_COLUMNS * 2 < (int)VID_MEMORY)
        *video = *video - MAX_COLUMNS * 2 + (80 * 25 * 2);
    else
        *video -= MAX_COLUMNS * 2;
}

void arrow_down(char **video)
{
    if ((int)*video + MAX_COLUMNS * 2 > (int)VID_MEMORY + (80 * 25 * 2))
        *video = *video + MAX_COLUMNS * 2 - (80 * 25 * 2);
    else
        *video += MAX_COLUMNS * 2;
}

void arrow_right(char **video)
{
    if ((int)*video + 2 > (int)VID_MEMORY + (80 * 25 * 2))
        *video = *video + 2 - (80 * 25 * 2);
    else
        *video += 2;
}

void arrow_left(char **video)
{
    if ((int)*video - 2 < (int)VID_MEMORY)
        *video = *video - 2 + (80 * 25 * 2);
    else
        *video -= 2;
}