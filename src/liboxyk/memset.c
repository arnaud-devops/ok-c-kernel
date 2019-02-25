//
// Created by oxynux on 2/20/19.
//

#include "liboxyk.h"

void	*memset(void *b, int c, size_t len)
{
    unsigned char	*p;

    p = b;
    while (len--)
        *p++ = (unsigned char)c;
    return (b);
}
