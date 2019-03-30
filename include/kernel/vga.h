//
// Created by oxynux on 2/20/19.
//

#ifndef OXYNUX_VGA_H
#define OXYNUX_VGA_H

#include "kernel.h"
#include "kernel/keyboard.h"
#include "kernel/vga.h"

#define VID_MEMORY		0x0b8000
#define VGA_WIDTH       80

#define MAX_COLUMNS		80
#define MAX_LINES		25

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

void        kputchar(int c);
void        kputstr(char *s);
void        kputnbr(int n);
void        clear_screen(void);
void        scroll(void);
int         column(void);
int         line(void);
void        enter(void);
void        del(void);
void        arrow_up(void);
void        arrow_down(void);
void        arrow_right(void);
void        arrow_left(void);
void        cursor_reset(void);
void        cursor_init(uint8_t cursor_start, uint8_t cursor_end);
void        cursor_update(int x, int y);
void        kdraw(int c);

#endif //OXYNUX_VGA_H
