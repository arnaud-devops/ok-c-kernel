//
// Created by oxynux on 3/13/19.
//

#include "kernel/kshell.h"

bool caps = 0;
char buf[78];

void prompt(void)
{
    kputstr("$ ");
}

void kshell(void) {
    int c;
    static char i = 0;
    prompt();
    while (1) {
        c = getchar(caps);
        if (c == '\n') {
            i = 0;
            kputchar(c);
            cmd_parse(buf);
            memset(buf, 0, 78);
            prompt();
        } else if (isprint(c) && (column() >= 2 && column() < 79)) {
            buf[i] = c;
            kputchar(c);
            i++;
        } else if (c == 253 && column() > 2) {
            vidptr--;
            *vidptr = WHITE;
            vidptr--;
            *vidptr = ' ';
            buf[i] = ' ';
            i--;
        } else if (c == 155 || c == 156 || c == 157 || c == -156 || c == -157 || (c >= 200 && c <= 209))
            kputchar(c);
        cursor_update(column(),line());
    }
}