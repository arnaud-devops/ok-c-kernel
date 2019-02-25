//
// Created by oxynux on 2/20/19.
//

#include "liboxyk.h"

size_t strlen(const char *str)
{
    const char *s;

    for (s = str; *s; ++s)
        ;
    return (s - str);
}