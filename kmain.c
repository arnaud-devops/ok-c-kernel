/*
 * kmain.c
 */

#include "include/kernel.h"
#include "libk.h"

_Bool caps = 0;

/*
 *
 * outb: output byte in AL (here it's val and 0x0 in get_scancode())
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


void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

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

int column(char *video)
{
    return (((video - (char *)VID_MEMORY) / 2) % 80);
}

int line(char *video)
{
    return (((video - (char *)VID_MEMORY) / 2) / 80);
}

void enter(char **video)
{
//    if (line(*video) == 25)
//        *video = (char *)VID_MEMORY;
//    else
        *video = (char *)VID_MEMORY + 80 * 2 * (line(*video) + 1);
//    update_cursor(((*video-(char *)VID_MEMORY)/2)%80, ((*video-(char *)VID_MEMORY)/2)/80);
}

static inline void del(char **video)
{
    if ((int)*video - 2 < (int)VID_MEMORY)
        *video = *video - 2 + (80 * 25 * 2);
    else
        *video -= 2;
    **video = ' ';
}


static inline void arrow_up(char **video)
{
    if ((int)*video - MAX_COLUMNS * 2 < (int)VID_MEMORY)
        *video = *video - MAX_COLUMNS * 2 + (80 * 25 * 2);
    else
        *video -= MAX_COLUMNS * 2;
}

static inline void arrow_down(char **video)
{
    if ((int)*video + MAX_COLUMNS * 2 > (int)VID_MEMORY + (80 * 25 * 2))
        *video = *video + MAX_COLUMNS * 2 - (80 * 25 * 2);
    else
        *video += MAX_COLUMNS * 2;
}

static inline void arrow_right(char **video)
{
    if ((int)*video + 2 > (int)VID_MEMORY + (80 * 25 * 2))
        *video = *video + 2 - (80 * 25 * 2);
    else
        *video += 2;
}

static inline void arrow_left(char **video)
{
    if ((int)*video - 2 < (int)VID_MEMORY)
        *video = *video - 2 + (80 * 25 * 2);
    else
        *video -= 2;
}

void kputchar(int c) {
	static char *video = (char*)VID_MEMORY;
	static char color = WHITE;

	switch (c)
	{
        case 150:
            arrow_up(&video);
            break;
        case 151:
            arrow_left(&video);
            break;
        case 152:
            arrow_right(&video);
            break;
        case 153:
            arrow_down(&video);
            break;
        case 200:
			color = BLUE;
			break;
		case 201:
			color = GREEN;
			break;
		case 202:
			color = CYAN;
			break;
		case 203:
			color = RED;
			break;
		case 204:
			color = MAGENTA;
			break;
		case 205:
			color = BROWN;
			break;
		case 206:
			color = LIGHT_BLUE;
			break;
		case 207:
			color = LIGHT_GREEN;
			break;
		case 208:
			color = LIGHT_RED;
			break;
		case 209:
			color = WHITE;
			break;
        case 253:
            del(&video);
            break;
	    case 255:
            enter(&video);
            break;
        case 155:
        case 156:
        case 157:
	        caps = !caps;
            break;
	    case -156:
	    case -157:
	        caps = !caps;
	        break;
		default:
		    if (c < 0)
		        break;
			*video++ = (char)c;
			*video++ = color;
			break;
	}
    if (video == (char*)(VID_MEMORY + MAX_COLUMNS * MAX_LINES * 2))
        video = (char *) VID_MEMORY;
    update_cursor(column(video), line(video));
}

static void basic_kbd() {
	int c;
	while (1) {
		c = getchar(caps);
		if (c != 0)
			kputchar(c);
	}
}

void kmain(void)
{
	const char *str = "Hello World!"; /* Message which will be displayed on Kernel screen */
	char *vidptr = (char*)VID_MEMORY; /* Videos memory begin here */
	char c;


//	init_gdt();
	ft_clear_screen();
	enable_cursor(0, 15);
	ft_write_on_screen(str, vidptr);
	while (1) {
		c = getchar(0);
        if (c != 0) {
			ft_clear_screen();
			basic_kbd();
		}
	}
	return ;
}
