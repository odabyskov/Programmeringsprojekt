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

// Functions to draw objects on Putty
void drawSpaceship(struct spaceship_t *spaceship);
void drawSpaceshipBullet(struct bullet_t *bullet);
void drawSpaceshipShieldBullet(struct bullet_t *bullet);
void drawEnemyBullet(struct bullet_t *bullet);
void drawEnemyOne(struct enemy_t *enemy);
void drawEnemyTwo(struct enemy_t *enemy);
void drawEnemyThree(struct enemy_t *enemy);

uint8_t mainmenu(); // enter the main menu
void drawTitle(uint8_t type); // draw title
void drawmenuStart(); // update start menu when selected
void drawmenuHelp(); //  update help menu when selected
void drawmenuCredits(); // update credit menu when selected
void drawmenuQuit(); // update quit menu when selected
void getHelp(); //enter the help menu
void getCredits(); //enter the credits menu
uint8_t getDifficulty(); // Enter the difficulty menu
void drawmenuEasy(); // Draw the Easy box
void drawmenuNormal(); // Draw the Normal box
void drawmenuHard(); // Draw the Hard box
void drawmenuMainMenu(); // Draw the main menu box
void gameOver(); //Draw the game over screen
void drawGameWindow(int8_t playerHits);
void getHealth(int8_t hits);
#endif
