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
This function generates a random 18.14 fixed point number in the range from lower to upper
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
This function calculates sine to the angle given as argument
*/
int32_t calculateSin(int32_t deg){
    int degr = (deg * 512)/360;
    return (int32_t)(SIN[degr & 0x1FF]);
}

/*
This function calculates cosine to the angle given as argument
*/
int32_t calculateCos(int32_t deg){
    return calculateSin(deg+90); // Cosine to an angle equals sine to the angle plus 90 degrees
}

/*
This function rotates the direction of a bullet with the angle given in the argument
*/
void rotateDirection(struct bullet_t *b, int deg){
    int32_t x1 = (*b).velX;
    int32_t y1 = (*b).velY;

    b->velX = FIX14_MULT(x1,calculateCos(deg))-FIX14_MULT(y1,calculateSin(deg));
    b->velY = FIX14_MULT(x1,calculateSin(deg))+FIX14_MULT(y1,calculateCos(deg));

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
If the user presses the 'a'-key or pulls the joystick left the spaceship moves one step to the left.
If the user presses the 'd'-key or pulls the joystick to the right the spaceship moves one step to the right.
*/
void updateSpaceshipPosition(struct spaceship_t *spaceship, char temp){

    if ( temp == 'a' || temp == 'A' || temp == 'd' || temp == 'D' || temp == 4 || temp == 8 ){

        // We set the current position to the previous position
        spaceship->prevPosX=(*spaceship).posX;
        spaceship->prevPosY=(*spaceship).posY;

        // We update current position
        if( temp=='a' || temp == 'A' || temp == 4 ){
            if ((*spaceship).posX > (5 << FIX14_SHIFT)){
                spaceship->posX = (*spaceship).prevPosX - (1 << FIX14_SHIFT);
            } else {
                spaceship->posX = (5 << FIX14_SHIFT);
            }
        }
         else if( temp=='d' || temp == 'D' || temp == 8 ){
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

    if ( (temp == 32 || temp == 16) && bullet->drawBullet == 0 ){

        bullet->posX = (*ship).posX; // The x-position is set to the middle of the spaceship
        bullet->posY = (*ship).posY - (2 << FIX14_SHIFT); // The y-position is set to the top of the spaceship
        bullet->drawBullet = 1;
        bullet->velX = 0 << FIX14_SHIFT;
        bullet->velY = 1 << FIX14_SHIFT;

    } else if ((*bullet).drawBullet == 1 ){

        // We set the current positions to previous position
        bullet->prevPosX=(*bullet).posX;
        bullet->prevPosY=(*bullet).posY;

        // We update the current position
        bullet->posX = (*bullet).prevPosX + (*bullet).velX;
        bullet->posY = (*bullet).prevPosY - ((*bullet).velY >> 14-k);
    }
}

/*
This function updates the bullet's position.
The bullet moves vertically upwards from where it was fired.
k determines what you shift - so if you want the position to change with 0.5 you set k=13
*/
void updateSpaceshipShieldBulletPosition(struct bullet_t *bullet, struct spaceship_t *ship, char temp, uint32_t k){

    if ( (temp == 'w' || temp == 'W' || temp == 1) && bullet->drawBullet == 0 ){

        bullet->posX = (*ship).posX; // The x-position is set to the middle of the spaceship
        bullet->posY = (*ship).posY - (2 << FIX14_SHIFT); // The y-position is set to the top of the spaceship

        bullet->drawBullet = 1;

    } else if (bullet->drawBullet == 1 ){

        // We set the current positions to previous position
        bullet->prevPosX=(*bullet).posX;
        bullet->prevPosY=(*bullet).posY;

        // We update the current position
        bullet->posX = (*bullet).posX; // The x-position is set to the middle of the spaceship
        bullet->posY = (*bullet).posY - (1 << k); // The y-position is set to the position above the previous position

    }
}

/*
This function updates the bullet's position.
The bullet moves vertically downwards from where it was fired.
*/
void updateEnemyBulletPosition(struct bullet_t *enemyBullet, struct enemy_t *enemy, uint32_t k){

    if ( (*enemyBullet).drawBullet == 0 && (*enemy).drawEnemy == 1 ){

        enemyBullet->posX = (*enemy).posX; // The x-position is set to the middle of the enemy
        enemyBullet->posY = (*enemy).posY + (2 << FIX14_SHIFT); // The y-position is set to the bottom of the enemy
        enemyBullet->drawBullet = 1;
        enemyBullet->velX = 0 << FIX14_SHIFT;
        enemyBullet->velY = 1 << FIX14_SHIFT;

    } else if ( (*enemyBullet).drawBullet == 1 ){

        // We set the current positions to previous position
        enemyBullet->prevPosX=(*enemyBullet).posX;
        enemyBullet->prevPosY=(*enemyBullet).posY;

        // We update the current position
        enemyBullet->posX = (*enemyBullet).prevPosX + (*enemyBullet).velX; // The x-position is set to the middle of the enemy
        enemyBullet->posY = (*enemyBullet).posY + ((*enemyBullet).velY >> 14-k); // The y-position is set to the position below the previous position

    }

    if ((*enemyBullet).posY > 38 << FIX14_SHIFT ){
            (*enemyBullet).drawBullet = 0;

    }
}

/*
This function updates the position of an enemy
*/
void updateEnemyPosition(struct enemy_t *enemy, uint32_t k){

    if ( (*enemy).drawEnemy == 1 ){
        // We set the current positions to previous position
        enemy->prevPosX = (*enemy).posX;
        enemy->prevPosY = (*enemy).posY;
        enemy->posY = (*enemy).posY + (1 << k); // The y-position is set to the position below the previous position

    } else if ( (*enemy).drawEnemy == 0 ){ // If the enemy has been killed or made it to the planet,
                                           // it is initialized at a random position in the top of the screen
        enemy->posX = randomNumber(4,66);
        enemy->posY = 2 << FIX14_SHIFT;
    }
}

/*
This function updates the position of a power-up
*/
void updateHeartPosition(struct enemy_t *heart, uint32_t k, uint32_t playerHits){

    if ( (*heart).drawEnemy == 1 ){
        // We set the current positions to previous position
        heart->prevPosX = (*heart).posX;
        heart->prevPosY = (*heart).posY;
        heart->posY = (*heart).posY + (1 << k); // The y-position is set to the position below the previous position

    } else if ( (*heart).drawEnemy == 0 && playerHits ==2){
        heart->posX = randomNumber(4,65);
        heart->posY = 2 << FIX14_SHIFT;
        heart->drawEnemy=1;
    }
    if ((*heart).posY >= (37<<FIX14_SHIFT)){
        heart->drawEnemy=0;
    }
}

/*
*
*
*
* The following functions check whether the different objects have
* been hit by a bullet.
*
*
*
*/

/*
This function checks whether enemy1 has been hit or not and returns 1 if there's a hit
*/
uint32_t isEnemyOneHit(struct enemy_t *e, struct bullet_t *b1, struct bullet_t *b2, struct bullet_t *b3, struct bullet_t *b4, struct bullet_t *b5, struct bullet_t *sb1, struct bullet_t *sb2){

    uint32_t temp = 0;

    if ((*e).drawEnemy==1 && (((*b1).posX<=(*e).posX+(1<<FIX14_SHIFT) && ((*b1).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b1).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b1).posY>=(*e).posY)))){

        e->drawEnemy=0;
        e->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        e->posY=2 << FIX14_SHIFT;
        b1->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b2).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b2).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b2).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b2).posY>=(*e).posY))){

        e->drawEnemy=0;
        e->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        e->posY=2 << FIX14_SHIFT;
        b2->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b3).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b3).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b3).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b3).posY>=(*e).posY))){

        e->drawEnemy=0;
        e->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        e->posY=2 << FIX14_SHIFT;
        b3->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b4).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b4).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b4).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b4).posY>=(*e).posY))){

        e->drawEnemy=0;
        e->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        e->posY=2 << FIX14_SHIFT;
        b4->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b5).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b5).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*b5).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b5).posY>=(*e).posY))){

        e->drawEnemy=0;
        e->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        e->posY=2 << FIX14_SHIFT;
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

    if ((*e).drawEnemy==1 && ((*b1).posX<=(*e).posX+(1<<FIX14_SHIFT) && ((*b1).posX>=(*e).posX-(1<<FIX14_SHIFT))) && ((*b1).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b1).posY>=(*e).posY)){

        e->drawEnemy=0;
        e->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        e->posY=2 << FIX14_SHIFT;
        b1->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b2).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b2).posX>=(*e).posX-(1<<FIX14_SHIFT))) && ((*b2).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b2).posY>=(*e).posY)){

        e->drawEnemy=0;
        e->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        e->posY=2 << FIX14_SHIFT;
        b2->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b3).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b3).posX>=(*e).posX-(1<<FIX14_SHIFT))) && ((*b3).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b3).posY>=(*e).posY)){

        e->drawEnemy=0;
        e->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        e->posY=2 << FIX14_SHIFT;
        b3->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b4).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b4).posX>=(*e).posX-(1<<FIX14_SHIFT))) && ((*b4).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b4).posY>=(*e).posY)){

        e->drawEnemy=0;
        e->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        e->posY=2 << FIX14_SHIFT;
        b4->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*b5).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*b5).posX>=(*e).posX-(1<<FIX14_SHIFT))) && ((*b5).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*b5).posY>=(*e).posY)){

        e->drawEnemy=0;
        e->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        e->posY=2 << FIX14_SHIFT;
        b5->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*sb1).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*sb1).posX>=(*e).posX-(1<<FIX14_SHIFT))) && ((*sb1).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*sb1).posY>=(*e).posY)){

        sb1->drawBullet=0;
        temp = 0;

     } else if ((*e).drawEnemy==1 && (((*sb2).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*sb2).posX>=(*e).posX-(1<<FIX14_SHIFT))) && ((*sb2).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*sb2).posY>=(*e).posY)){

        sb2->drawBullet=0;
        temp = 0;

     } else {
        temp = 0;
     }
    return temp;
}

/*
This function checks whether enemy3 has been hit or not and returns 1 if there's a hit
*/
uint32_t isEnemyThreeHit(struct enemy_t *e, struct bullet_t *b1, struct bullet_t *b2, struct bullet_t *b3, struct bullet_t *b4, struct bullet_t *b5, struct bullet_t *sb1, struct bullet_t *sb2, struct bullet_t *eb1, struct bullet_t *eb2, struct bullet_t *eb3){

    uint32_t temp = 0;

    // Player bullets
    if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*b1).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*b1).posY) && ((*e).posX-(6<<FIX14_SHIFT) <= (*b1).posX && (*e).posX > (*b1).posX))){
        rotateDirection(b1,5);
        temp = 0;
    } else if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*b1).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*b1).posY) && ((*e).posX <= (*b1).posX && (*e).posX+(6<<FIX14_SHIFT) >= (*b1).posX))){
        rotateDirection(b1,355);
        temp = 0;
    } else if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*b2).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*b2).posY) && ((*e).posX-(6<<FIX14_SHIFT) <= (*b2).posX && (*e).posX > (*b2).posX))){
        rotateDirection(b2,5);
        temp = 0;
    } else if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*b2).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*b2).posY) && ((*e).posX <= (*b2).posX && (*e).posX+(6<<FIX14_SHIFT) >= (*b2).posX))){
        rotateDirection(b2,355);
        temp = 0;
    } else if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*b3).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*b3).posY) && ((*e).posX-(6<<FIX14_SHIFT) <= (*b3).posX && (*e).posX > (*b3).posX))){
        rotateDirection(b3,5);
        temp = 0;
    } else if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*b3).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*b3).posY) && ((*e).posX <= (*b3).posX && (*e).posX+(6<<FIX14_SHIFT) >= (*b3).posX))){
        rotateDirection(b3,355);
        temp = 0;
    } else if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*b4).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*b4).posY) && ((*e).posX-(6<<FIX14_SHIFT) <= (*b4).posX && (*e).posX > (*b4).posX))){
        rotateDirection(b4,5);
        temp = 0;
    } else if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*b4).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*b4).posY) && ((*e).posX <= (*b4).posX && (*e).posX+(6<<FIX14_SHIFT) >= (*b4).posX))){
        rotateDirection(b4,355);
        temp = 0;
    } else if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*b5).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*b5).posY) && ((*e).posX-(6<<FIX14_SHIFT) <= (*b5).posX && (*e).posX > (*b5).posX))){
        rotateDirection(b5,5);
        temp = 0;
    } else if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*b5).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*b5).posY) && ((*e).posX <= (*b5).posX && (*e).posX+(6<<FIX14_SHIFT) >= (*b5).posX))){
        rotateDirection(b5,355);
        temp = 0;
    }

    // Enemy bullets
    if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*eb1).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*eb1).posY) && ((*e).posX-(6<<FIX14_SHIFT) <= (*eb1).posX && (*e).posX > (*eb1).posX))){
        rotateDirection(eb1,5);
        temp = 0;
    } else if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*eb1).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*eb1).posY) && ((*e).posX <= (*eb1).posX && (*e).posX+(6<<FIX14_SHIFT) >= (*eb1).posX))){
        rotateDirection(eb1,355);
        temp = 0;
    } else if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*eb2).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*eb2).posY) && ((*e).posX-(6<<FIX14_SHIFT) <= (*eb2).posX && (*e).posX > (*eb2).posX))){
        rotateDirection(eb2,5);
        temp = 0;
    } else if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*eb2).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*eb2).posY) && ((*e).posX <= (*eb2).posX && (*e).posX+(6<<FIX14_SHIFT) >= (*eb2).posX))){
        rotateDirection(eb2,355);
        temp = 0;
    } else if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*eb3).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*eb3).posY) && ((*e).posX-(6<<FIX14_SHIFT) <= (*eb3).posX && (*e).posX > (*eb3).posX))){
        rotateDirection(eb3,5);
        temp = 0;
    } else if ((*e).drawEnemy==1 && (( (*e).posY+(3<<FIX14_SHIFT) <= (*eb3).posY && (*e).posY+(11<<FIX14_SHIFT) >= (*eb3).posY) && ((*e).posX <= (*eb3).posX && (*e).posX+(6<<FIX14_SHIFT) >= (*eb3).posX))){
        rotateDirection(eb3,355);
        temp = 0;
    }

    // Shield-buster bullets
    if ((*e).drawEnemy==1 && (((*sb1).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*sb1).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*sb1).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*sb1).posY>=(*e).posY))){

        e->drawEnemy=0;
        e->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        e->posY=2 << FIX14_SHIFT;
        sb1->drawBullet=0;
        temp = 1;

     } else if ((*e).drawEnemy==1 && (((*sb2).posX<=(*e).posX+(1<<FIX14_SHIFT)) && ((*sb2).posX>=(*e).posX-(1<<FIX14_SHIFT)) && ((*sb2).posY<=(*e).posY+(1<<FIX14_SHIFT)) && ((*sb2).posY>=(*e).posY))){

        e->drawEnemy=0;
        e->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        e->posY=2 << FIX14_SHIFT;
        sb2->drawBullet=0;
        temp = 1;

     } else {
        temp = 0;
     }
}

/*
This function checks whether the power-up has been hit or not and returns 1 if there's a hit
*/
uint32_t isHeartHit(struct enemy_t *h, struct bullet_t *b1, struct bullet_t *b2, struct bullet_t *b3, struct bullet_t *b4, struct bullet_t *b5, struct bullet_t *sb1, struct bullet_t *sb2){

    uint32_t temp = 0;

    if ((*h).drawEnemy==1 && (((*b1).posX<=(*h).posX+(2<<FIX14_SHIFT) && ((*b1).posX>=(*h).posX-(1<<FIX14_SHIFT)) && ((*b1).posY<=(*h).posY+(1<<FIX14_SHIFT)) && ((*b1).posY>=(*h).posY)))){

        h->drawEnemy=0;
        h->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        h->posY=2 << FIX14_SHIFT;
        b1->drawBullet=0;
        temp = 1;

     } else if ((*h).drawEnemy==1 && (((*b2).posX<=(*h).posX+(2<<FIX14_SHIFT)) && ((*b2).posX>=(*h).posX-(1<<FIX14_SHIFT)) && ((*b2).posY<=(*h).posY+(1<<FIX14_SHIFT)) && ((*b2).posY>=(*h).posY))){

        h->drawEnemy=0;
        h->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        h->posY=2 << FIX14_SHIFT;
        b2->drawBullet=0;
        temp = 1;

     } else if ((*h).drawEnemy==1 && (((*b3).posX<=(*h).posX+(2<<FIX14_SHIFT)) && ((*b3).posX>=(*h).posX-(1<<FIX14_SHIFT)) && ((*b3).posY<=(*h).posY+(1<<FIX14_SHIFT)) && ((*b3).posY>=(*h).posY))){

        h->drawEnemy=0;
        h->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        h->posY=2 << FIX14_SHIFT;
        b3->drawBullet=0;
        temp = 1;

     } else if ((*h).drawEnemy==1 && (((*b4).posX<=(*h).posX+(2<<FIX14_SHIFT)) && ((*b4).posX>=(*h).posX-(1<<FIX14_SHIFT)) && ((*b4).posY<=(*h).posY+(1<<FIX14_SHIFT)) && ((*b4).posY>=(*h).posY))){

        h->drawEnemy=0;
        h->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        h->posY=2 << FIX14_SHIFT;
        b4->drawBullet=0;
        temp = 1;

     } else if ((*h).drawEnemy==1 && (((*b5).posX<=(*h).posX+(2<<FIX14_SHIFT)) && ((*b5).posX>=(*h).posX-(1<<FIX14_SHIFT)) && ((*b5).posY<=(*h).posY+(1<<FIX14_SHIFT)) && ((*b5).posY>=(*h).posY))){

        h->drawEnemy=0;
        h->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        h->posY=2 << FIX14_SHIFT;
        b5->drawBullet=0;
        temp = 1;

     } else if ((*h).drawEnemy==1 && (((*sb1).posX<=(*h).posX+(2<<FIX14_SHIFT)) && ((*sb1).posX>=(*h).posX-(1<<FIX14_SHIFT)) && ((*sb1).posY<=(*h).posY+(1<<FIX14_SHIFT)) && ((*sb1).posY>=(*h).posY))){

        h->drawEnemy=0;
        h->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        h->posY=2 << FIX14_SHIFT;
        sb1->drawBullet=0;
        temp = 1;

     } else if ((*h).drawEnemy==1 && (((*sb2).posX<=(*h).posX+(2<<FIX14_SHIFT)) && ((*sb2).posX>=(*h).posX-(1<<FIX14_SHIFT)) && ((*sb2).posY<=(*h).posY+(1<<FIX14_SHIFT)) && ((*sb2).posY>=(*h).posY))){

        h->drawEnemy=0;
        h->posX=randomNumber(4,66); // The x-position is generated randomly within the game window
        h->posY=2 << FIX14_SHIFT;
        sb2->drawBullet=0;
        temp = 1;

     } else {
        temp = 0;
     }
    return temp;
}

/*
This function checks whether the player's spaceship has been hit or not
or if an enemy has reached the planet. It returns 1 if one of these cases occur.
*/
uint32_t isSpaceshipHit(struct spaceship_t *s,struct enemy_t *e1,struct enemy_t *e2, struct enemy_t *e3,struct enemy_t *e4,struct enemy_t *e5,struct enemy_t *e6,struct enemy_t *e7,struct enemy_t *e8,struct enemy_t *e9,struct bullet_t *eb1,struct bullet_t *eb2,struct bullet_t *eb3){

    uint32_t temp = 0;

    // Check if player has been hit by bullet
    if ( (*eb1).drawBullet == 1 && ( ( (*eb1).posX <= (*s).posX+(2<<FIX14_SHIFT) && ( (*eb1).posX>=(*s).posX-(2<<FIX14_SHIFT) ) && ((*eb1).posY <= (*s).posY+(1<<FIX14_SHIFT)) && ((*eb1).posY >= (*s).posY-(1<<FIX14_SHIFT) ) ) ) ){
        eb1->drawBullet = 0;
        temp = 1;

    } else if ( (*eb2).drawBullet == 1 && ( ( (*eb2).posX <= (*s).posX+(2<<FIX14_SHIFT) && ( (*eb2).posX>=(*s).posX-(2<<FIX14_SHIFT) ) && ((*eb2).posY <= (*s).posY+(1<<FIX14_SHIFT)) && ((*eb2).posY >= (*s).posY-(1<<FIX14_SHIFT) ) ) ) ){
        eb2->drawBullet = 0;
        temp = 1;

    } else if ( (*eb3).drawBullet == 1 && ( ( (*eb3).posX <= (*s).posX+(2<<FIX14_SHIFT) && ( (*eb3).posX>=(*s).posX-(2<<FIX14_SHIFT) ) && ((*eb3).posY <= (*s).posY+(1<<FIX14_SHIFT)) && ((*eb3).posY >= (*s).posY-(1<<FIX14_SHIFT) ) ) ) ){
        eb3->drawBullet = 0;
        temp = 1;

    // Check if enemy players reach bottom of the screen
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

