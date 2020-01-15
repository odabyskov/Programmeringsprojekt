#include <stdio.h>
#include "stm32f30x_conf.h"

#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "ansi.h"
#include "timing.h"
#include "calc.h"

/*
*
* The structures defined below represents the objects in the game
* (enemies, spaceship, bullets etc.).
*
*/


/*
This struct represents the player's spaceship. posX and posY are the center coordinates of the spaceship
*/
struct spaceship_t {
    uint32_t prevPosX; // previous position
    uint32_t prevPosY;
    uint32_t posX; // current position
    uint32_t posY;
};

/*
This struct represents the bullets that fire from the user's spaceship
If drawBullet is 0, the bullet is not drawn. If drawBullet is equal to
or greater than 1, the bullet is drawn.
*/
struct spaceshipBullet_t {
    uint32_t prevPosX; // previous position
    uint32_t prevPosY;
    uint32_t posX; // current position
    uint32_t posY;
    uint32_t timeAtPosition;
    uint32_t drawBullet;
};

/*
This struct represents the bullets that fire from enemy 1.
If drawBullet is 0, the bullet is not drawn. If drawBullet is equal to
or greater than 1, the bullet is drawn.
*/
struct enemyBullet_t {
    uint32_t prevPosX; // previous position
    uint32_t prevPosY;
    uint32_t posX; // current position
    uint32_t posY;
    uint32_t timeAtPosition;
    uint32_t drawBullet;
};

/*
The following structs represent the enemies.
posX and posY are the center coordinates of the enemy.
*/

struct enemy1_t { // This enemy shoots bullets
    uint32_t prevPosX; // previous position
    uint32_t prevPosY;
    uint32_t posX; // current position
    uint32_t posY;
    uint32_t timeAtPosition;
    uint32_t drawEnemy1;
};

struct enemy2_t { // This enemy can't shoot bullets nor does it have a shield
    uint32_t prevPosX; // previous position
    uint32_t prevPosY;
    uint32_t posX; // current position
    uint32_t posY;
    uint32_t timeAtPosition;
    uint32_t drawEnemy2;
};

struct enemy3_t { // This enemy has a shield
    uint32_t prevPosX; // previous position
    uint32_t prevPosY;
    uint32_t posX; // current position
    uint32_t posY;
    uint32_t timeAtPosition;
    uint32_t drawEnemy3;
};



// Functions to initialize objects
void initSpaceship(struct spaceship_t *spaceship);
void initSpaceshipBullet(struct spaceshipBullet_t *bullet);
void initEnemyBullet(struct spaceshipBullet_t *bullet);
void initEnemy1(struct enemy1_t *enemy);
void initEnemy2(struct enemy2_t *enemy);
void initEnemy3(struct enemy3_t *enemy);

#endif
