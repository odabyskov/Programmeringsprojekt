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

//struct spaceship_t ship;
initSpaceship(&ship);
drawSpaceship(&ship);
initSpaceshipBullet(&bullet);

char temp;

while(1){

    //mainmenu();
    time = counter.time;

    if (uart_get_count() >= 1){

        temp = uart_get_char();
        updateSpaceshipPosition(&ship, temp);
        if (bullet.drawBullet == 0 ){
        updateSpaceshipBulletPosition(&bullet, &ship, temp);
        }
        uart_clear();
    }

    drawSpaceship(&ship);
    drawSpaceshipBullet(&bullet);

    while (time > counter.time - 10){}
    if (time == counter.time - 10){
        updateSpaceshipBulletPosition(&bullet, &ship, 1);
        updateSpaceshipPosition(&ship, 1);

        drawSpaceshipBullet(&bullet);


    }
}

while(1){}
}
