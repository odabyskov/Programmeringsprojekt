#include "stm32f30x_conf.h" // STM32 config
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "ansi.h"
#include "timing.h"
#include "objects.h"
#include "calc.h"

// set flags
char temp; // input flags
int time = 0, hits = 0, iter = 0; // time flag, damage flag and game state flag

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
setTimer();
initCounter(&counter);

// Initialize the Player
struct spaceship_t ship;
struct spaceshipBullet_t bullet;
struct spaceshipBullet_t enemyBullet1;
struct spaceshipBullet_t enemyBullet2;
struct spaceshipBullet_t enemyBullet3;

initSpaceship(&ship);
drawSpaceship(&ship);
initSpaceshipBullet(&bullet);
initSpaceshipBullet(&enemyBullet1);
initSpaceshipBullet(&enemyBullet2);
initSpaceshipBullet(&enemyBullet3);

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
    updateSpaceshipBulletPosition(&bullet, &ship, temp);
    updateEnemyBulletPosition(&enemyBullet,&fighter);
}
if (iter == 6){
    updateEnemy1Position(&fighter);
    updateEnemy2Position(&grunt);
    updateEnemy3Position(&shieldbearer);
}


/*
Drawing
*/
drawSpaceship(&ship);
drawSpaceshipBullet(&bullet);
drawEnemyBullet(&enemyBullet);
drawEnemy1(&fighter);
drawEnemy2(&grunt);
drawEnemy3(&shieldbearer);

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
