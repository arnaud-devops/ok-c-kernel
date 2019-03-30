//
// Created by oxynux on 3/14/19.
//

#ifndef OXYNUX_MEMDUMP_H
#define OXYNUX_MEMDUMP_H

#include "kernel.h"
#include "liboxyk.h"

static void	print_offset_com1(void *addr);
static void	print_hex_value_com1(void *addr);
static void	print_ascii_value_com1(void *addr);
void	hexdump_com1(void *addr);
static void	print_offset_vga(void *addr);
static void	print_hex_value_vga(void *addr);
static void	print_ascii_value_vga(void *addr);
void	hexdump_vga(void *addr);
char	*to_hex_16(uint16_t key);
char	*to_hex_32(uint32_t key);
char	*to_hex_8(uint8_t key);

#endif //OXYNUX_MEMDUMP_H
