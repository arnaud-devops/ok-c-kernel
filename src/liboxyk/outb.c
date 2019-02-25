//
// Created by oxynux on 2/20/19.
//

#include "liboxyk.h"

/*
 *
 * outb: output byte in AL (here it's val and 0x0 in keyboard.c get_scancode() function)
 *       to I/O port address in DX (here it's port and 0x60 in get_scancode())
 *
 * a: constraint mean use the A register (in this case AL)
 * Nd: constraint mean:
 * 	N: force 8-bit integer constant
 * 	d: use the D register (in this case DX)
 *
 * x86 OUT (Output to Port) :
 * Copies the value from the second operand (source operand)
 * to the I/O port specified with the destination operand (first operand).
 *
 */
inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1"
    :
    : "a"(val), "Nd"(port) );
}
