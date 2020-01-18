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
int32_t convertTo3200(int32_t i);

// Functions to update the position of objects
void updateSpaceshipPosition(struct spaceship_t *spaceship, char input);
void updateSpaceshipBulletPosition(struct bullet_t *bullet, struct spaceship_t *ship, char input, uint32_t k);
void updateSpaceshipShieldBulletPosition(struct bullet_t *bullet, struct spaceship_t *ship, char temp, uint32_t k);
void updateEnemyBulletPosition(struct bullet_t *bullet, struct enemy_t *enemy, uint32_t k);
void updateEnemyPosition(struct enemy_t *enemy, uint32_t k);

// Functions to check if the objects have been hit by a bullet
uint32_t isEnemyOneHit(struct enemy_t *e, struct bullet_t *b1, struct bullet_t *b2, struct bullet_t *b3, struct bullet_t *b4, struct bullet_t *b5, struct bullet_t *sb1, struct bullet_t *sb2);
uint32_t isEnemyTwoHit(struct enemy_t *e, struct bullet_t *b1, struct bullet_t *b2, struct bullet_t *b3, struct bullet_t *b4, struct bullet_t *b5, struct bullet_t *sb1, struct bullet_t *sb2);
//uint32_t isEnemyThreeHit(struct enemy_t *e, struct bullet_t *b1, struct bullet_t *b2, struct bullet_t *b3, struct bullet_t *b4, struct bullet_t *b5, struct bullet_t *sb1, struct bullet_t *sb2);
uint32_t isSpaceshipHit(struct spaceship_t *s,struct enemy_t *e1,struct enemy_t *e2, struct enemy_t *e3,struct enemy_t *e4,struct enemy_t *e5,struct enemy_t *e6,struct enemy_t *e7,struct enemy_t *e8,struct enemy_t *e9,struct bullet_t *eb1,struct bullet_t *eb2,struct bullet_t *eb3);
#endif
