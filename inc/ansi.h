#include <stdio.h>
#include "stm32f30x_conf.h"

#ifndef _ANSI_H_
#define _ANSI_H_

#include "calc.h"
#include "timing.h"
#include "objects.h"

// General ansi-functions
void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void resetbgcolor();
void clrscr();
void clreol();
void gotoxy(uint8_t x, uint8_t y);
void deleteSymbol(uint8_t x, uint8_t y);
void drawBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void drawWindow(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char* string_p, uint8_t style);


// Functions to draw the main menu
uint8_t mainmenu();
void drawTitle(uint8_t type);
void drawmenuStart();
void drawmenuHelp();
void drawmenuCredits();
void drawmenuQuit();
void getHelp();
void getCredits();
uint8_t getDifficulty();
void drawmenuEasy();
void drawmenuNormal();
void drawmenuHard();
void drawmenuMainMenu();

// Functions to draw objects on Putty
void drawSpaceship(struct spaceship_t *spaceship);
void drawSpaceshipBullet(struct bullet_t *bullet);
void drawSpaceshipShieldBullet(struct bullet_t *bullet);
void drawEnemyBullet(struct bullet_t *bullet);
void drawEnemyOne(struct enemy_t *enemy);
void drawEnemyTwo(struct enemy_t *enemy);
void drawEnemyThree(struct enemy_t *enemy);
void drawHeart(struct enemy_t *heart);

// Functions to draw game screens
void gameOver(uint32_t enemyOneKilled, uint32_t enemyTwoKilled, uint32_t enemyThreeKilled);
void drawGameWindow(int8_t playerHits);
void getHealth(int8_t hits);
void bossKey(char temp);
void thankYou();


#endif
