#include <stdint.h>
#include <sound.h>
#include <io.h>
#include <screensaver.h>

static unsigned int timeout = 0;

//! output sound to speaker
void sound(uint32_t frequency)
{
        if ((frequency<19) || (frequency>22000)) return;

        outportb(0x61, inportb(0x61) | 3);
        outportb(0x43, 0xB6);
        outportb(0x42, (1193182L / frequency) & 0xFF);
        outportb(0x42, (1193182L / frequency) >> 8);
}

void nosound(void)
{
          outportb(0x61, inportb(0x61) & 0xFC);
}

void beep(void)
{
	beepl(1);
}

void beepl(unsigned int length)
{
	beeplf(length, 0x533);
}

void beeplf(unsigned int length, unsigned int freq)
{
	timeout = timeout > length ? timeout : length;
    sound(freq);
}


void tick_sound(void)
{
	if (timeout > 0) {
		timeout--;
	} else {
		nosound();
	}
}