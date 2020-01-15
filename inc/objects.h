#include <stdio.h>
#include "stm32f30x_conf.h"

#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "ansi.h"
#include "timing.h"
#include "calc.h"
#include "objects.h"

/*
*
* The structures defined below represents the objects in the game
* (enemies, spaceship, bullets etc.).
*
*/

/*
This struct represents an enemy. posX and posY are the center coordinates of the enemy
*/
struct enemy_t {
    uint8_t posX;
    uint8_t posY;
    uint8_t timeAtPosition;
};

/*
This struct represents the player's spaceship. posX and posY are the center coordinates of the spaceship
*/
struct spaceship_t {
    uint8_t prevPosX; // previous position
    uint8_t prevPosY;
    uint8_t posX; // current position
    uint8_t posY;
};

/*
This struct represents the bullets that fire from the user's spaceship
If drawBullet is 0, the bullet is not drawn. If drawBullet is equal to
or greater than 1, the bullet is drawn.
*/
struct spaceshipBullet_t {
    uint8_t prevPosX; // previous position
    uint8_t prevPosY;
    uint8_t posX; // current position
    uint8_t posY;
    uint8_t timeAtPosition;
    uint8_t drawBullet;
};


// Functions to initialize objects
void initEnemy(struct enemy_t *enemy);
void initSpaceship(struct spaceship_t *spaceship);
void initSpaceshipBullet(struct spaceshipBullet_t *bullet);


#endif
