#include "include/kernel.h"

unsigned char kbdus[2][128] = {{
            0, // error
            0, // esc
            '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
            '-', '=',
            0, // tab
            253, // backspace
            'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
            255, // enter
            0, // left ctrl
            'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
            156, // left shift
            '\\', 'z', 'x', 'c', 'v', 'b', 'n',
            'm', ',', '.', '/',
            157, // right SHIft
            '*',
            0, // left alt
            ' ', // space
            155, // caps-lock
            200, 201, 202, 203, 204, 205, 206, 207, 208, 209, // f1->f10
            0, // numlock
            0, // scroll lock
            0, // home
            150, // up
            0, // page up
            '-',
            151, // left
            0, // keypad 5
            152, // right
            '+',
            0, // end
            153, // down
            0, // page down
            0, // insert
            0, // del
            0, // Alt-SysRq ?
            0, // Fn?
            0, // Cmd/Super?
            0, // f11
            0, // f12
            0, // undefined
            },

			{
			0, // error
            0, // esc
            '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
            '_', '+',
            253, // backspace
            0, // tab
            'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
            255, // enter
            0, // left ctrl
            'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~',
            156, // left shift
            '|', 'Z', 'X', 'C', 'V', 'B', 'N',
            'M', '<', '>', '?',
            157, // right shift
            '*',
            0, // left alt
            ' ', // space
            155, // caps-lock
            200, 201, 202, 203, 204, 205, 206, 207, 208, 209, // f1->f10
            0, // numlock
            0, // scroll lock
            0, // home
            150, // up
            0, // page up
            '-',
            151, // left
            0, // keypad 5
            152, // right
            '+',
            0, // end
            153, // down
            0, // page down
            0, // insert
            0, // del
            0, // Alt-SysRq ?
            0, // Fn?
            0, // Cmd/Super?
            0, // f11
            0, // f12
            0, // undefined
} };


/*
 *
 * outb: output byte in AL (here it's val and 0x0 in _scancode())
 *       to I/O port address in DX (here it's port and 0x60 in get_scancode())
 * 
 * a: constraint mean use the A register (in this case AL)
 * Nd: constraint mean:
 * 	N: force 8-bit integer constant
 * 	d: use the D register (in this case DX)
 *
 * x86 OUT (Output to Port) :
 * Copies the value from the second operand (source operand)
 * to the I/O port specified with the destination operand (first operand).
 *
 */

 static inline void outb(uint16_t port, uint8_t val)
 {
 	asm volatile ( "outb %0, %1"
 			:
 			: "a"(val), "Nd"(port) );
 }


/*
 *
 * inb: take I/O port address in DX (here it's port and 0x60 in get_scancode())
 * 	and return the I/O port value in AL (here ret and c= in get_scancode())
 * 
 * =a: constraint mean use the A register (in this case AL) and copy it to
 *     ret as output
 * 
 * Nd: constraint mean:
 * 	N: force 8-bit integer constant
 * 	d: use the D register (in this case DX)
 *
 * x86 IN (Input from Port) :
 * Copies the value from the I/O port
 * specified with the second operand (source operand)
 * to the destination operand (first operand).
 *
 */

static inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ( "inb %1, %0"
			: "=a"(ret)
			: "Nd"(port) );
	return ret;
}

static unsigned char get_scancode()
{
	unsigned char c = 0;
	do {
		if(inb(0x64) & 0x01){
			c = inb(0x60);
			return c;
		}
	} while(1);
}


int getchar(_Bool caps) {
	int c = get_scancode();
	if (c >= 128)
        return (-kbdus[caps][c - 128]);
	return kbdus[caps][c];
}

