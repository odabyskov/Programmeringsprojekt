#include <stdio.h>
#include "stm32f30x_conf.h"

void initializeJoystick();
uint8_t readJoystick();
void printJoystick(uint8_t joystick);

void initializeLED();
void setLED(uint8_t joystick);
