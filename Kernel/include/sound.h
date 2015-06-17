#ifndef __sound
#define __sound 1
#include <stdint.h>

#define MAGIC /*int x = 10000000/7; while (x --> 0); //first impl. of time-based beep*/

void beep(void);
void beepl(unsigned int length);
void beeplf(unsigned int length, unsigned int freq);
void nosound(void);
void sound(uint32_t frequency);
void tick_sound(void);

#endif