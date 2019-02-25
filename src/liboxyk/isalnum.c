//
// Created by oxynux on 2/23/19.
//

#include "liboxyk.h"

int		isalnum(int c)
{
    return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z'));
}
