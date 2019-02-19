#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>


/*
 * Video Memory begin
 */

#define VID_MEMORY		0x0b8000
#define VGA_WIDTH       80

/*
 * Max Columns and Lines
 */

#define MAX_COLUMNS		80
#define MAX_LINES		25

/*
 * Colors
 */

#define BLACK			0x00
#define BLUE			0x01
#define GREEN			0x02
#define CYAN			0x03
#define RED			    0x04
#define MAGENTA			0x05
#define BROWN			0x06
#define LIGHT_GREY		0x07
#define DARK_GREY		0x08
#define LIGHT_BLUE		0x09
#define LIGHT_GREEN		0x0a
#define LIGHT_CYAN		0x0b
#define LIGHT_RED		0x0c
#define LIGHT_MAGENTA	0x0d
#define LIGHT_BROWN		0x0e
#define WHITE			0x0f

int getchar(_Bool caps);
//void init_gdt(void);

//
//struct gdtr {
//    uint16_t limite;
//    uint32_t base;
//} __attribute__ ((packed));
//
//struct gdtdesc {
//    uint16_t lim0_15;
//    uint16_t base0_15;
//    uint8_t base16_23;
//    uint8_t acces;
//    uint8_t lim16_19:4;
//    uint8_t other:4;
//    uint8_t base24_31;
//} __attribute__ ((packed));

#define GDTBASE    0x00000800

#endif
