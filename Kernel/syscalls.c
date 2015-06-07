#include <syscalls.h>
#include <video.h>
#include <interrupts.h>
#include <keyboard.h>
#include <rtc-driver.h>

extern void _halt(void);

static char video_dormant = 0;

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

void syscall_write(unsigned int fd, char *str, unsigned int size)
{
	if (video_dormant) {
		syscall_wake();
	};

	switch (fd) {
		case 1:
		vid_color(WHITE, BLACK);
		break;
		case 2:
		vid_color(RED, BLACK);
		break;
		
		case 3:
		vid_raw_print(str, size);
		return;

		default:
		return;
	}
	vid_print(str, size);
}

int syscall_read(unsigned int fd, char * buf, unsigned int size)
{
	int read = -1;
	enum KEYCODE keycode;
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

IntSysHandler int80h(int sysno, int RDI, int RSI, int RDX, int R10, int R8, int R9)
{
	int exitno = 0;
	switch (sysno) {
		case 0: /* sys_write fd buf size */
		syscall_write((unsigned int) RDI, (char *) RSI, (unsigned int) RDX);
		break;

		case 1: /* sys_read fd buf size */
		exitno = syscall_read((unsigned int) RDI, (char *) RSI, (unsigned int) RDX);
		break;

		case 34: /* sys_pause */
		syscall_pause();
		break;

		case 48: /* sys_shutdown */
		_halt();
		break;

		case 42: /* sys_towel */
		while (1) {
			syscall_write(1, "42 ", 3);
		}
		break;

		default:
		return 0;
	}
	return 0;
}