#include "stm32f30x_conf.h" // STM32 config
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "ansi.h"
#include "timing.h"
#include "objects.h"
#include "calc.h"

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

/*
Initialize the game
*/
setTimer();
initCounter(&counter);

// Player
struct spaceship_t ship;
struct spaceshipBullet_t bullet;
struct enemyBullet_t enemyBullet;

initSpaceship(&ship);
drawSpaceship(&ship);
initSpaceshipBullet(&bullet);
initEnemyBullet(&enemyBullet);

// Enemy
struct enemy1_t fighter;
struct enemy2_t grunt;
struct enemy3_t shieldbearer;

initEnemy1(&fighter);
initEnemy2(&grunt);
initEnemy3(&shieldbearer);

// set flags
char temp; // input flags
int time = 0, hits = 0, iter = 0; // time flag, damage flag and game state flag

while(1){

/*
Input
*/
if (iter == 6){
    iter = 0;
    time = counter.time;
}
temp = uart_get_char(); //a = 97, d = 100, space = 32
uart_clear();

iter++;
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
gotoxy(2,2);
printf("%d",enemyBullet.drawBullet);
gotoxy(2,3);
printf("%d",enemyBullet.posY >> 14);
gotoxy(2,4);
printf("%d",enemyBullet.posY >> 14);
gotoxy(2,5);
printf("%d",bullet.posY) >> 14;

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

while(1){}
}
