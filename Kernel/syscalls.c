#include <syscalls.h>
#include <video.h>
#include <time.h>
#include <interrupts.h>
#include <keyboard.h>
#include <rtc-driver.h>

#define STDIN  0
#define STDOUT 1
#define STDERR 2
#define STDRAW 3

extern void _halt(void);
extern unsigned int screensaver_delay;

static char video_dormant = 0;
static enum VID_COLOR colors[] = {LIGHT_GRAY, BLACK, RED, BLACK};

void syscall_halt(void)
{
	vid_clr();
	vid_print("\n\tHalted X(", 11);
	_halt();
}

void syscall_pause(void)
{
	if (video_dormant) return;

	vid_flip_buffer();
	video_dormant = 1;
}

void syscall_wake(void)
{
	if (!video_dormant) return;
	
	vid_flip_buffer();
	video_dormant = 0;
}

int syscall_write(unsigned int fd, char *str, unsigned int size)
{
	if (video_dormant) {
		syscall_wake();
	};

	switch (fd) {
		case STDOUT:
		vid_color(colors[0], colors[1]);
		break;
		case STDERR:
		vid_color(colors[2], colors[3]);
		break;
		
		case STDRAW:
		vid_raw_print(str, size);
		return size;

		default:
		return -1;
	}
	vid_print(str, size);
	return size;
}

int syscall_read(unsigned int fd, char * buf, unsigned int size)
{
	int read = -1;
	enum KEYCODE keycode = KEY_UNKNOWN;
	char code;

	/* this function will return when the buffer gets consumed! */
	while ((keycode = kbrd_get_key()) != KEY_UNKNOWN) {
		read++;
		/* Most naive version to get keys working */
		code = kbrd_key_to_ascii(keycode);
		if(code != 0)
		{
			buf[read] = code;
		}
	}

	return read;
}

int syscall_ioctl(unsigned int fd, unsigned long request, void * params)
{
	int exitno = -1;
	if (fd == STDOUT || fd == STDERR || fd == STDRAW || fd == STDIN) {
		char high = ((uint64_t) params >> 8) & 0xFF;
		char low = ((uint64_t) params) & 0xFF;
			
		switch (request) {
			case 0: /* move cursor */
			vid_cursor(high, low);
			return 0;
			break;

			case 1: /* clear screen */
			vid_clr();
			return 0;
			break;

			case 2: /* change color */
			vid_color(high, low);
			if (fd == STDOUT || fd == STDERR) {
				colors[fd - 1] = high;
				colors[fd] = low;
			}
			return 0;
			break;

			case 3: /* inactive */
			screensaver_delay = (unsigned int) params;
			return screensaver_delay;
			break;
		}
	}
	return exitno;
}

uint64_t int80h(uint64_t sysno, uint64_t RDI, uint64_t RSI, uint64_t RDX, uint64_t RCX,
	uint64_t R8, uint64_t R9)
{
	int exitno = 0;
	switch (sysno) {
		case 0: /* sys_write fd buf size */
		exitno = syscall_write((unsigned int) RDI, (char *) RSI, (unsigned int) RDX);
		break;

		case 1: /* sys_read fd buf size */
		exitno = syscall_read((unsigned int) RDI, (char *) RSI, (unsigned int) RDX);
		break;

		case 6:
		exitno = syscall_ioctl((unsigned int) RDI, (unsigned long) RSI, (void *) RDX);
		break;

		case 34: /* sys_pause */
		syscall_pause();
		break;

		case 48: /* sys_shutdown */
		syscall_halt();
		break;

		case 42: /* sys_towel */
		while (1) {
			syscall_write(1, "42 ", 3);
		}
		break;

		case 200:
		syscall_get_time((struct rtc_time *) RDI);
		break;

		case 201:
		syscall_set_time((struct rtc_time *) RDI);
		break;

		default:
		return 0;
	}
	return exitno;
}
