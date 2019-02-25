//
// Created by oxynux on 2/20/19.
//

#ifndef OXYNUX_VGA_H
#define OXYNUX_VGA_H

#include "kernel.h"
#include "kernel/keyboard.h"

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
void        write_on_screen(const char *str, char *vidptr);
void        clear_screen(void);
void        enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void        update_cursor(int x, int y);
int         column(char *video);
int         line(char *video);
void        enter(char **video);
void        del(char **video);
void        arrow_up(char **video);
void        arrow_down(char **video);
void        arrow_right(char **video);
void        arrow_left(char **video);
void        reset_cursor(void);

#endif //OXYNUX_VGA_H
