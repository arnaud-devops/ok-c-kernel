//
// Created by oxynux on 2/20/19.
//

#include "kernel/keyboard.h"

bool caps = 0;

unsigned char kbdus[2][128] = {{
                                       0, // error
                                       0, // esc
                                       '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
                                       '-', '=',
                                       253, // backspace
                                       0, // tab
                                       'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
                                       255, // enter
                                       0, // left ctrl
                                       'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
                                       156, // left shift
                                       '\\', 'z', 'x', 'c', 'v', 'b', 'n',
                                       'm', ',', '.', '/',
                                       157, // right SHIft
                                       '*',
                                       0, // left alt
                                       ' ', // space
                                       155, // caps-lock
                                       200, 201, 202, 203, 204, 205, 206, 207, 208, 209, // f1->f10
                                       0, // numlock
                                       0, // scroll lock
                                       0, // home
                                       150, // up
                                       0, // page up
                                       '-',
                                       151, // left
                                       0, // keypad 5
                                       152, // right
                                       '+',
                                       0, // end
                                       153, // down
                                       0, // page down
                                       0, // insert
                                       0, // del
                                       0, // Alt-SysRq ?
                                       0, // Fn?
                                       0, // Cmd/Super?
                                       0, // f11
                                       0, // f12
                                       0, // undefined
                               },

                               {
                                       0, // error
                                       0, // esc
                                       '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
                                       '_', '+',
                                       253, // backspace
                                       0, // tab
                                       'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
                                       255, // enter
                                       0, // left ctrl
                                       'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~',
                                       156, // left shift
                                       '|', 'Z', 'X', 'C', 'V', 'B', 'N',
                                       'M', '<', '>', '?',
                                       157, // right shift
                                       '*',
                                       0, // left alt
                                       ' ', // space
                                       155, // caps-lock
                                       200, 201, 202, 203, 204, 205, 206, 207, 208, 209, // f1->f10
                                       0, // numlock
                                       0, // scroll lock
                                       0, // home
                                       150, // up
                                       0, // page up
                                       '-',
                                       151, // left
                                       0, // keypad 5
                                       152, // right
                                       '+',
                                       0, // end
                                       153, // down
                                       0, // page down
                                       0, // insert
                                       0, // del
                                       0, // Alt-SysRq ?
                                       0, // Fn?
                                       0, // Cmd/Super?
                                       0, // f11
                                       0, // f12
                                       0, // undefined
                               } };


static unsigned char get_scancode()
{
    unsigned char c = 0;
    do {
        if(inb(0x64) & 0x01){
            c = inb(0x60);
            return c;
        }
    } while(1);
}

int getchar(bool caps) {
    int c = get_scancode();
    if (c > 128)
        return (-kbdus[caps][c - 128]);
    return kbdus[caps][c];
}

char buf[1024];

void basic_kbd(void) {
    int c;
    static int i = 0;
    while (1) {
        c = getchar(caps);
        if (c == 255) {
            i = 0;
            kputchar(c);
            cmd_parse(buf);
            memset(buf, 0, 1024);
        }
        else if (c != 0) {
            if(isprint(c)) {
                buf[i] = c;
                i++;
            }
            write_serial(buf[i]);
            kputchar(c);
        }
    }
}