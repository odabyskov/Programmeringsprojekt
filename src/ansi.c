#define ESC 0x1B
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "ansi.h"


/*
*
*
*
* The following functions are general functions used to draw on the Putty
*
*
*
*/


/*
This function clears the screen and homes the cursor
*/
void clrscr(){
    printf("%c[2J", ESC);
    gotoxy(1,1);
    printf("%c[?25l",ESC); // hide cursor
}

/*
This function clears the rest of the line
*/
void clreol(){
    printf("%c[K", ESC);
}

/*
This function changes the coordinates of the cursor
*/
void gotoxy(uint8_t x, uint8_t y){
    uint8_t r=y;
    uint8_t c=x;
    printf("%c[%d;%dH", ESC, r, c);
}

/*
This function deletes the symbol at position (x,y)
*/
void deleteSymbol(uint8_t x, uint8_t y){
    gotoxy(x,y);
    printf(" ");
}

/*
This function draws a box with upper left corner in (x1,y1) and lower right corner in (x2,y2)
*/
void drawBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){

    uint8_t i;

    // This part draws the corners
    gotoxy(x1,y1);
    printf("%c\n",201);
    gotoxy(x2,y1);
    printf("%c", 187);
    gotoxy(x1,y2);
    printf("%c", 200);
    gotoxy(x2,y2);
    printf("%c", 188);


    // This part draws the vertical sides of the box
    for (i=y1+1; i<y2; i++){
        gotoxy(x1, i);
        printf("%c", 186);
        gotoxy(x2, i);
        printf("%c", 186);
    }

    // This part draws the horizontal sides of the box
    for (i=x1+1; i<x2; i++){
        gotoxy(i, y1);
        printf("%c", 205);
        gotoxy(i, y2);
        printf("%c", 205);
    }
}

/*
This function draws a window with upper left corner in (x1,y1) and lower right corner in (x2,y2).
The char input is the title, which will be drawn in the top of the box.
The style defines the sides of the box - if style is set to 0 the sides are drawn with double line,
if it's set different from 0 the sides are drawn with a single line.
*/
void drawWindow(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char* string_p, uint8_t style){

    uint8_t stringLength=0;
    uint8_t counter=0; // We use a counter to avoid changing the address of the pointer

    // This part calculates the length of the string
    for (string_p; *(string_p+counter) != '\0'; counter++){
    stringLength++;
    }

    // This part checks if the string is too long to fit the box
    if (stringLength <= x2-4){

    // This part decides the style
    if (style==0){

        // This part draws the corners
        gotoxy(x1,y1);
        printf("%c\n",201);
        gotoxy(x2,y1);
        printf("%c", 187);
        gotoxy(x1,y2);
        printf("%c", 200);
        gotoxy(x2,y2);
        printf("%c", 188);

        // This part draws the vertical sides of the box
        uint8_t i;
        for (i=y1+1; i<y2; i++){
            gotoxy(x1, i);
            printf("%c", 186);
            gotoxy(x2, i);
            printf("%c", 186);
        }

        // This part draws the lower horizontal part of the box
        for (i=x1+1; i<x2; i++){
            gotoxy(i, y2);
            printf("%c", 205);
        }

        // This part determines the length of the extra space to the right of the title
        uint8_t ekstraTegn = x2-x1-4-stringLength;

        // Vi tegner toppen af boksen

        // This part draws the leftmost part of the top of the box
        uint8_t vertical1 = x1+1;
        gotoxy(vertical1,y1);
        printf("%c", 185);

        // This part prints the title
        uint8_t vertical2 = vertical1+1;
        gotoxy(vertical2,y1);
        for (i=0; i<stringLength; i++){
         printf("%c", *string_p);
         string_p++;
        }

        // This part draws the rigthmost part of the top of the box
        uint8_t vertical3 = vertical2+stringLength;
        gotoxy(vertical3,y1);
        printf("%c", 204);

        uint8_t vertical4 = vertical3+1;
        gotoxy(vertical4,y1);
        for (i=0; i<ekstraTegn;i++){
            printf("%c", 205);
        }
    } else {

        // This part of the code does the same as the code we just described but with a different style

        gotoxy(x1,y1);
        printf("%c\n",218);
        gotoxy(x2,y1);
        printf("%c", 191);
        gotoxy(x1,y2);
        printf("%c", 192);
        gotoxy(x2,y2);
        printf("%c", 217);

        // Sides
        uint8_t i;
        for (i=y1+1; i<y2; i++){
            gotoxy(x1, i);
            printf("%c", 179);
            gotoxy(x2, i);
            printf("%c", 179);
        }

        // Lower horizontal part
        for (i=x1+1; i<x2; i++){
            gotoxy(i, y2);
            printf("%c", 196);
        }

        // Extra space to the left of the title
        uint8_t ekstraTegn = x2-x1-4-stringLength;

        // Leftmost part of top
        uint8_t vertical1 = x1+1;
        gotoxy(vertical1,y1);
        printf("%c", 180);

        // Title
        uint8_t vertical2 = vertical1+1;
        gotoxy(vertical2,y1);
        for (i=0; i<stringLength; i++){
         printf("%c", *string_p);
         string_p++;
        }

        // Rightmost part of top
        uint8_t vertical3 = vertical2+stringLength;
        gotoxy(vertical3,y1);
        printf("%c", 195);

        uint8_t vertical4 = vertical3+1;
        gotoxy(vertical4,y1);
        for (i=0; i<ekstraTegn;i++){
            printf("%c", 196);
        }
    }
    } else {
        printf("The title is too long!");
    }

}


/*
*
*
*
* The following functions are used to draw the objects in the Putty
*
*
*
*/

/*
This function draws the enemy
*/
void drawEnemy(struct enemy_t *enemy){

    gotoxy((*enemy).posX,(*enemy).posY);
    printf("o");

}

/*
This function draws the player's spaceship
*/
void drawSpaceship(struct spaceship_t *spaceship){


    // We define x- and y-components to use in the gotoxy-function
    uint8_t newX;
    uint8_t newY;

    gotoxy((*spaceship).posX,(*spaceship).posY);
    printf("%c", 186);
    newY = (*spaceship).posY - 1;
    gotoxy((*spaceship).posX,newY);
    printf("%c", 167);
    newX = (*spaceship).posX - 1;
    gotoxy(newX,(*spaceship).posY);
    printf("%c", 205);
    newX = (*spaceship).posX - 2;
    gotoxy(newX,(*spaceship).posY);
    printf("%c", 173);
    newX = (*spaceship).posX + 1;
    gotoxy(newX,(*spaceship).posY);
    printf("%c", 205);
    newX = (*spaceship).posX + 2;
    gotoxy(newX,(*spaceship).posY);
    printf("%c", 173);

}

/*
This function draws the bullet fired from the spaceship
*/
void drawSpaceshipBullet(struct spaceshipBullet_t *bullet){

    if ((*bullet).posY < 2){
            (*bullet).drawBullet = 0;
    }

    if ((*bullet).drawBullet >= 1){
        gotoxy((*bullet).posX,(*bullet).posY);
        //printf("%c", 004); // draws a bullet shaped like a diamond
        printf("o"); // draws a bullet shaped like a diamond
    }
}


