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

clrscr();

setTimer();
initCounter(&counter);

struct enemy_t ball; // We make it global to be able to use timing
struct spaceship_t ship; // We initialize the spaceship as a global variable
struct spaceshipBullet_t bullet; // We initialize the spaceship bullet as a global variable

//uint32_t tid;
/*
while(1){
 //tid = counter.time;
 if (counter.time == 20){
    printf("G\n");
    counter.time=0;
 }
}
*/



//struct spaceship_t ship;
initSpaceship(&ship);
drawSpaceship(&ship);
initSpaceshipBullet(&bullet);

char temp;
int time;

while(1){

    time = counter.time;

    if (uart_get_count() >= 1){

        temp = uart_get_char();
       // updateSpaceshipPosition(&ship,temp);
       // updateSpaceshipBulletPosition(&bullet, &ship,temp);
        uart_clear();
    }

    drawSpaceship(&ship);

    while (time > counter.time - 10){}
    if (time == counter.time - 10){
        updateSpaceshipBulletPosition(&bullet, &ship, 1);
        updateSpaceshipPosition(&ship,1);


        drawSpaceshipBullet(&bullet);
    }
}
/*
    if (counter.time >= 1){
        drawSpaceship(&ship);
        updateSpaceshipPosition(&ship);

        if (counter.time == 10){
            updateSpaceshipBulletPosition(&bullet, &ship);
            drawSpaceshipBullet(&bullet);

            counter.time=0;
        }
    }
    */
/*
    if (counter.time == 10){
        updateSpaceshipBulletPosition(&bullet, &ship);
        drawSpaceshipBullet(&bullet);

        counter.time=0;
    }


}
*/


//drawSpaceship(&ship);

/*
while(1){
    drawSpaceship(&ship);
    updateSpaceshipPosition(&ship);

    drawSpaceshipBullet(&bullet);
    if (bullet.timeAtPosition>200){
        updateSpaceshipBulletPosition(&bullet);
        drawSpaceshipBullet(&bullet);
    }


}
*/
/*
initEnemy(&ball);
drawEnemy(&ball);

while(1){
    drawEnemy(&ball);
    if (ball.timeAtPosition>200){
        updateEnemyPosition(&ball);
        drawEnemy(&ball);
    }
}
*/

while(1){}
}
