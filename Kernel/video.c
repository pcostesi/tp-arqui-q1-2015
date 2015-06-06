#include <video.h>

#define COLS ((VID_COLS) * 2)
#define ROWS (VID_ROWS)

#define VID_RAW_POS(row, col) ((char *) _vid_video + COLS * (row) + (col))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define TAB_SIZE (8)

static volatile char * _vid_video = (char *) 0xB8000;
static volatile char * _vid_cursor = (char *) 0xB8000;
static char _vid_fmt = (char) 0x07;

inline static void vid_scroll();
inline static void _vid_copy_row(const int row_src, const int row_dst);
static void _vid_set_cursor(const unsigned int row, const unsigned int col);



void vid_raw_print(const char * str, unsigned int n)
{
	char * c = (char *) str;
	char * fmt = (char *) str;
	while (n--) {
		vid_raw_putc(*c++, *fmt++);
	}
}

void vid_print(const char * str)
{
	char * p = (char *) str;
	while (*p != '\0') {
		vid_putc(*p++);
	}
	
}

void vid_println(const char * str)
{
	vid_print(str);
	vid_putc('\n');
}

void vid_clr() {
	int i;
	for (i = 0; i < COLS * ROWS ; i++) {
		*_vid_cursor++ = (char) 0;
		*_vid_cursor++ = (char) 0;
	}
	_vid_set_cursor(0, 0);
}

char vid_color(const enum VID_COLOR foreground, const enum VID_COLOR background)
{
	return _vid_fmt = VID_COLOR(foreground, background);
}

void vid_putc(const char c)
{
	vid_raw_putc(c, _vid_fmt);
}

static void _vid_set_cursor(const unsigned int row, const unsigned int col)
{
	char * raw = VID_RAW_POS(row, col);
	char * _VID_MAX_POS = VID_RAW_POS(ROWS - 1, COLS);
	char * _VID_MIN_POS = VID_RAW_POS(0, 0);

	if (raw > _VID_MAX_POS) {
		 _vid_cursor = _VID_MAX_POS;
	} else if (raw < _VID_MIN_POS) {
		_vid_cursor = _VID_MIN_POS;
	} else {
		_vid_cursor = raw;
	}
}

void vid_raw_putc(const char c, const enum VID_COLOR fmt)
{
	int offset, row, col;

	if (_vid_cursor >= VID_RAW_POS(ROWS - 1, COLS)) {
		vid_scroll();
		_vid_set_cursor(ROWS - 1, 0);
	}

	offset = _vid_cursor - _vid_video;
	row = offset / COLS;
	col = offset % COLS;

	switch (c) {
		case '\n':
		while (_vid_cursor < VID_RAW_POS(row + 1, 0)) {
			*_vid_cursor++ = ' ';
			*_vid_cursor++ = fmt;
		}
		_vid_set_cursor(row + 1, 0);
		break;
	
		case '\r':
		_vid_set_cursor(row, 0);
		break;

		case '\b':
		_vid_set_cursor(row, MAX(col - 1, 0));
		break;

		case '\t':
		do {
			*_vid_cursor++ = ' ';
			*_vid_cursor++ = fmt;
			col += 2;
		} while (col < COLS && col < TAB_SIZE * 2);
		break;
	
		default:
		*_vid_cursor++ = c;
		*_vid_cursor++ = fmt;
	}
}

inline static void _vid_copy_row(const int row_src, const int row_dst)
{
	char * src = VID_RAW_POS(row_src, 0);
	char * dst = VID_RAW_POS(row_dst, 0);
	int idx;
	for (idx = 0; idx < COLS; idx++) {
		*dst++ = *src++;
	}
}

inline static void vid_scroll()
{
	int row, col;
	char * ptr = VID_RAW_POS(ROWS - 1, 0);

	for (row = 0; row < ROWS - 1; row++) {
		_vid_copy_row(row + 1, row);
	}

	for (col = 0; col < COLS; col++) {
		*ptr++ = (char) 0;
	}
}

#undef COLS
#undef ROWS
#undef MAX
#undef MIN
#undef TAB_SIZE
#undef VID_RAW_POS