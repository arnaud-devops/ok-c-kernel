//
// Created by oxynux on 2/27/19.
//

#include "kernel/gdt.h"

struct gdtdesc gdt[GDT_ENTRIES];
struct gdtr gdt_r;

void gdt_set_desc(uint32_t base, uint32_t limit, uint8_t access, uint8_t gran, struct gdtdesc *desc)
{
    desc->limit_low = limit & 0xFFFF; // 16bits
    desc->base_low = base & 0xFFFF; // 16bits
    desc->base_middle = (base >> 16) & 0xFF; // 8bits
    desc->access = access; // 8bits
    desc->limit_high = (limit >> 16) & 0x0F; // 4bits
    desc->granularity = gran & 0x0F; // 4bits
    desc->base_high = (base >> 24) & 0xFF; // 8bits
}

void gdt_set_null_seg(struct gdtdesc *desc)
{
    gdt_set_desc(0x0, 0x0, GDT_NULL, 0x0, desc);
}

void gdt_set_kcode_seg(struct gdtdesc *desc)
{
    gdt_set_desc(0x0, 0xFFFFF, GDT_KCODE, GDT_PAGE_BLOCK, desc);
}

void gdt_set_kdata_seg(struct gdtdesc *desc)
{
    gdt_set_desc(0x0, 0xFFFFF, GDT_KDATA, GDT_PAGE_BLOCK, desc);
}

void gdt_set_kstack_seg(struct gdtdesc *desc)
{
    gdt_set_desc(0x0, 0xFFFFF, GDT_KSTACK, GDT_PAGE_BLOCK, desc);
}

void gdt_set_ucode_seg(struct gdtdesc *desc)
{
    gdt_set_desc(0x0, 0xFFFFF, GDT_UCODE, GDT_PAGE_BLOCK, desc);
}

void gdt_set_udata_seg(struct gdtdesc *desc)
{
    gdt_set_desc(0x0, 0xFFFFF, GDT_UDATA, GDT_PAGE_BLOCK, desc);
}

void gdt_set_ustack_seg(struct gdtdesc *desc)
{
    gdt_set_desc(0x0, 0xFFFFF, GDT_USTACK, GDT_PAGE_BLOCK, desc);
}

void gdt_init(void)
{
    gdt_r.limit = GDT_LIMIT;
    gdt_r.base = GDT_BASE;
    
    gdt_set_null_seg(&gdt[0]);
    
    gdt_set_kcode_seg(&gdt[1]);
    gdt_set_kdata_seg(&gdt[2]);
    gdt_set_kstack_seg(&gdt[3]);

    gdt_set_ucode_seg(&gdt[4]);
    gdt_set_udata_seg(&gdt[5]);
    gdt_set_ustack_seg(&gdt[6]);
    
    memcpy((uint8_t *)gdt_r.base, &gdt, gdt_r.limit);

    gdt_flush((uint32_t)&gdt_r);
}
