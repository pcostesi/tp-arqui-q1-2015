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

int syscall_write(unsigned int fd, char *str, unsigned int size)
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
		return size;

		default:
		return -1;
	}
	vid_print(str, size);
	return size;
}

int syscall_read(unsigned int fd, char * buf, unsigned int size)
{
	int read = 0;
	enum KEYCODE keycode;
	char code;

	/* this function will return when the buffer gets consumed! */
	while (size && (keycode = kbrd_get_key()) != KEY_UNKNOWN && !buffer_is_empty()) {
		read++;
		size--;
		/* Most naive version to get keys working */
		code = (char) keycode;
		buf[read] = code;
	}

	return read;
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

		case 34: /* sys_pause */
		syscall_pause();
		break;

		case 48: /* sys_shutdown */
		vid_clr();
		vid_print("\n\tHalted X(", 11);
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
	return exitno;
}