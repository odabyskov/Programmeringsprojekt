#include "joystick.h"
#include "calc.h"
#include "sinLUT.h"
#define ESC 0x1B
#include <stdint.h>
#include <stdio.h>

void initializeJoystick(){

RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A

// Set pin PA4 (Up) to input
GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
GPIOA->MODER |= (0x00000000 << (4 * 2)); // Set mode register (0x00 – Input)
GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
GPIOA->PUPDR |= (0x00000002 << (4 * 2)); // Set push/pull register (0x02 - Pull-down, da vi gerne vil have 0, hvis intet input)


RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B

// Set pin PB0 (Down) to input
GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input)
GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
GPIOB->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x02 - Pull-down, da vi gerne vil have 0, hvis intet input)

// Set pin PB5 (Center) to input
GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
GPIOB->MODER |= (0x00000000 << (5 * 2)); // Set mode register (0x00 – Input)
GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
GPIOB->PUPDR |= (0x00000002 << (5 * 2)); // Set push/pull register (0x02 - Pull-down, da vi gerne vil have 0, hvis intet input)


RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

// Set pin PC0 (Right) to input
GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
GPIOC->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input)
GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
GPIOC->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x02 - Pull-down, da vi gerne vil have 0, hvis intet input)

// Set pin PC1 (Left) to input
GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
GPIOC->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 – Input)
GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
GPIOC->PUPDR |= (0x00000002 << (1 * 2)); // Set push/pull register (0x02 - Pull-down, da vi gerne vil have 0, hvis intet input)


}

uint8_t readJoystick(){

// Vi læser fra pins'ene
uint8_t bit0 = GPIOA->IDR & (0x0001 << 4); //Read from pin PA4
uint8_t bit1 = GPIOB->IDR & (0x0001 << 0); //Read from pin PB0
uint8_t bit2 = GPIOC->IDR & (0x0001 << 1); //Read from pin PC1
uint8_t bit3 = GPIOC->IDR & (0x0001 << 0); //Read from pin PC0
uint8_t bit4 = GPIOB->IDR & (0x0001 << 5); //Read from pin PB5

// Vi initialiserer return-værdi
uint8_t returnValue = 0;

// Vi indstiller returnValue efter de læste værdier
    if (bit0 >= 1){
        returnValue = 1;
    }
    if (bit1 >= 1){
        returnValue = 2;
    }
    if (bit2 >= 1){
        returnValue = 4;
    }
    if (bit3 >= 1){
        returnValue = 8;
    }
    if (bit4 >= 1){
        returnValue = 16;
    }
    return returnValue;
}

void printJoystick(uint8_t joystick){

    if (joystick == 16){
        printf("Center\n");
    }
    if (joystick == 8) {
        printf("Right\n");
    }
    if (joystick == 4){
        printf("Left\n");
    }
    if (joystick == 2){
        printf("Down\n");
    }
    if (joystick == 1){
        printf("Up\n");
    }

}


