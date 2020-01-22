#include <stdio.h>
#include "stm32f30x_conf.h"

#ifndef _TIMING_H_
#define _TIMING_H_

/*
This struct is used to control the timing of the game
*/
struct counter_t{

    uint32_t time;

};

struct counter_t counter; // We define a global counter to use in timing-issues

void setTimer();
void startStopTimer();
void TIM2_IRQHandler(void);

void initCounter(struct counter_t *counter);

#endif
