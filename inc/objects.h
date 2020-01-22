#include <stdio.h>
#include "stm32f30x_conf.h"

#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "ansi.h"
#include "timing.h"
#include "calc.h"

/*
*
*
*
* The structures defined below represents the objects in the game
* (enemies, spaceship, bullets, power-up).
*
*
*
*/

/*
This struct represents the player's spaceship. posX and posY are the center coordinates of the spaceship
*/
struct spaceship_t {
    uint32_t prevPosX; // Previous position
    uint32_t prevPosY;
    uint32_t posX; // Current position
    uint32_t posY;
};

/*
This struct represents a bullet
If drawBullet is 0, the bullet is not drawn. If drawBullet is equal to
or greater than 1, the bullet is drawn.
*/
struct bullet_t {
    uint32_t velX; // Velocity
    uint32_t velY;
    uint32_t prevPosX; // Previous position
    uint32_t prevPosY;
    uint32_t posX; // Current position
    uint32_t posY;
    uint32_t timeAtPosition;
    uint32_t drawBullet;
};

/*
The following struct represent the enemies and powerup.
posX and posY are the center coordinates of the enemy.
*/
struct enemy_t {
    uint32_t prevPosX; // Previous position
    uint32_t prevPosY;
    uint32_t posX; // Current position
    uint32_t posY;
    uint32_t timeAtPosition;
    uint32_t drawEnemy; // Should the enemy be drawn
    uint32_t shoot; // Should the enemy shoot
};


// Functions to initialize objects
void initSpaceship(struct spaceship_t *spaceship);
void initBullet(struct bullet_t *bullet);
void initEnemy(struct enemy_t *enemy);


#endif
