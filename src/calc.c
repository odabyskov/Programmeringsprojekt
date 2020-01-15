#define ESC 0x1B
#include <stdint.h>
#include <stdio.h>


#include "calc.h"

/*
*
*
*
* The following functions are general functions to make calculations
*
*
*
*/

/*
This function generates a random number in the range from lower to upper
*/

uint8_t randomNumber(uint8_t lower, uint8_t upper){

    uint8_t random = (rand() % (upper - lower + 1)) + lower;

    return random;
}


/*
*
*
*
* The following functions update the positions of the different objects
* in the game.
*
*
*
*/

/*
This function updates the position of the spaceship according to the input from the user.
If the user presses the 'a'-key the spaceship moves one step to the left.
If the user presses the 'd'-key the spaceship moves one step to the right.
*/
void updateSpaceshipPosition(struct spaceship_t *spaceship, char temp){

    if (temp == 'a' || temp == 'd'){

        // We set the current position to the previous position
        spaceship->prevPosX=(*spaceship).posX;
        spaceship->prevPosY=(*spaceship).posY;

        // We update current position
        if(temp=='a'){
            if ((*spaceship).posX>4){
                spaceship->posX--;
            } else {
                spaceship->posX=4;
            }
        }
        else if(temp=='d'){
            if ((*spaceship).posX<77){
                spaceship->posX++;
            } else {
                spaceship->posX=77;
            }
        }
    }
}


/*
This function updates the enemy's position
*/
void updateEnemyPosition(struct enemy_t *enemy){

    // We save the previous location of the enemy
    uint8_t prevX = (*enemy).posX;
    uint8_t prevY = (*enemy).posY;

    deleteSymbol(prevX,prevY); // We delete the enemy at its last position

    enemy->posY++;

    if ((*enemy).posY>=39){
            enemy->posX=randomNumber(2,79);
            enemy->posY=1;
    }
}

/*
This function updates the bullet's position.
The bullet moves vertically upwards from where it was fired.
*/
void updateSpaceshipBulletPosition(struct spaceshipBullet_t *bullet, struct spaceship_t *ship, char temp){

    if (temp == 32 && (*bullet).drawBullet == 0){

        bullet->posX = (*ship).posX; // the x-position is set to the middle of the spaceship
        bullet->posY = (*ship).posY-2; // the y-position is set to the top of the spaceship

        bullet->drawBullet = 1;

    } else if ((*bullet).drawBullet >= 1){

        // We set the current positions to previous position
        bullet->prevPosX=(*bullet).posX;
        bullet->prevPosY=(*bullet).posY;

        // We update the current position
        bullet->posX = (*bullet).posX; // the x-position is set to the middle of the spaceship
        bullet->posY = (*bullet).posY-1; // the y-position is set to the position above the previous position

    }

}


