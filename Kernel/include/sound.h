#ifndef __sound
#define __sound 1

#define MAGIC int x = 10000000/7; while (x --> 0);

void beep();
void nosound();
void sound(uint32_t frequency);

#endif