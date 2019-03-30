//
// Created by oxynux on 3/14/19.
//

#include "kernel/memdump.h"

static void	print_offset_com1(void *addr)
{
    // Print offset and padding
    com1_print_to_serial(to_hex_32((uint32_t)addr));
    com1_print_to_serial("  ");
}

static void	print_offset_vga(void *addr)
{
    // Print offset and padding
    kputstr(to_hex_32((uint32_t)addr));
    kputstr("  ");
}

static void	print_hex_value_com1(void *addr)
{
    // print hex value and padding
    for (int i = 0; i < 16; i++) {
        com1_print_to_serial(to_hex_8(*(uint8_t *)addr));

        if (i == 7)
            com1_print_to_serial("  ");
        else
            com1_print_to_serial(" ");

        addr++;
    }
    com1_print_to_serial(" |");
}

static void	print_hex_value_vga(void *addr)
{
    // print hex value and padding
    for (int i = 0; i < 16; i++) {
        kputstr(to_hex_8(*(uint8_t *)addr));

        if (i == 7)
            kputstr("  ");
        else
            kputstr(" ");

        addr++;
    }
    kputstr(" |");
}

static void	print_ascii_value_com1(void *addr)
{
    // Print value in ascii
    for (int i = 0; i < 16; i++) {
        if (isprint(*(uint8_t *)addr))
            com1_write_serial(*(uint8_t *)addr);
        else
            com1_write_serial('.');

        addr++;
    }
    com1_write_serial('|');
    com1_write_serial('\n');
}


static void	print_ascii_value_vga(void *addr)
{
    // Print value in ascii
    for (int i = 0; i < 16; i++) {
        if (isprint(*(uint8_t *)addr))
            kputchar(*(uint8_t *)addr);
        else
            kputchar('.');

        addr++;
    }
    kputchar('|');
    kputchar('\n');
}

void	hexdump_com1(void *addr)
{
    print_offset_com1(addr);
    print_hex_value_com1(addr);
    print_ascii_value_com1(addr);
}


void	hexdump_vga(void *addr)
{
    print_offset_vga(addr);
    print_hex_value_vga(addr);
    print_ascii_value_vga(addr);
}


char	*to_hex_32(uint32_t key)
{
    char	*value = "00000000";

    strcpy(&value[0], to_hex_8((key >> 24) & 0xFF));
    strcpy(&value[2], to_hex_8((key >> 16) & 0xFF));
    strcpy(&value[4], to_hex_8((key >> 8) & 0xFF));
    strcpy(&value[6], to_hex_8(key & 0xFF));

    return (value);
}

char	*to_hex_16(uint16_t key)
{
    char	*value = "0000";

    strcpy(&value[0], to_hex_8((key >> 8) & 0xFF));
    strcpy(&value[2], to_hex_8(key & 0xFF));

    return (value);
}

char	*to_hex_8(uint8_t key)
{
    char	*value = "00";
    char	*hex = "0123456789ABCDEF";

    value[0] = hex[(key >> 4) & 0xF];
    value[1] = hex[key & 0xF];

    return (value);
}