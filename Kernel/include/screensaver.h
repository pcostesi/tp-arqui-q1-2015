#ifndef __SCR_SVR
#define __SCR_SVR 1


#define TICK 55

void scrsvr_set_delay(unsigned int delay);
int scrsvr_should_show(unsigned int seconds);
void scrsvr_tick(unsigned int tick);


#endif