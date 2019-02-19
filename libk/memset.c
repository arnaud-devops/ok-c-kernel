//
// Created by oxynux on 2/17/19.
//

#include "libk.h"

void	*memset(void *b, int c, size_t len)
{
    unsigned char	*p;

    p = b;
    while (len--)
        *p++ = (unsigned char)c;
    return (b);
}
