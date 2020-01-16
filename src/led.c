#include "led.h"

#define ESC 0x1B
#include <stdint.h>
#include <stdio.h>



void initializeLED(){

RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A

// Set pin PA9 to output
GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2)); // Clear speed register
GPIOA->OSPEEDR |= (0x00000002 << (9 * 2)); // set speed register (0x02 - 2 MHz)
GPIOA->OTYPER &= ~(0x0001 << (9)); // Clear output type register
GPIOA->OTYPER |= (0x0000 << (9)); // Set output type register (0x00 - Push pull)
GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
GPIOA->MODER |= (0x00000001 << (9 * 2)); // Set mode register (0x01 - Output)

// sluk for den
GPIOA->ODR |= (0x0001 << 9);
//

RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B

// Set pin PB4 to output
GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2)); // Clear speed register
GPIOB->OSPEEDR |= (0x00000002 << (4 * 2)); // set speed register (0x02 - 2 MHz)
GPIOB->OTYPER &= ~(0x0001 << (4)); // Clear output type register
GPIOB->OTYPER |= (0x0000 << (4)); // Set output type register (0x00 - Push pull)
GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
GPIOB->MODER |= (0x00000001 << (4 * 2)); // Set mode register (0x01 - Output)

// sluk for den
GPIOB->ODR |= (0x0001 << 4);
//


RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

// Set pin PC7 to output
GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2)); // Clear speed register
GPIOC->OSPEEDR |= (0x00000002 << (7 * 2)); // set speed register (0x02 - 2 MHz)
GPIOC->OTYPER &= ~(0x0001 << (7)); // Clear output type register
GPIOC->OTYPER |= (0x0000 << (7)); // Set output type register (0x00 - Push pull)
GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
GPIOC->MODER |= (0x00000001 << (7 * 2)); // Set mode register (0x01 - Output)

// sluk for den
GPIOC->ODR |= (0x0001 << 7);
//

}

void setLED(uint8_t ledhits){

    if (ledhits == 0) {
        GPIOC->ODR &= ~(0x0001 << 7);
    }
    else if (ledhits == 1){
        GPIOB->ODR &= ~(0x0001 << 4);
        GPIOC->ODR &= ~(0x0001 << 7);
    }
    else if (ledhits == 2){
        GPIOB->ODR &= ~(0x0001 << 4);
    }
    else if (ledhits == 3) {
        GPIOB->ODR &= ~(0x0001 << 4);
        GPIOC->ODR &= ~(0x0001 << 7);
        GPIOA->ODR &= ~(0x0001 << 9);
    }

    else{
        GPIOB->ODR &= ~(0x0001 << 4);
    }
}

