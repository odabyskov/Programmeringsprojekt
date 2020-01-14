#include <stdio.h>
#include "stm32f30x_conf.h"

#ifndef _CALC_H_
#define _CALC_H_


#include "calc.h"
#include "ansi.h"
#include "timing.h"
#include "objects.h"

// General calc-functions
uint8_t randomNumber(uint8_t lower, uint8_t upper);

// Functions to update the position of objects
void updateSpaceshipPosition(struct spaceship_t *spaceship, char input);
void updateEnemyPosition(struct enemy_t *enemy);
void updateSpaceshipBulletPosition(struct spaceshipBullet_t *bullet, struct spaceship_t *ship, char input);


#endif
