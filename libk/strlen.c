//
// Created by oxynux on 2/17/19.
//

#include "libk.h"

size_t strlen(const char *str)
{
	const char *s;

	for (s = str; *s; ++s)
		;
	return (s - str);
}