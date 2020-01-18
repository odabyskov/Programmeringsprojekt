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
                spaceship->posX = (*spaceship).prevPosX + (1 << FIX14_SHIFT);
            } else {
                spaceship->posX = (65 << FIX14_SHIFT);
            }
        }
    }
}

/*
This function updates the bullet's position.
The bullet moves vertically upwards from where it was fired.
k determines what you shift - so if you want the position to change with 0.5 you set k=13
*/
void updateSpaceshipBulletPosition(struct bullet_t *bullet, struct spaceship_t *ship, char temp, uint32_t k){

    if (temp == 32 && bullet->drawBullet == 0 ){

        bullet->posX = (*ship).posX; // the x-position is set to the middle of the spaceship
        bullet->posY = (*ship).posY - (2 << FIX14_SHIFT); // the y-position is set to the top of the spaceship
        bullet->drawBullet = 1;

    } else if ((*bullet).drawBullet == 1 ){

        // We set the current positions to previous position
        bullet->prevPosX=(*bullet).posX;
        bullet->prevPosY=(*bullet).posY;

        // We update the current position
        bullet->posX = (*bullet).posX; // the x-position is set to the middle of the spaceship
        bullet->posY = (*bullet).posY - (1 << k); // the y-position is set to the position above the previous position

    }

}

/*
This function updates the bullet's position.
The bullet moves vertically upwards from where it was fired.
k determines what you shift - so if you want the position to change with 0.5 you set k=13
*/
void updateSpaceshipShieldBulletPosition(struct bullet_t *bullet, struct spaceship_t *ship, char temp, uint32_t k){

    if ( (temp == 'w' || temp == 'W') && bullet->drawBullet == 0 ){

        bullet->posX = (*ship).posX; // the x-position is set to the middle of the spaceship
        bullet->posY = (*ship).posY - (2 << FIX14_SHIFT); // the y-position is set to the top of the spaceship

        bullet->drawBullet = 1;

    } else if (bullet->drawBullet == 1 ){

        // We set the current positions to previous position
        bullet->prevPosX=(*bullet).posX;
        bullet->prevPosY=(*bullet).posY;

        // We update the current position
        bullet->posX = (*bullet).posX; // the x-position is set to the middle of the spaceship
        bullet->posY = (*bullet).posY - (1 << k); // the y-position is set to the position above the previous position

    }
}

/*
This function updates the bullet's position.
The bullet moves vertically downwards from where it was fired.
*/
void updateEnemyBulletPosition(struct bullet_t *enemyBullet, struct enemy_t *enemy, uint32_t k){

    if ( (*enemyBullet).drawBullet == 0 && (*enemy).drawEnemy == 1 ){

        enemyBullet->posX = (*enemy).posX; // the x-position is set to the middle of the enemy
        enemyBullet->posY = (*enemy).posY + (2 << FIX14_SHIFT); // the y-position is set to the bottom of the enemy
        enemyBullet->drawBullet = 1;

    } else if ( (*enemyBullet).drawBullet == 1 ){

        // We set the current positions to previous position
        enemyBullet->prevPosX=(*enemyBullet).posX;
        enemyBullet->prevPosY=(*enemyBullet).posY;

        // We update the current position
        enemyBullet->posX = (*enemyBullet).posX; // the x-position is set to the middle of the enemy
        enemyBullet->posY = (*enemyBullet).posY + (1 << k); // the y-position is set to the position below the previous position

    }

    if ((*enemyBullet).posY > 38 << FIX14_SHIFT ){
            (*enemyBullet).drawBullet = 0;
    }

}

/*
This function updates the position of an enemy/power-up
*/
void updateEnemyPosition(struct enemy_t *enemy, uint32_t k){
    if ( (*enemy).drawEnemy == 1 ){
    // We set the current positions to previous position
    enemy->prevPosX = (*enemy).posX;
    enemy->prevPosY = (*enemy).posY;
    enemy->posY = (*enemy).posY + (1 << k); // the y-position is set to the position below the previous position
    } else if ( (*enemy).drawEnemy == 0 ){
        enemy->posX = randomNumber(4,66);
        enemy->posY = 2 << FIX14_SHIFT;
    }
}

/*
This function checks whether enemy1 has been hit or not and returns 1 if there's a hit
*/
uint32_t isEnemyOneHit(struct enemy_t *e, struct bullet_t *b1, struct bullet_t *b2, struct bullet_t *b3, struct bullet_t *b4, struct bullet_t *b5, struct bullet_t *sb1, struct bullet_t *sb2){

    uint32_t temp = 0;

    if ((*e).drawEnemy==1 && (((*b1).posX<=(*e).posX+(1<<FIX14_SHIFT) && ((*b1).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b1).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b1).posY>=(*e).posY)))){

        e->drawEnemy=0;
        b1->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b2).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b2).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b2).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b2).posY>=(*e).posY))){

        e->drawEnemy=0;
        b2->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b3).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b3).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b3).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b3).posY>=(*e).posY))){

        e->drawEnemy=0;
        b3->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b4).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b4).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b4).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b4).posY>=(*e).posY))){

        e->drawEnemy=0;
        b4->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b5).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b5).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b5).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b5).posY>=(*e).posY))){

        e->drawEnemy=0;
        b5->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*sb1).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*sb1).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*sb1).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*sb1).posY>=(*e).posY))){

        sb1->drawBullet=0;
        temp = 0;

     } else if ((*e).drawEnemy==1 && (((*sb2).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*sb2).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*sb2).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*sb2).posY>=(*e).posY))){

        sb2->drawBullet=0;
        temp = 0;

     } else {
        temp = 0;
     }
    return temp;
}


/*
This function checks whether enemy2 has been hit or not and returns 1 if there's a hit
*/
uint32_t isEnemyTwoHit(struct enemy_t *e, struct bullet_t *b1, struct bullet_t *b2, struct bullet_t *b3, struct bullet_t *b4, struct bullet_t *b5, struct bullet_t *sb1, struct bullet_t *sb2){

    uint32_t temp = 0;

    if ((*e).drawEnemy==1 && ((*b1).posX<=(*e).posX+(1<<FIX14_SHIFT) && ((*b1).posX>=(*e).posX-(1<<FIX14_SHIFT))) && (*e).posY==(*b1).posY){

        e->drawEnemy=0;
        b1->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b2).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b2).posX>=(*e).posX-(1<<FIX14_SHIFT))) && (*e).posY==(*b2).posY){

        e->drawEnemy=0;
        b2->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b3).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b3).posX>=(*e).posX-(1<<FIX14_SHIFT))) && (*e).posY==(*b3).posY){

        e->drawEnemy=0;
        b3->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b4).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b4).posX>=(*e).posX-(1<<FIX14_SHIFT))) && (*e).posY==(*b4).posY){

        e->drawEnemy=0;
        b4->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b5).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b5).posX>=(*e).posX-(1<<FIX14_SHIFT))) && (*e).posY==(*b5).posY){

        e->drawEnemy=0;
        b5->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*sb1).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*sb1).posX>=(*e).posX-(1<<FIX14_SHIFT))) && (*e).posY==(*sb1).posY){

        sb1->drawBullet=0;
        temp = 0;

     } else if ((*e).drawEnemy==1 && (((*sb2).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*sb2).posX>=(*e).posX-(1<<FIX14_SHIFT))) && (*e).posY==(*sb2).posY){

        sb2->drawBullet=0;
        temp = 0;

     } else {
        temp = 0;
     }
    return temp;
}

/*
        -- UNDER CONSTRUCTION --
This function checks whether enemy3 has been hit or not and returns 1 if there's a hit
* /
uint32_t isEnemyThreeHit(struct enemy_t *e, struct bullet_t *b1, struct bullet_t *b2, struct bullet_t *b3, struct bullet_t *b4, struct bullet_t *b5, struct bullet_t *sb1, struct bullet_t *sb2){

    uint32_t temp = 0;

    if ((*e).drawEnemy3==(1<<FIX14_SHIFT) && (((*b1).posX<=(*e).posX+(1<<FIX14_SHIFT) && ((*b1).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b1).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b1).posY>=(*e).posY)))){


        b1->drawBullet=(0 << FIX14_SHIFT);
        temp = 0;

     } else if ((*e).drawEnemy3==(1<<FIX14_SHIFT) && (((*b2).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b2).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b2).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b2).posY>=(*e).posY))){


        b2->drawBullet=(0 << FIX14_SHIFT);
        temp = 0;

     } else if ((*e).drawEnemy3==(1<<FIX14_SHIFT) && (((*b3).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b3).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b3).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b3).posY>=(*e).posY))){


        b3->drawBullet=(0 << FIX14_SHIFT);
        temp = 0;

     } else if ((*e).drawEnemy3==(1<<FIX14_SHIFT) && (((*b4).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b4).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b4).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b4).posY>=(*e).posY))){

        b4->drawBullet=(0 << FIX14_SHIFT);
        temp = 0;

     } else if ((*e).drawEnemy3==(1<<FIX14_SHIFT) && (((*b5).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b5).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b5).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b5).posY>=(*e).posY))){

        b5->drawBullet=(0 << FIX14_SHIFT);
        temp = 0;

     } else if ((*e).drawEnemy3==(1<<FIX14_SHIFT) && (((*sb1).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*sb1).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*sb1).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*sb1).posY>=(*e).posY))){

        e->drawEnemy3=(0 << FIX14_SHIFT);
        sb1->drawBullet=(0 << FIX14_SHIFT);
        temp = 1;

     } else if ((*e).drawEnemy3==(1<<FIX14_SHIFT) && (((*sb2).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*sb2).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*sb2).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*sb2).posY>=(*e).posY))){

        e->drawEnemy3=(0 << FIX14_SHIFT);
        sb2->drawBullet=(0 << FIX14_SHIFT);
        temp = 1;

     } else {
        temp = 0;
     }
    return temp;
} */

/*
This function checks whether the player's spaceship has been hit or not and returns 1 if there's a hit
*/
uint32_t isSpaceshipHit(struct spaceship_t *s,struct enemy_t *e1,struct enemy_t *e2, struct enemy_t *e3,struct enemy_t *e4,struct enemy_t *e5,struct enemy_t *e6,struct enemy_t *e7,struct enemy_t *e8,struct enemy_t *e9,struct bullet_t *eb1,struct bullet_t *eb2,struct bullet_t *eb3){

    uint32_t temp = 0;
/*
Player is hit by enemy bullets
*/
    if ( (*eb1).drawBullet == 1 && ( ( (*eb1).posX <= (*s).posX+(2<<FIX14_SHIFT) && ( (*eb1).posX>=(*s).posX-(2<<FIX14_SHIFT) ) && ((*eb1).posY <= (*s).posY+(1<<FIX14_SHIFT)) && ((*eb1).posY >= (*s).posY-(1<<FIX14_SHIFT) ) ) ) ){
        eb1->drawBullet = 0;
        temp = 1;

    } else if ( (*eb2).drawBullet == 1 && ( ( (*eb2).posX <= (*s).posX+(2<<FIX14_SHIFT) && ( (*eb2).posX>=(*s).posX-(2<<FIX14_SHIFT) ) && ((*eb2).posY <= (*s).posY+(1<<FIX14_SHIFT)) && ((*eb2).posY >= (*s).posY-(1<<FIX14_SHIFT) ) ) ) ){
        eb2->drawBullet = 0;
        temp = 1;

    } else if ( (*eb3).drawBullet == 1 && ( ( (*eb3).posX <= (*s).posX+(2<<FIX14_SHIFT) && ( (*eb3).posX>=(*s).posX-(2<<FIX14_SHIFT) ) && ((*eb3).posY <= (*s).posY+(1<<FIX14_SHIFT)) && ((*eb3).posY >= (*s).posY-(1<<FIX14_SHIFT) ) ) ) ){
        eb3->drawBullet = 0;
        temp = 1;
/*
Enemy players reaches bottom of the screen
*/
    } if ( (*e1).drawEnemy == 1 && (*e1).posY >= (38<<FIX14_SHIFT)){
        e1->drawEnemy = 0;
        temp = 1;

    } else if ( (*e2).drawEnemy == 1 && (*e2).posY >= (38<<FIX14_SHIFT)){
        e2->drawEnemy = 0;
        temp = 1;

    } else if ( (*e3).drawEnemy == 1 && (*e3).posY >= (38<<FIX14_SHIFT)){
        e3->drawEnemy = 0;
        temp = 1;

    } else if ( (*e4).drawEnemy == 1 && (*e4).posY >= (38<<FIX14_SHIFT)){
        e4->drawEnemy = 0;
        temp = 1;

    } else if ( (*e5).drawEnemy == 1 && (*e5).posY >= (38<<FIX14_SHIFT)){
        e5->drawEnemy = 0;
        temp = 1;

    } else if ( (*e6).drawEnemy == 1 && (*e6).posY >= (38<<FIX14_SHIFT)){
        e6->drawEnemy = 0;
        temp = 1;

    } else if ( (*e7).drawEnemy == 1 && (*e7).posY >= (37<<FIX14_SHIFT)){
        e7->drawEnemy = 0;
        temp = 1;

    } else if ( (*e8).drawEnemy == 1 && (*e8).posY >= (37<<FIX14_SHIFT)){
        e8->drawEnemy = 0;
        temp = 1;

    } else if ( (*e9).drawEnemy == 1 && (*e9).posY >= (37<<FIX14_SHIFT)){
        e9->drawEnemy = 0;
        temp = 1;
    }
    return temp;
}
