//
// Created by oxynux on 3/29/19.
//

#include "liboxyk.h"

/* getsp() return the value pointed by ESP register (Stack Pointer) */
inline uint32_t getsp(void)
{
    uint32_t sp;
    asm volatile ( "mov %%esp, %0"
    : "=rm"(sp) );
    return sp;
}