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
    spaceship->prevPosX = 40 << FIX14_SHIFT; // The spaceship starts in the middle of the screen
    spaceship->prevPosY = 20 << FIX14_SHIFT; // 
    
    spaceship->posX = 32 << FIX14_SHIFT; // The spaceship is moved to the middle of the game screen
    spaceship->posY = 38 << FIX14_SHIFT; // The spaceship is moved in the buttom of the window
}

/*
This function initializes a bullet
*/
void initBullet(struct bullet_t *bullet){

    bullet->velX = 0 << FIX14_SHIFT; // Velocity set to vertical
    bullet->velY = 1 << FIX14_SHIFT;
    bullet->posX = 3 << FIX14_SHIFT; // Random values - they will be set to the top of the spaceship once the bullet is fired
    bullet->posY = 3 << FIX14_SHIFT;
    bullet->timeAtPosition = 0 << FIX14_SHIFT;
    bullet->drawBullet = 0;

}

/*
This function initializes an object (enemy or power up)
*/
void initEnemy(struct enemy_t *enemy){

    enemy->prevPosX = randomNumber(4,66); // The x-position is generated randomly within the game window
    enemy->prevPosY = 2 << FIX14_SHIFT;
    enemy->posX = randomNumber(4,66); // The x-position is generated randomly within the game window
    enemy->posY = 2 << FIX14_SHIFT;
    enemy->timeAtPosition = 0 << FIX14_SHIFT;
    enemy->drawEnemy = 0;
}
