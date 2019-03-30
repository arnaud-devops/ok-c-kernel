//
// Created by oxynux on 3/14/19.
//

#include "liboxyk.h"

char	*strcpy(char *dst, const char *src)
{
    char	*ret;

    ret = dst;
    while ((*dst++ = *src++))
        ;
    return (ret);
}
