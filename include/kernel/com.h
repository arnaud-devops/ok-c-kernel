//
// Created by oxynux on 2/24/19.
//

#ifndef OXYNUX_COM_H
#define OXYNUX_COM_H

#include "kernel.h"

#define COM1 0x3F8

void    init_serial(void);
int     is_transmit_empty(void);
void    write_serial(char a);
void    print_to_serial(char *s);

#endif //OXYNUX_COM_H
