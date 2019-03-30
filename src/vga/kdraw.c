//
// Created by oxynux on 3/13/19.
//

#include "kernel/vga.h"

void kdraw(int c)
{
    static char color = WHITE;

    switch (c)
    {
        case 150:
            arrow_up();
            break;
        case 151:
            arrow_left();
            break;
        case 152:
            arrow_right();
            break;
        case 153:
            arrow_down();
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
            break;
        case '\n':
            break;
        case 155:
        case 156:
        case 157:
        case -156:
        case -157:
            caps = !caps;
            break;
        default:
            if (c < 0)
                break;
            *vidptr++ = (char)c;
            *vidptr++ = color;
            break;
    }
}