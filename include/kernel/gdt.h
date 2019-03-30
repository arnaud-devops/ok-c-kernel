    //
// Created by oxynux on 2/27/19.
//

#ifndef OXYNUX_GDT_H
#define OXYNUX_GDT_H

#include "kernel.h"

#define GDT_ENTRIES     7 // number of GDT entries (null, kcode, kdata, kstack, ucode, udata, ustack)
#define GDT_ENTRY_SIZE  64 // size of a GDT descriptor (64bits)
#define GDT_SIZE        GDT_ENTRY_SIZE * GDT_ENTRIES
#define GDT_LIMIT       GDT_SIZE - 1
#define GDT_BASE        0x00000800 // GDT load address

/* Access (8 bits)
 * Bit 7: Present, 1 if segment is present, else 0.
 * Bits 6 & 5: Privilege/Ring number, 00 if ring 0 (kernel), 11 if ring 3 (user).
 * Bit 4: Descriptor type, 0 if it's a system descriptor (TSS), 1 if it's a code/data/stack descriptor.
 * Bit 3: Executable bit, 1 if code in this segment can be executed (code), else 0 (data/stack).
 * Bit 2: Direction bit, 0 if expand up (data/code), 1 if expand down (stack).
 * Bit 1: R/W bit, readable bit for code descriptor, writable bit for data/stack descriptor.
 *        Code descriptor: 1 if readable else 0 (NB: even if 0 code is always writable).
 *        Data/Stack descriptor: 1 if writable else 0 (NB: even if 0 data/stack is always readable).
 * Bit 0: Accessed bit, just set to 0, the CPU sets this to 1 when the segment is accessed.
 */
#define GDT_NULL    0x00 // 0000 0000
#define GDT_KCODE   0x9A // 1001 1010
#define GDT_KDATA   0x92 // 1001 0010
#define GDT_KSTACK  0x96 // 1001 0110
#define GDT_UCODE   0xFA // 1111 1010
#define GDT_UDATA   0xF2 // 1111 0010
#define GDT_USTACK  0xF6 // 1111 0110

/* Granularity (4 bits)
 * Bit 3: Granularity bit
 *        0 if limit is expressed in 1B blocks (byte granularity)
 *        1 if limit is expressed in 4KiB blocks (page granularity)
 * Bit 2: Size bit
 *        0 if the selector defines 16 bit protected mode
 *        1 if the selector defines 32 bit protected mode
 * Bit 1: Always 0
 * Bit 0: Freely available
 */
#define GDT_PAGE_BLOCK  0x0C // (0000) 1100

// GDT segment descriptor
struct gdtdesc
{

    uint16_t limit_low; // limit bits 0 to 15
    uint16_t base_low; // base bits 0 to 15
    uint8_t base_middle; // base bits 0 to 23
    uint8_t access;
    uint8_t limit_high:4; // limit bits 16 to 19
    uint8_t granularity:4;
    uint8_t base_high; // base bits 24 to 31
} __attribute__ ((packed));

// GDT register
struct gdtr
{
    uint16_t limit; // GDT_LIMIT (GDT_ENTRY_SIZE * GDT_ENTRIES - 1)
    uint32_t base; // GDT_BASE (GDT load address)
} __attribute__ ((packed));

void gdt_init(void);
void gdt_set_desc(uint32_t base, uint32_t limit, uint8_t access, uint8_t gran, struct gdtdesc *desc);
extern void	gdt_flush(uint32_t);

#endif //OXYNUX_GDT_H
