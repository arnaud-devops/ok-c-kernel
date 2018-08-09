/*
 * kmain.c
 */

#include "include/kernel.h"

static void ft_write_on_screen(const char *str, char *vidptr)
{
	unsigned int i, j = 0;

	/*
	 * This loop write the string to video memory
	 */
	while (str[j] != '\0')
	{
		/* ASCII character */
		vidptr[i] = str[j];
		/* Color character */
		vidptr[i+1] = RED;
		/* Next character of our string 'Hello World' */
		j++;
		/* Next character written on kernel screen on 2 bytes */
		i = i + 2;
	}
}

static void ft_clear_screen()
{
	char *video = (char*)VID_MEMORY;
	unsigned int i = 0;

	/*
	 * This loop clears the screen
	 * There are 25 lines each of 80 colums, each element takes 2 bytes
	 */
	while (i < MAX_COLUMNS * MAX_LINES * 2)
	{
		*video++ = ' '; /* Blank character on all screen */
		*video++ = LIGHT_GREY; /* Each character on two bytes - character + colors */
		i = i + 2;
	}
}

static void kputchar(char c) {
	static char *video = (char*)VID_MEMORY;

	*video++ = c;
	*video++ = CYAN;
}

static void basic_kbd() {
	char c;

	while (1) {
		c = getchar();
		if (c != 0)
			kputchar(c);
	}
}

void kmain(void)
{
	const char *str = "Hello World!"; /* Message which will be displayed on Kernel screen */
	char *vidptr = (char*)VID_MEMORY; /* Videos memory begin here */
	char c;

	ft_clear_screen();
	ft_write_on_screen(str, vidptr);
	while (1) {
		c = getchar();
		if (c != 0) {
			ft_clear_screen();
			basic_kbd();
		}
	}
	return ;
}
