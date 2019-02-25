//
// Created by oxynux on 2/20/19.
//

#ifndef OXYNUX_LIBOXYK_H
#define OXYNUX_LIBOXYK_H

#include "freestanding.h"

uint8_t inb(uint16_t port);
void    outb(uint16_t port, uint8_t val);
void    *memcpy(void *s1, const void *s2, size_t n);
void    *memmove(void *s1, const void *s2, size_t n);
void    *memset(void *b, int c, size_t len);
size_t  strlen(const char *str);
int		isalnum(int c);
int		isalpha(int c);
int		isascii(int c);
int		isdigit(int c);
int		islower(int c);
int		isprint(int c);
int		isspace(int c);
int		isupper(int c);
int		strncmp(const char *s1, const char *s2, size_t n);

#endif //OXYNUX_LIBOXYK_H
