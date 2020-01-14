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
This function initializes an enemy
*/
void initEnemy(struct enemy_t *enemy){

    enemy->posX = randomNumber(2,79); // the x-position is generated randomly
    enemy->posY = 2; // The enemy is drawn in the top of the window
    enemy->timeAtPosition = 0;

}

/*
This function initializes the player's spaceship
*/
void initSpaceship(struct spaceship_t *spaceship){

    spaceship->posX = 40; // the x-position is generated randomly
    spaceship->posY = 39; // The enemy is drawn in the top of the window

}

/*
This function initializes a spaceship bullet
*/
void initSpaceshipBullet(struct spaceshipBullet_t *bullet){

    bullet->posX = 1; // the x-position is set to the middle of the spaceship
    bullet->posY = 1; // the y-position is set to the top of the spaceship
    bullet->timeAtPosition = 0;
    bullet->drawBullet = 0;
}




