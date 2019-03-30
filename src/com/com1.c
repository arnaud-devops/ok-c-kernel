//
// Created by oxynux on 2/20/19.
//

#include "kernel/com.h"

void com1_init() {
    outb(COM1 + 1, 0x00);    // Disable all interrupts
    outb(COM1 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(COM1 + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(COM1 + 1, 0x00);    //                  (hi byte)
    outb(COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

int com1_transmit_empty() {
    return inb(COM1 + 5) & 0x20;
}

void com1_write_serial(char a) {
    while (com1_transmit_empty() == 0);

    outb(COM1,a);
}

void com1_print_to_serial(char *s) {
    int i = 0;
    while (s[i] != 0) {
        com1_write_serial(s[i]);
        i++;
    }
}