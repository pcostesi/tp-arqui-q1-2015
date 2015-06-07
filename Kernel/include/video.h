#ifndef __vid_drv
#define __vid_drv 1

#define VID_COLS (80)
#define VID_ROWS (25)
#define VID_COLOR(foreground, background) (((foreground) & 0x0F) | ((background) << 4))

enum VID_COLOR
{
	BLACK = 0,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GRAY,

	GRAY = 8,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	YELLOW,
	WHITE,
};

void vid_putc(const char c);
void * vid_cursor(const unsigned int row, const unsigned int col);
void vid_raw_putc(const char c, const enum VID_COLOR);
char vid_color(const enum VID_COLOR, const enum VID_COLOR);
void vid_print(const char * str, unsigned int n);
void vid_raw_print(const char * str, unsigned int n);
void vid_clr(void);
void vid_flip_buffer(void);

#endif