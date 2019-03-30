//
// Created by oxynux on 2/20/19.
//

#ifndef OXYNUX_KEYBOARD_H
#define OXYNUX_KEYBOARD_H

#include "kernel.h"
#include "kernel/kshell.h"
#include "kernel/com.h"

extern unsigned char kbdus[2][128];
extern bool caps;

int     getchar(bool caps);
void    draw_mode(void);

#endif //OXYNUX_KEYBOARD_H
