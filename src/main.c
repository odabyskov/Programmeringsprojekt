#include "stm32f30x_conf.h" // STM32 config
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "ansi.h"
#include "timing.h"
#include "objects.h"
#include "calc.h"

// set flags
char temp; // input flags
int time, hits, iter, enemy1Killed; // time flag, damage flag and game state flag and kills

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
mainmenu();
clrscr();

while(1){ // while playing

/*
Initialize the game
*/
time = 0; // time flag
hits = 0; // damage flag
iter = 0; // game state flag
enemy1Killed = 0; // kill counter

setTimer();
initCounter(&counter);

// Initialize the Player
struct spaceship_t ship;
struct spaceshipBullet_t bullet1;
struct spaceshipBullet_t bullet2;
struct spaceshipBullet_t bullet3;
struct spaceshipBullet_t bullet4;
struct spaceshipBullet_t bullet5;
struct spaceshipShieldBullet_t sbullet1;
struct spaceshipShieldBullet_t sbullet2;

initSpaceship(&ship);
drawSpaceship(&ship);
initSpaceshipBullet(&bullet1);
initSpaceshipBullet(&bullet2);
initSpaceshipBullet(&bullet3);
initSpaceshipBullet(&bullet4);
initSpaceshipBullet(&bullet5);
initSpaceshipShieldBullet(&sbullet1);
initSpaceshipShieldBullet(&sbullet2);

// Initialize the Enemy
struct enemy1_t fighter1;
struct enemy1_t fighter2;
struct enemy1_t fighter3;
struct enemy2_t grunt1;
struct enemy2_t grunt2;
struct enemy2_t grunt3;
struct enemy3_t shield1;
struct enemy3_t shield2;
struct enemy3_t shield3;

struct spaceshipBullet_t enemyBullet1;
struct spaceshipBullet_t enemyBullet2;
struct spaceshipBullet_t enemyBullet3;

initSpaceshipBullet(&enemyBullet1);
initSpaceshipBullet(&enemyBullet2);
initSpaceshipBullet(&enemyBullet3);

initEnemy1(&fighter1);
initEnemy1(&fighter2);
initEnemy1(&fighter3);
initEnemy2(&grunt1);
initEnemy2(&grunt2);
initEnemy2(&grunt3);
initEnemy3(&shield1);
initEnemy3(&shield2);
initEnemy3(&shield3);

/*
Game Start
*/
while(1){ // while not dead

/*
Input
*/
if (iter == 6){ //reset the micro game state
    iter = 0;
    time = counter.time;
}
temp = uart_get_char(); // get player input a = 97, d = 100, space = 32
uart_clear();

iter++;
/*
Spawn enemies in intervals
*/
if ( counter.time % 900 > 0 && counter.time % 900 < 12 )
    grunt1.drawEnemy2 = 1;
else if ( counter.time % 900 > 100 && counter.time % 900 < 112 )
    grunt2.drawEnemy2 = 1;
else if ( counter.time % 900 > 200 && counter.time % 900 < 212 ){
    fighter1.drawEnemy1 = 1;
    //enemyBullet1.drawBullet = 1;
    }
else if ( counter.time % 900 > 300 && counter.time % 900 < 312 )
    shield1.drawEnemy3 = 1;
else if ( counter.time % 900 > 400 && counter.time % 900 < 412 )
    grunt3.drawEnemy2 = 1;
else if ( counter.time % 900 > 500 && counter.time % 900 < 512 )
    shield2.drawEnemy3 = 1;
else if ( counter.time % 900 > 600 && counter.time % 900 < 612 ){
    fighter2.drawEnemy1 = 1;
    //enemyBullet2.drawBullet = 1;
    }
else if ( counter.time % 900 > 700 && counter.time % 900 < 712 ){
    fighter3.drawEnemy1 = 1;
    //enemyBullet3.drawBullet = 1;
    }
else if ( counter.time % 900 > 800 && counter.time % 900 < 812 )
    shield3.drawEnemy3 = 1;

/*
Boss key screen
*/
if (temp == 'b'){
clrscr();
printf("Microsoft [Version 10.0.18362.535]");
printf("(c) 2019 Microsoft Corporation. Alle rettigheder forbeholdes");
printf(" ");
printf(" ");
printf("C:/Users/LookBusy>");
clrscr();
while(uart_get_count() < 1){}
}

/*
Calculation
*/
if (temp == 97 || temp == 100 )
    updateSpaceshipPosition(&ship, temp);

if (iter == 2 || iter == 4 || iter == 6){
    updateSpaceshipBulletPosition(&bullet1, &ship, 1);
    updateSpaceshipBulletPosition(&bullet2, &ship, 1);
    updateSpaceshipBulletPosition(&bullet3, &ship, 1);
    updateSpaceshipBulletPosition(&bullet4, &ship, 1);
    updateSpaceshipBulletPosition(&bullet5, &ship, 1);

    updateSpaceshipShieldBulletPosition(&sbullet1, &ship, 1);
    updateSpaceshipShieldBulletPosition(&sbullet2, &ship, 1);

    updateEnemyBulletPosition(&enemyBullet1,&fighter1);
    updateEnemyBulletPosition(&enemyBullet2,&fighter2);
    updateEnemyBulletPosition(&enemyBullet3,&fighter3);
}
if (iter == 6){
    updateEnemy1Position(&fighter1);
    updateEnemy1Position(&fighter2);
    updateEnemy1Position(&fighter3);
    updateEnemy2Position(&grunt1);
    updateEnemy2Position(&grunt2);
    updateEnemy2Position(&grunt3);
    updateEnemy3Position(&shield1);
    updateEnemy3Position(&shield2);
    updateEnemy3Position(&shield3);
}


/*
Drawing
*/
drawSpaceship(&ship);
drawSpaceshipBullet(&bullet1);
drawSpaceshipBullet(&bullet2);
drawSpaceshipBullet(&bullet3);
drawSpaceshipBullet(&bullet4);
drawSpaceshipBullet(&bullet5);
drawSpaceshipShieldBullet(&sbullet1);
drawSpaceshipShieldBullet(&sbullet2);

drawEnemy1(&fighter1);
drawEnemy1(&fighter2);
drawEnemy1(&fighter3);
drawEnemy2(&grunt1);
drawEnemy2(&grunt2);
drawEnemy2(&grunt3);
drawEnemy3(&shield1);
drawEnemy3(&shield2);
drawEnemy3(&shield3);

drawEnemyBullet(&enemyBullet1);
drawEnemyBullet(&enemyBullet2);
drawEnemyBullet(&enemyBullet3);

/*
Wait for next tick
*/
if (iter == 1)
while (time > counter.time - 2){}
if (iter == 2)
while (time > counter.time - 4){}
if (iter == 3)
while (time > counter.time - 6){}
if (iter == 4)
while (time > counter.time - 8){}
if (iter == 5)
while (time > counter.time - 10){}
if (iter == 5)
while (time > counter.time - 12){}

}

//Game Over should be here

}

while(1){}
}
