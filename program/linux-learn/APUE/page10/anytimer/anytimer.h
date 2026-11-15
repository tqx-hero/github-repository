#ifndef __MY_SET_TIMER_H__
#define __MY_SET_TIMER_H__
#define MYTIME_SIZ 1024
typedef void mytime_t;

mytime_t *mysettimer(unsigned int,void(*)(void*),void*);

//int mysettimer_modify(mytime_t*);

#endif
