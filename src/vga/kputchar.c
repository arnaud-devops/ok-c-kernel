//
// Created by oxynux on 2/20/19.
//

#include "kernel/vga.h"

extern bool caps;

void kputchar(int c)
{
    static char *video = (char*)VID_MEMORY;
    static char color = WHITE;

    switch (c)
    {
        case 150:
            arrow_up(&video);
            break;
        case 151:
            arrow_left(&video);
            break;
        case 152:
            arrow_right(&video);
            break;
        case 153:
            arrow_down(&video);
            break;
        case 200:
            color = BLUE;
            break;
        case 201:
            color = GREEN;
            break;
        case 202:
            color = CYAN;
            break;
        case 203:
            color = RED;
            break;
        case 204:
            color = MAGENTA;
            break;
        case 205:
            color = BROWN;
            break;
        case 206:
            color = LIGHT_BLUE;
            break;
        case 207:
            color = LIGHT_GREEN;
            break;
        case 208:
            color = LIGHT_RED;
            break;
        case 209:
            color = WHITE;
            break;
        case 253:
            del(&video);
            break;
        case 255:
            enter(&video);
            break;
        case 155:
        case 156:
        case 157:
        case -156:
        case -157:
            caps = !caps;
            break;
        default:
            if (c < 0) /* TODO clean this crap!!!!! */
                break;
            *video++ = (char)c;
            *video++ = color;
            break;
    }
    if (video == (char*)(VID_MEMORY + MAX_COLUMNS * MAX_LINES * 2))
        video = (char *) VID_MEMORY;
    update_cursor(column(video), line(video));
}