//
// Created by oxynux on 2/24/19.
//

#ifndef OXYNUX_KSHELL_H
#define OXYNUX_KSHELL_H

#include "kernel.h"
#include "kernel/system.h"
#include "kernel/com.h"
#include "kernel/keyboard.h"
#include "kernel/memdump.h"

void    prompt(void);
void    kshell(void);
int     cmd_parse(char *buf);

#endif //OXYNUX_KSHELL_H
