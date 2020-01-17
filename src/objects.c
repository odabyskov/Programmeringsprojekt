#define ESC 0x1B
#include <stdint.h>
#include <stdio.h>

#include "objects.h"

/*
*
* The following functions initializes the objects
*
*/

/*
This function initializes the player's spaceship
*/
void initSpaceship(struct spaceship_t *spaceship){

    spaceship->posX = 32 << FIX14_SHIFT; // the x-position is generated randomly
    spaceship->posY = 38 << FIX14_SHIFT; // The enemy is drawn in the top of the window

}

/*
This function initializes a spaceship bullet
*/
void initSpaceshipBullet(struct spaceshipBullet_t *bullet){

    bullet->posX = 1 << FIX14_SHIFT; // Random values - they will be set to the top of the spaceship once the bullet is fired
    bullet->posY = 1 << FIX14_SHIFT;
    bullet->timeAtPosition = 0 << FIX14_SHIFT;
    bullet->drawBullet = 0;
}

/*
This function initializes an enemy bullet
*/
void initEnemyBullet(struct enemyBullet_t *bullet){

    bullet->posX = 1 << FIX14_SHIFT; // Random values - they will be set to the top of the enemy once the bullet is fired
    bullet->posY = 1 << FIX14_SHIFT;
    bullet->timeAtPosition = 0 << FIX14_SHIFT;
    bullet->drawBullet = 0;
}


/*
The following functions initialize the three types of enemies
*/
void initEnemy1(struct enemy1_t *enemy){

    enemy->posX = randomNumber(3,68); // the x-position is generated randomly within the game window
    enemy->posY = convertTo1814(2);
    enemy->timeAtPosition = 0 << FIX14_SHIFT;
    enemy->drawEnemy1 = 0;
}

void initEnemy2(struct enemy2_t *enemy){

    enemy->posX = randomNumber(3,68); // the x-position is generated randomly within the game window
    enemy->posY = convertTo1814(2);
    enemy->timeAtPosition = 0 << FIX14_SHIFT;
    enemy->drawEnemy2 = 0;
}

void initEnemy3(struct enemy3_t *enemy){

    enemy->posX = randomNumber(3,68); // the x-position is generated randomly within the game window
    enemy->posY = convertTo1814(2);
    enemy->timeAtPosition = 0 << FIX14_SHIFT;
    enemy->drawEnemy3 = 0;
}


