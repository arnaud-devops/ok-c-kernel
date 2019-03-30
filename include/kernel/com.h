//
// Created by oxynux on 2/24/19.
//

#ifndef OXYNUX_COM_H
#define OXYNUX_COM_H

#include "kernel.h"

#define COM1 0x3F8

void    com1_init(void);
int     com1_transmit_empty(void);
void    com1_write_serial(char a);
void    com1_print_to_serial(char *s);

#endif //OXYNUX_COM_H
