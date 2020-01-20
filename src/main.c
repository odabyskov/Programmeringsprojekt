#include "stm32f30x_conf.h" // STM32 config
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "ansi.h"
#include "timing.h"
#include "objects.h"
#include "calc.h"
#include "sinLUT.h"
#include "led.h"

// set flags
char temp; // input flags
int time = 0, hits = 0, difficulty, playerHits; // time flag, damage flag and game state flag
uint32_t velBullet, velEnemy; // Velocity of the bullets/enemies (determined by shifting 1 tis number of places to the left)
uint32_t enemyOneKilled=0; // Kill-rate of enemy 1
uint32_t enemyTwoKilled=0; // Kill-rate of enemy 2
uint32_t enemyThreeKilled=0; // Kill-rate of enemy 3

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
struct enemy_t heart; // Power-up


int main(void)
{
    //uart_init( 9600 );
    uart_init(115200);

    difficulty=2;

    while(difficulty != 0){ // exit when quit is pressed
    
            // Main menu
            clrscr();
            gotoxy(1,1);
            printf("w/s to choose between menubars.\n");
            printf("spacebar to select the highlighted menubar.");
            difficulty = mainmenu();
            clrscr();
            playerHits = 0;
        
      
    while( difficulty != 0 && playerHits < 3 ){ // when game is over, return
    /*
    Game Start
    */

        /*
        Initialize the game
        */
        drawGameWindow(0);
        setTimer();
        initCounter(&counter);
        velBullet = 10 + difficulty; // Velocity of the bullets (determined by shifting 1 tis number of places to the left)
        velEnemy = 9 + difficulty; // Velocity of the enemies (determined by shifting 1 tis number of places to the left)

        
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
        initEnemy(&fighter1); // enemy 1
        initEnemy(&fighter2);
        initEnemy(&fighter3);
        initEnemy(&grunt1); // enemy 2
        initEnemy(&grunt2);
        initEnemy(&grunt3);
        initEnemy(&shield1); // enemy 3
        initEnemy(&shield2);
        initEnemy(&shield3);
        initEnemy(&heart); // Power-up

        // Initialize LED
        initializeLED();
        
    while(playerHits<3 && difficulty !=0){ // while not dead


        //Input
        time = counter.time << FIX14_SHIFT;

        temp = uart_get_char(); // get player input a = 97, d = 100, space = 32
        uart_clear();


        //Spawn enemies in intervals
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

        // Check for boss-key
        bossKey(temp);

        // Calculation
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

        if (temp == 'a' || temp == 'A' || temp == 'd' || temp == 'D' )
            updateSpaceshipPosition(&ship, temp);

        updateSpaceshipBulletPosition(&b1, &ship, 0, velBullet);
        updateSpaceshipBulletPosition(&b2, &ship, 0, velBullet);
        updateSpaceshipBulletPosition(&b3, &ship, 0, velBullet);
        updateSpaceshipBulletPosition(&b4, &ship, 0, velBullet);
        updateSpaceshipBulletPosition(&b5, &ship, 0, velBullet);
        updateSpaceshipShieldBulletPosition(&sb1, &ship, 0, velBullet);
        updateSpaceshipShieldBulletPosition(&sb2, &ship, 0, velBullet);

        updateEnemyBulletPosition(&eb1,&fighter1,velBullet);
        updateEnemyBulletPosition(&eb2,&fighter2,velBullet);
        updateEnemyBulletPosition(&eb3,&fighter3,velBullet);

        updateEnemyPosition(&fighter1, velEnemy);
        updateEnemyPosition(&fighter2, velEnemy);
        updateEnemyPosition(&fighter3, velEnemy);
        updateEnemyPosition(&grunt1, velEnemy);
        updateEnemyPosition(&grunt2, velEnemy);
        updateEnemyPosition(&grunt3, velEnemy);
        updateEnemyPosition(&shield1, velEnemy);
        updateEnemyPosition(&shield2, velEnemy);
        updateEnemyPosition(&shield3, velEnemy);

        updateHeartPosition(&heart, velEnemy, playerHits);

        // Kill-rates
        enemyOneKilled += isEnemyOneHit(&fighter1,&b1,&b2,&b3,&b4,&b5,&sb1,&sb2);
        enemyOneKilled += isEnemyOneHit(&fighter2,&b1,&b2,&b3,&b4,&b5,&sb1,&sb2);
        enemyOneKilled += isEnemyOneHit(&fighter3,&b1,&b2,&b3,&b4,&b5,&sb1,&sb2);
        enemyTwoKilled += isEnemyTwoHit(&grunt1,&b1,&b2,&b3,&b4,&b5,&sb1,&sb2);
        enemyTwoKilled += isEnemyTwoHit(&grunt2,&b1,&b2,&b3,&b4,&b5,&sb1,&sb2);
        enemyTwoKilled += isEnemyTwoHit(&grunt3,&b1,&b2,&b3,&b4,&b5,&sb1,&sb2);
        enemyThreeKilled += isEnemyThreeHit(&shield1,&b1,&b2,&b3,&b4,&b5,&sb1,&sb2);
        enemyThreeKilled += isEnemyThreeHit(&shield2,&b1,&b2,&b3,&b4,&b5,&sb1,&sb2);
        enemyThreeKilled += isEnemyThreeHit(&shield3,&b1,&b2,&b3,&b4,&b5,&sb1,&sb2);

        playerHits += isSpaceshipHit(&ship,&fighter1,&fighter2,&fighter3,&grunt1,&grunt2,&grunt3,&shield1,&shield2,&shield3,&eb1,&eb2,&eb3);
        playerHits -= isHeartHit(&heart,&b1,&b2,&b3,&b4,&b5,&sb1,&sb2);

        // Drawing
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

        drawHeart(&heart);

        drawEnemyBullet(&eb1);
        drawEnemyBullet(&eb2);
        drawEnemyBullet(&eb3);


        // Print kill-rates
        gotoxy(74,25);
        printf("%d", enemyOneKilled);
        gotoxy(74,30);
        printf("%d", enemyTwoKilled);
        gotoxy(74,36);
        printf("%d", enemyThreeKilled);

        getHealth(playerHits);
        setLED(playerHits);

        // Wait for next tick
        if ( time < 1000 << FIX14_SHIFT ){
            while ( time > ( (counter.time - (6 >> 1) ) << FIX14_SHIFT) );
        } else if ( time < 2000 << FIX14_SHIFT ) {
            while ( time > ( (counter.time - (5 >> 1) ) << FIX14_SHIFT) );
        } else if ( time < 3000 << FIX14_SHIFT ) {
            while ( time > ( (counter.time - (4 >> 1) ) << FIX14_SHIFT) );
        } else if ( time < 4000 << FIX14_SHIFT ) {
            while ( time > ( (counter.time - (3 >> 1) ) << FIX14_SHIFT) );
        } else if ( time < 5000 << FIX14_SHIFT ) {
            while ( time > ( (counter.time - (2 >> 1) ) << FIX14_SHIFT) );
        }

    }

        gameOver(enemyOneKilled,enemyTwoKilled,enemyThreeKilled);
        enemyOneKilled=0;
        enemyTwoKilled=0;
        enemyThreeKilled=0;
        difficulty=4; // return to main menu

    }
    }

    clrscr();
    gotoxy(1,1);
    printf("Thank you for playing!");

while(1){}
}
