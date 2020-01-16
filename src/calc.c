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
This function generates a 18.14 fixed point random number in the range from lower to upper
*/

uint32_t randomNumber(uint8_t lower, uint8_t upper){

    uint32_t random = ((rand() % (upper - lower + 1)) + lower) << FIX14_SHIFT;

    return random;
}

/*
This function converts a 18.14 fixed point number to 32.0 and returns it
*/
int32_t convertTo3200(int32_t i) {

 return i >> 14;
 }

 /*
This function converts a 32.0 fixed point number to 18.14 and returns it
*/
int32_t convertTo1814(int32_t i) {

 return i << 14;
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

    if (temp == 'a' || temp == 'A' || temp == 'd' || temp == 'D'){

        // We set the current position to the previous position
        spaceship->prevPosX=(*spaceship).posX;
        spaceship->prevPosY=(*spaceship).posY;

        // We update current position
        if(temp=='a' || temp == 'A'){
            if ((*spaceship).posX > (5 << FIX14_SHIFT)){
                spaceship->posX = (*spaceship).prevPosX - (1 << FIX14_SHIFT);
            } else {
                spaceship->posX = (5 << FIX14_SHIFT);
            }
        }
        else if(temp=='d' || temp == 'D'){
            if ((*spaceship).posX < (65 << FIX14_SHIFT)){
                spaceship->posX = (*spaceship).prevPosX + convertTo1814(1);
            } else {
                spaceship->posX = (65 << FIX14_SHIFT);
            }
        }
    }
}

/*
This function updates the bullet's position.
The bullet moves vertically upwards from where it was fired.
*/
void updateSpaceshipBulletPosition(struct spaceshipBullet_t *bullet, struct spaceship_t *ship, char temp){

    if (temp == 32 && bullet->drawBullet == 0 << FIX14_SHIFT){

        bullet->posX = (*ship).posX; // the x-position is set to the middle of the spaceship
        bullet->posY = (*ship).posY- (2 << FIX14_SHIFT); // the y-position is set to the top of the spaceship

        bullet->drawBullet = (1 << FIX14_SHIFT);

    } else if ((*bullet).drawBullet >= (1 << FIX14_SHIFT)){

        // We set the current positions to previous position
        bullet->prevPosX=(*bullet).posX;
        bullet->prevPosY=(*bullet).posY;

        // We update the current position
        bullet->posX = (*bullet).posX; // the x-position is set to the middle of the spaceship
        bullet->posY = (*bullet).posY - (1 << FIX14_SHIFT); // the y-position is set to the position above the previous position

    }

}

/*
This function updates the bullet's position.
The bullet moves vertically upwards from where it was fired.
*/
void updateSpaceshipShieldBulletPosition(struct spaceshipShieldBullet_t *bullet, struct spaceship_t *ship, char temp){

    if ((temp == 'w' || temp == 'W') && bullet->drawBullet == 0 << FIX14_SHIFT){

        bullet->posX = (*ship).posX; // the x-position is set to the middle of the spaceship
        bullet->posY = (*ship).posY - (2 << FIX14_SHIFT); // the y-position is set to the top of the spaceship

        bullet->drawBullet = convertTo1814(1);

    } else if (bullet->drawBullet >= (1 << FIX14_SHIFT)){

        // We set the current positions to previous position
        bullet->prevPosX=(*bullet).posX;
        bullet->prevPosY=(*bullet).posY;

        // We update the current position
        bullet->posX = (*bullet).posX; // the x-position is set to the middle of the spaceship
        bullet->posY = (*bullet).posY - (1 << FIX14_SHIFT); // the y-position is set to the position above the previous position

    }
}


/*
This function updates the bullet's position.
The bullet moves vertically downwards from where it was fired.
*/
void updateEnemyBulletPosition(struct enemyBullet_t *enemyBullet, struct enemy1_t *enemy){

    if ( (*enemyBullet).drawBullet == 0 << FIX14_SHIFT){

        enemyBullet->posX = (*enemy).posX; // the x-position is set to the middle of the spaceship
        enemyBullet->posY = (*enemy).posY + (2 << FIX14_SHIFT); // the y-position is set to the top of the spaceship
        enemyBullet->drawBullet = (1 << FIX14_SHIFT);

    } else if ( (*enemyBullet).drawBullet >= (1 << FIX14_SHIFT)){

        // We set the current positions to previous position
        enemyBullet->prevPosX=(*enemyBullet).posX;
        enemyBullet->prevPosY=(*enemyBullet).posY;

        // We update the current position
        enemyBullet->posX = (*enemyBullet).posX; // the x-position is set to the middle of the enemy
        enemyBullet->posY = (*enemyBullet).posY + (1 << FIX14_SHIFT); // the y-position is set to the position below the previous position

    }

}
/*
This function updates the position of enemy1
*/
void updateEnemy1Position(struct enemy1_t *enemy){

    // We set the current positions to previous position
    enemy->prevPosX = (*enemy).posX;
    enemy->prevPosY = (*enemy).posY;

    enemy->posY = (*enemy).posY + convertTo1814(1); // the y-position is set to the position below the previous position

}

/*
This function updates the position of enemy2
*/
void updateEnemy2Position(struct enemy2_t *enemy){

    // We set the current positions to previous position
    enemy->prevPosX=(*enemy).posX;
    enemy->prevPosY=(*enemy).posY;

    enemy->posY = (*enemy).posY + (1 << FIX14_SHIFT); // the y-position is set to the position below the previous position

}

/*
This function updates the position of enemy3
*/
void updateEnemy3Position(struct enemy3_t *enemy){

    // We set the current positions to previous position
    enemy->prevPosX=(*enemy).posX;
    enemy->prevPosY=(*enemy).posY;

    enemy->posY = (*enemy).posY + (1 << FIX14_SHIFT); // the y-position is set to the position below the previous position

}

/*
This function checks whether enemy1 has been hit or not and returns 1 if there's a hit
*/
uint32_t isEnemyOneHit(struct enemy1_t *e, struct spaceshipBullet_t *b1, struct spaceshipBullet_t *b2, struct spaceshipBullet_t *b3, struct spaceshipBullet_t *b4, struct spaceshipBullet_t *b5, struct spaceshipShieldBullet_t *sb1, struct spaceshipShieldBullet_t *sb2){

    uint32_t temp = 0;

    if ((*e).drawEnemy1==(1<<FIX14_SHIFT) && (((*b1).posX<=(*e).posX+(1<<FIX14_SHIFT) && ((*b1).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b1).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b1).posY>=(*e).posY)))){

        e->drawEnemy1=(0 << FIX14_SHIFT);
        b1->drawBullet=(0 << FIX14_SHIFT);
        temp = 1;

     } else if ((*e).drawEnemy1==(1<<FIX14_SHIFT) && (((*b2).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b2).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b2).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b2).posY>=(*e).posY))){

        e->drawEnemy1=(0 << FIX14_SHIFT);
        b2->drawBullet=(0 << FIX14_SHIFT);
        temp = 1;

     } else if ((*e).drawEnemy1==(1<<FIX14_SHIFT) && (((*b3).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b3).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b3).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b3).posY>=(*e).posY))){

        e->drawEnemy1=(0 << FIX14_SHIFT);
        b3->drawBullet=(0 << FIX14_SHIFT);
        temp = 1;

     } else if ((*e).drawEnemy1==(1<<FIX14_SHIFT) && (((*b4).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b4).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b4).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b4).posY>=(*e).posY))){

        e->drawEnemy1=(0 << FIX14_SHIFT);
        b4->drawBullet=(0 << FIX14_SHIFT);
        temp = 1;

     } else if ((*e).drawEnemy1==(1<<FIX14_SHIFT) && (((*b5).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b5).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b5).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b5).posY>=(*e).posY))){

        e->drawEnemy1=(0 << FIX14_SHIFT);
        b5->drawBullet=(0 << FIX14_SHIFT);
        temp = 1;

     } else if ((*e).drawEnemy1==(1<<FIX14_SHIFT) && (((*sb1).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*sb1).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*sb1).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*sb1).posY>=(*e).posY))){

        sb1->drawBullet=(0 << FIX14_SHIFT);
        temp = 0;

     } else if ((*e).drawEnemy1==(1<<FIX14_SHIFT) && (((*sb2).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*sb2).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*sb2).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*sb2).posY>=(*e).posY))){

        sb2->drawBullet=(0 << FIX14_SHIFT);
        temp = 0;

     } else {
        temp = 0;
     }
    return temp;
}

/*
This function checks whether enemy2 has been hit or not and returns 1 if there's a hit
*/
uint32_t isEnemyTwoHit(struct enemy2_t *e, struct spaceshipBullet_t *b1, struct spaceshipBullet_t *b2, struct spaceshipBullet_t *b3, struct spaceshipBullet_t *b4, struct spaceshipBullet_t *b5, struct spaceshipShieldBullet_t *sb1, struct spaceshipShieldBullet_t *sb2){

    uint32_t temp = 0;

    if ((*e).drawEnemy2==(1<<FIX14_SHIFT) && ((*b1).posX<=(*e).posX+(1<<FIX14_SHIFT) && ((*b1).posX>=(*e).posX-(1<<FIX14_SHIFT))) && (*e).posY==(*b1).posY){

        e->drawEnemy2=(0 << FIX14_SHIFT);
        b1->drawBullet=(0 << FIX14_SHIFT);
        temp = 1;

     } else if ((*e).drawEnemy2==(1<<FIX14_SHIFT) && (((*b2).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b2).posX>=(*e).posX-(1<<FIX14_SHIFT))) && (*e).posY==(*b2).posY){

        e->drawEnemy2=(0 << FIX14_SHIFT);
        b2->drawBullet=(0 << FIX14_SHIFT);
        temp = 1;

     } else if ((*e).drawEnemy2==(1<<FIX14_SHIFT) && (((*b3).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b3).posX>=(*e).posX-(1<<FIX14_SHIFT))) && (*e).posY==(*b3).posY){

        e->drawEnemy2=(0 << FIX14_SHIFT);
        b3->drawBullet=(0 << FIX14_SHIFT);
        temp = 1;

     } else if ((*e).drawEnemy2==(1<<FIX14_SHIFT) && (((*b4).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b4).posX>=(*e).posX-(1<<FIX14_SHIFT))) && (*e).posY==(*b4).posY){

        e->drawEnemy2=(0 << FIX14_SHIFT);
        b4->drawBullet=(0 << FIX14_SHIFT);
        temp = 1;

     } else if ((*e).drawEnemy2==(1<<FIX14_SHIFT) && (((*b5).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b5).posX>=(*e).posX-(1<<FIX14_SHIFT))) && (*e).posY==(*b5).posY){

        e->drawEnemy2=(0 << FIX14_SHIFT);
        b5->drawBullet=(0 << FIX14_SHIFT);
        temp = 1;

     } else if ((*e).drawEnemy2==(1<<FIX14_SHIFT) && (((*sb1).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*sb1).posX>=(*e).posX-(1<<FIX14_SHIFT))) && (*e).posY==(*sb1).posY){

        sb1->drawBullet=(0 << FIX14_SHIFT);
        temp = 0;

     } else if ((*e).drawEnemy2==(1<<FIX14_SHIFT) && (((*sb2).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*sb2).posX>=(*e).posX-(1<<FIX14_SHIFT))) && (*e).posY==(*sb2).posY){

        sb2->drawBullet=(0 << FIX14_SHIFT);
        temp = 0;

     } else {
        temp = 0;
     }
    return temp;
}




