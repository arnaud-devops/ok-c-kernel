#include "include/kernel.h"

unsigned char kbdus[128] = {
	0, // error
	0, // esc
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'-', '=',
	'\b', // backspace
	'\t', // tab
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
	'\n', // enter
	0, // left ctrl
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	0, // left shift
	'\\', 'z', 'x', 'c', 'v', 'b', 'n',
	'm', ',', '.', '/',
	0, // right shift
	'*',
	0, // left alt
	' ', // space
	0, // caps-lock
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // f1->f12
	0, // numlock
	0, // scroll lock
	0, // home
	0, // up
	0, // page up
	'-',
	0, // left
	0, // keypad 5
	0, // right
	'+',
	0, // end
	0, // down
	0, // page down
	0, // insert
	0, // del
	0, // Alt-SysRq ?
	0, // Fn?
	0, // Cmd/Super?
	0, // f11
	0, // f12
	0, // undefined
};

static inline void outb(uint16_t port, uint8_t val)
{
	asm volatile ( "outb %0, %1"
			:
			: "a"(val), "Nd"(port) );
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ( "inb %1, %0"
			: "=a"(ret)
			: "Nd"(port) );
	return ret;
}

// https://stackoverflow.com/questions/46608895/
static char get_scancode()
{
	char c = 0;
	outb(0x60, 0x0);
	do {
		if(inb(0x60) != c){
			c = inb(0x60);
			if(c > 0)
				return c;
		}
	} while(1);
}

char getchar() {
	return kbdus[get_scancode()];
}

