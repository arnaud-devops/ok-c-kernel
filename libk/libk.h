//
// Created by oxynux on 2/17/19.
//

#ifndef KFS_LIBK_H
#define KFS_LIBK_H

#include <stddef.h>

int     memcmp(const void *s1, const void *s2, size_t n);
void    *memcpy(void *s1, const void *s2, size_t n);
void    *memmove(void *s1, const void *s2, size_t n);
void    *memset(void *b, int c, size_t len);
size_t  strlen(const char *str);

#endif //KFS_LIBK_H
