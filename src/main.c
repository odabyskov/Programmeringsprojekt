#include "stm32f30x_conf.h" // STM32 config
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "ansi.h"
#include "timing.h"
#include "objects.h"
#include "calc.h"

// set flags
char temp; // input flags
int time = 0, hits = 0, iter = 0, difficulty, playerHits; // time flag, damage flag and game state flag
uint32_t velBullet = 13; // Velocity of the bullets (determined by shifting 1 tis number of places to the left)
uint32_t velEnemy = 12; // Velocity of the enemies (determined by shifting 1 tis number of places to the left)

int main(void)
{
//uart_init( 9600 );
uart_init(115200);

/*
mainmenu
*/
clrscr();
gotoxy(1,1);
printf("w/s to choose between menubars.\n");
printf("spacebar to select the highlighted menubar.");
difficulty = mainmenu();
clrscr();

while(difficulty != 0){ // while playing

/*
Initialize the game
*/
setTimer();
initCounter(&counter);
playerHits = 0;
    
struct spaceship_t ship; // Spaceship

struct bullet_t b1; // Regular bullets
struct bullet_t b2;
struct bullet_t b3;
struct bullet_t b4;
struct bullet_t b5;
struct bullet_t sb1; // Shield bullets
struct bullet_t sb2;
struct bullet_t eb1; // Enemy bullets
struct bullet_t eb2;
struct bullet_t eb3;

struct enemy_t fighter1; // Enemies
struct enemy_t fighter2;
struct enemy_t fighter3;
struct enemy_t grunt1;
struct enemy_t grunt2;
struct enemy_t grunt3;
struct enemy_t shield1;
struct enemy_t shield2;
struct enemy_t shield3;

// Initialize the player
initSpaceship(&ship);
drawSpaceship(&ship);

// Initialize the bullets
initBullet(&b1);
initBullet(&b2);
initBullet(&b3);
initBullet(&b4);
initBullet(&b5);
initBullet(&sb1);
initBullet(&sb2);
initBullet(&eb1);
initBullet(&eb2);
initBullet(&eb3);

// Initialize the enemies
initEnemy(&fighter1);
initEnemy(&fighter2);
initEnemy(&fighter3);
initEnemy(&grunt1);
initEnemy(&grunt2);
initEnemy(&grunt3);
initEnemy(&shield1);
initEnemy(&shield2);
initEnemy(&shield3);


drawGameWindow();

/*
Game Start
*/
while(1){ 
//while(playerHits < 3) // while not dead

/*
Input
*/
time = counter.time << FIX14_SHIFT;
temp = uart_get_char(); // get player input a = 97, d = 100, space = 32
uart_clear();

/*
Boss key screen
*/
if (temp == 'b' || temp == 'B'){
    clrscr();
    printf("Microsoft [Version 10.0.18362.535]");
    printf("(c) 2019 Microsoft Corporation. Alle rettigheder forbeholdes");
    printf(" ");
    printf(" ");
    printf("C:/Users/LookBusy>");
while(uart_get_count() < 1){}
clrscr();
}

/*
Calculation
*/

/*
Spawn enemies in intervals
*/
if ( counter.time % 900 > 0 && counter.time % 900 < 12 )
    grunt1.drawEnemy = 1;
else if ( counter.time % 900 > 100 && counter.time % 900 < 112 )
    grunt2.drawEnemy = 1;
else if ( counter.time % 900 > 200 && counter.time % 900 < 212 )
    fighter1.drawEnemy = 1;
else if ( counter.time % 900 > 300 && counter.time % 900 < 312 )
    shield1.drawEnemy = 1;
else if ( counter.time % 900 > 400 && counter.time % 900 < 412 )
    grunt3.drawEnemy = 1;
else if ( counter.time % 900 > 500 && counter.time % 900 < 512 )
    shield2.drawEnemy = 1;
else if ( counter.time % 900 > 600 && counter.time % 900 < 612 )
    fighter2.drawEnemy = 1;
else if ( counter.time % 900 > 700 && counter.time % 900 < 712 )
    fighter3.drawEnemy = 1;
else if ( counter.time % 900 > 800 && counter.time % 900 < 812 )
    shield3.drawEnemy = 1;

    if (b1.drawBullet == 0 ){
        updateSpaceshipBulletPosition(&b1, &ship, temp, velBullet);

    }else if (b2.drawBullet == 0 ){
        updateSpaceshipBulletPosition(&b2, &ship, temp, velBullet);

    }else if (b3.drawBullet == 0 ){
        updateSpaceshipBulletPosition(&b3, &ship, temp, velBullet);

    }else if (b4.drawBullet == 0 ){
        updateSpaceshipBulletPosition(&b4, &ship, temp, velBullet);

    }else if (b5.drawBullet == 0 ){
        updateSpaceshipBulletPosition(&b5, &ship, temp, velBullet);
    }
    if (sb1.drawBullet == 0){
        updateSpaceshipShieldBulletPosition(&sb1, &ship, temp, velBullet);

    } else if (sb2.drawBullet == 0){
        updateSpaceshipShieldBulletPosition(&sb2, &ship, temp, velBullet);
    }

if (temp == 97 || temp == 100 )
    updateSpaceshipPosition(&ship, temp);
    updateSpaceshipBulletPosition(&b1, &ship, 0, velBullet);
    updateSpaceshipBulletPosition(&b2, &ship, 0, velBullet);
    updateSpaceshipBulletPosition(&b3, &ship, 0, velBullet);
    updateSpaceshipBulletPosition(&b4, &ship, 0, velBullet);
    updateSpaceshipBulletPosition(&b5, &ship, 0, velBullet);
    updateSpaceshipShieldBulletPosition(&sb1, &ship, 0, velBullet);
    updateSpaceshipShieldBulletPosition(&sb2, &ship, 0, velBullet);

    updateEnemyPosition(&fighter1, velEnemy);
    updateEnemyPosition(&fighter2, velEnemy);
    updateEnemyPosition(&fighter3, velEnemy);
    updateEnemyPosition(&grunt1, velEnemy);
    updateEnemyPosition(&grunt2, velEnemy);
    updateEnemyPosition(&grunt3, velEnemy);
    updateEnemyPosition(&shield1, velEnemy);
    updateEnemyPosition(&shield2, velEnemy);
    updateEnemyPosition(&shield3, velEnemy);
    updateEnemyBulletPosition(&eb1,&fighter1, velBullet);
    updateEnemyBulletPosition(&eb2,&fighter2, velBullet);
    updateEnemyBulletPosition(&eb3,&fighter3, velBullet);

    playerHits = playerHits + isSpaceshipHit(&ship,&fighter1,&fighter2,&fighter3,&grunt1,&grunt2,&grunt3,&shield1,&shield2,&shield3,&eb1,&eb2,&eb3);

/*
Drawing
*/
drawSpaceship(&ship);
drawSpaceshipBullet(&b1);
drawSpaceshipBullet(&b2);
drawSpaceshipBullet(&b3);
drawSpaceshipBullet(&b4);
drawSpaceshipBullet(&b5);
drawSpaceshipShieldBullet(&sb1);
drawSpaceshipShieldBullet(&sb2);

drawEnemyOne(&fighter1);
drawEnemyOne(&fighter2);
drawEnemyOne(&fighter3);
drawEnemyTwo(&grunt1);
drawEnemyTwo(&grunt2);
drawEnemyTwo(&grunt3);
drawEnemyThree(&shield1);
drawEnemyThree(&shield2);
drawEnemyThree(&shield3);

drawEnemyBullet(&eb1);
drawEnemyBullet(&eb2);
drawEnemyBullet(&eb3);

/*
Debug
* /
gotoxy(3,2);
printf("%d",counter.time);
gotoxy(3,3);
printf("%d %d %d %d %d",b1.drawBullet,b2.drawBullet,b3.drawBullet,b4.drawBullet,b5.drawBullet);
gotoxy(3,4);
printf("%d %d",sb1.drawBullet,sb2.drawBullet);
gotoxy(3,5);
printf("Difficulty: %d",difficulty);
gotoxy(3,6);
printf("Enemy bullets: %d %d %d",eb1.drawBullet,eb2.drawBullet,eb3.drawBullet);
gotoxy(3,6);
printf("Life: %d",3 - playerHits);
*/
    
/*
Wait for next tick
*/

while (time > counter.time - (1 << FIX14_SHIFT));
}

gameOver();

}
gotoxy(1,1);
printf("Thank you for playing!);
    
while(1){}
}
