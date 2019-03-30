//
// Created by oxynux on 2/20/19.
//

#ifndef OXYNUX_KERNEL_H
#define OXYNUX_KERNEL_H

#include "liboxyk.h"
#include "kernel/vga.h"
#include "kernel/com.h"
#include "kernel/gdt.h"

extern char *vidptr;
extern const uint8_t stack_top asm("stack_top");

void kmain(void);
void khello(void);
void kenv(void);

#endif //OXYNUX_KERNEL_H
