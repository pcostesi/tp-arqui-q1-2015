#include <stdint.h>
#include <sound.h>
#include <io.h>

//! output sound to speaker
void sound(uint32_t frequency)
{
        if ((frequency<19) || (frequency>22000)) return;

        outportb(0x61, inportb(0x61) | 3);
        outportb(0x43, 0xB6);
        outportb(0x42, (1193182L / frequency) & 0xFF);
        outportb(0x42, (1193182L / frequency) >> 8);
}

void nosound()
{
          outportb(0x61, inportb(0x61) & 0xFC);
}

void beep()
{
        sound(0x533);
        MAGIC;
        nosound();
}