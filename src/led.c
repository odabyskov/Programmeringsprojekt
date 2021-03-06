#include "led.h"

#define ESC 0x1B
#include <stdint.h>
#include <stdio.h>

/*
This function initializes the LEDs
*/
void initializeLED(){

    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A

    // Set pin PA9 to output
    GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2)); // Clear speed register
    GPIOA->OSPEEDR |= (0x00000002 << (9 * 2)); // set speed register (0x02 - 2 MHz)
    GPIOA->OTYPER &= ~(0x0001 << (9)); // Clear output type register
    GPIOA->OTYPER |= (0x0000 << (9)); // Set output type register (0x00 - Push pull)
    GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000001 << (9 * 2)); // Set mode register (0x01 - Output)

    // Turn off the led by turning on the first bit (or-operation)
    GPIOA->ODR |= (0x0001 << 9);


    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B

    // Set pin PB4 to output
    GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2));
    GPIOB->OSPEEDR |= (0x00000002 << (4 * 2));
    GPIOB->OTYPER &= ~(0x0001 << (4));
    GPIOB->OTYPER |= (0x0000 << (4));
    GPIOB->MODER &= ~(0x00000003 << (4 * 2));
    GPIOB->MODER |= (0x00000001 << (4 * 2));

    // Turn off the led
    GPIOB->ODR |= (0x0001 << 4);

    RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

    // Set pin PC7 to output
    GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2));
    GPIOC->OSPEEDR |= (0x00000002 << (7 * 2));
    GPIOC->OTYPER &= ~(0x0001 << (7));
    GPIOC->OTYPER |= (0x0000 << (7));
    GPIOC->MODER &= ~(0x00000003 << (7 * 2));
    GPIOC->MODER |= (0x00000001 << (7 * 2));

    // Turn off the led
    GPIOC->ODR |= (0x0001 << 7);
}

/*
This function takes an integer and sets the LEDs accordingly
*/
void setLED(uint8_t ledhits){

    if (ledhits == 1){                      // One hit turns on yellow (red and green)
        GPIOB->ODR &= ~(0x0001 << 4);       // Turn on red by turning off the first bit(and-operation with inverse of one)
        GPIOC->ODR &= ~(0x0001 << 7);       // Turn on green
        GPIOA->ODR |= (0x0001 << 9);        // Turn off blue
    }
    else if (ledhits == 2){                 // Two hits turns on red
        GPIOB->ODR &= ~(0x0001 << 4);       // Turn on red
        GPIOA->ODR |= (0x0001 << 9);        // Turn off blue
        GPIOC->ODR |= (0x0001 << 7);        // Turn off green
    }
    else if (ledhits == 3) {                // Three hits and you are dead. white light (red, green and blue)
        GPIOB->ODR &= ~(0x0001 << 4);       // Turn on red
        GPIOC->ODR &= ~(0x0001 << 7);       // Turn on green
        GPIOA->ODR &= ~(0x0001 << 9);       // Turn on blue
    }
    else {                                  // Zero hits equals green.
        GPIOC->ODR &= ~(0x0001 << 7);       // Turn on green (default)
        GPIOA->ODR |= (0x0001 << 9);        // Turn off blue
        GPIOB->ODR |= (0x0001 << 4);        // Turn off red
    }
}

