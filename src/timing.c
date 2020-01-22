#define ESC 0x1B
#include <stdint.h>
#include <stdio.h>

#include "timing.h"

/*
This function sets the timer with an interrupt every 1/20 second
*/
void setTimer(){

    RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2
    TIM2->CR1 = 0x00; // Configure timer 2
    TIM2->ARR = 50; // Set reload value
    TIM2->PSC = 125489; // Set prescale value,

    TIM2->CR1 = 0x01; // Enable timer

    TIM2->DIER |= 0x0001; // Enable timer 2 interrupts
    NVIC_SetPriority(TIM2_IRQn, 0); // Set interrupt priority
    NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt

}

/*
This function is used to update the counter accordingly to the
timer interrupt.
*/
void TIM2_IRQHandler(void) {

    counter.time++; // Currently it increments 20 times per second

    TIM2->SR &= ~0x0001; // Clear interrupt bit
 }

/*
This function starts/stops the timer
*/
void startStopTimer(){
    if (TIM2->CR1 & 0x0001){
        TIM2->CR1 = 0x0000;
    }
    else{
        TIM2->CR1 = 0x0001;
    }
}

/*
This function initializes the counter
*/
void initCounter(struct counter_t *counter){
    counter->time = 0;
}
