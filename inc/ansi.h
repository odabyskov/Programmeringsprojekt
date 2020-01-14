#include <stdio.h>
#include "stm32f30x_conf.h"

#ifndef _ANSI_H_
#define _ANSI_H_

#include "calc.h"
#include "ansi.h"
#include "timing.h"
#include "objects.h"

// General ansi-functions
void clrscr();
void clreol();
void gotoxy(uint8_t x, uint8_t y);
void deleteSymbol(uint8_t x, uint8_t y);
void drawBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void drawWindow(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char* string_p, uint8_t style);

// Functions to draw objects on Putty
void drawEnemy(struct enemy_t *enemy);
void drawSpaceship(struct spaceship_t *spaceship);
void drawSpaceshipBullet(struct spaceshipBullet_t *bullet);

#endif
