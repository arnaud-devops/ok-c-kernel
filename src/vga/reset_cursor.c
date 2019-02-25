//
// Created by oxynux on 2/25/19.
//

#include "kernel/vga.h"

void reset_cursor(void) {
    update_cursor(0,0);
}