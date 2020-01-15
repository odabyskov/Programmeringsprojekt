#include <stdio.h>
#include "stm32f30x_conf.h"

#ifndef _CALC_H_
#define _CALC_H_

#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / b )

#include "ansi.h"
#include "timing.h"
#include "objects.h"

// General calc-functions
uint32_t randomNumber(uint8_t lower, uint8_t upper);
int32_t convertTo1814(int32_t i);
int32_t convertTo3200(int32_t i);

// Functions to update the position of objects
void updateSpaceshipPosition(struct spaceship_t *spaceship, char input);
void updateSpaceshipBulletPosition(struct spaceshipBullet_t *bullet, struct spaceship_t *ship, char input);
void updateEnemyBulletPosition(struct enemyBullet_t *bullet, struct enemy1_t *enemy);
void updateEnemy1Position(struct enemy1_t *enemy);
void updateEnemy2Position(struct enemy2_t *enemy);
void updateEnemy3Position(struct enemy3_t *enemy);


#endif
