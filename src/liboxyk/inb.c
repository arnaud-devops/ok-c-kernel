//
// Created by oxynux on 2/20/19.
//

#include "liboxyk.h"

/*
 *
 * inb: take I/O port address in DX (here it's port and 0x60 in keyboard.c get_scancode() function)
 * 	and return the I/O port value in AL (here ret and c= in get_scancode())
 *
 * =a: constraint mean use the A register (in this case AL) and copy it to
 *     ret as output
 *
 * Nd: constraint mean:
 * 	N: force 8-bit integer constant
 * 	d: use the D register (in this case DX)
 *
 * x86 IN (Input from Port) :
 * Copies the value from the I/O port
 * specified with the second operand (source operand)
 * to the destination operand (first operand).
 *
 */
inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
    : "=a"(ret)
    : "Nd"(port) );
    return ret;
}