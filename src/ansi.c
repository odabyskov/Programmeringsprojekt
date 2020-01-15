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
This function draws a window, but without a title
*/
void drawbox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
    /*
    Draw the corners
    */
    gotoxy(x1,y1);
    printf("%c\n",201);
    gotoxy(x2,y1);
    printf("%c", 187);
    gotoxy(x1,y2);
    printf("%c", 200);
    gotoxy(x2,y2);
    printf("%c", 188);
    
    /*
    Draw the sides
    */
    uint8_t i;
    for (i=y1+1; i<y2; i++){
        gotoxy(x1, i);
        printf("%c", 186);
        gotoxy(x2, i);
        printf("%c", 186);
    }
    /*
    Draw the top & bottom
    */
    for (i=x1+1; i<x2; i++){
        gotoxy(i, y1);
        printf("%c", 205);
        gotoxy(i, y2);
        printf("%c", 205);
    }
}

/*
Draw and enter the main menu
*/
void mainmenu(){
clrscr();
uart_clear();
uint8_t menu = 1, input = 0;

/*
Initialize the menu (start game is chosen as default)
*/
drawTitle(1);

fgcolor(2);
drawbox(30,17,50,21);
gotoxy(35,19);
fgcolor(15);
printf("Start Game");

drawbox(30,22,50,26);
gotoxy(38,24);
printf("help");
drawbox(30,27,50,31);
gotoxy(36,29);
printf("credits");
drawbox(30,32,50,36);
gotoxy(38,34);
printf("Quit");

while(input != 32){
/*
press s to choose the help menu, press enter to activate start game.
*/
while(input != 115 & input != 32 & menu == 1){
    input = uart_get_char();
    if (input == 115)
        menu++;
    if (input == 32)
        break;
    }

if (menu == 2 & input != 32){
drawmenuHelp();
}

/*
Press w to choose start game, press s to choose credits, press enter to activate help
*/
while (input != 115 & input != 119 & input != 32 & menu == 2){
    input = uart_get_char();
    if (input == 115)
        menu++;
    if (input == 119)
        menu--;
    if (input == 32)
        break;
}

switch (menu) {
    case 1: {
        if (input == 32)
            break;
        if (input =! 32){
            input = 0;
            uart_clear();
            }
        drawmenuStart();
        break;
    }

    case 3: {
        if (input == 32)
            break;
        drawmenuCredits();
        input = 0;
        uart_clear();
        break;
    }
}

/*
Press w to go back to help, press s to go down to Quit game
*/
while (input != 115 & input != 119 & input != 32 & menu == 3){
    input = uart_get_char();
    if (input == 115)
        menu++;
    if (input == 119)
        menu--;
    if (input == 32)
        break;
}

switch (menu) {
    case 2: {
        if (input == 32)
            break;
        drawmenuHelp();
        input=0;
        uart_clear();
        break;
    }
    case 4: {
        if (input == 32)
            break;
        drawmenuQuit();
        input = 0;
        uart_clear();
        break;
    }
}

/*
Press w to go back to credits
*/
while (input != 119 & input != 32 & menu == 4){
input = uart_get_char();
    if (input == 119)
        menu--;
    if (input == 32)
    break;
}

if (menu == 3 & input != 32){
    drawmenuCredits();
    if (input =! 32){
    input = 0;
    uart_clear();
    }
}

/*
end of while loop
*/
}

/*
If Enter is pressed leave the while loop & activate the chosen menu
*/
if (input == 32 & menu == 1){
    getDifficulty();}
else if (input == 32 & menu == 2){
    getHelp();}
else if (input == 32 & menu == 3){
    getCredits();}
else if (input == 32 & menu == 4){
    clrscr();
    exit(0);}

}
/*
draw title
*/
void drawTitle(uint8_t type){
color(15, 0);
if (type == 1){
    gotoxy(28,4);
    printf(" %c%c%c %c%c%c   %c%c   %c%c  %c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(28,5);
    printf("%c    %c  %c %c  %c %c  %c %c   ",219,219,219,219,219,219,219,219);
    gotoxy(28,6);
    printf(" %c%c  %c%c%c  %c%c%c%c %c    %c%c%c ",219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(28,7);
    printf("   %c %c    %c  %c %c  %c %c   ",219,219,219,219,219,219,219);
    gotoxy(28,8);
    printf("%c%c%c  %c    %c  %c  %c%c  %c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219);

    gotoxy(23,10);
    printf("%c   %c  %c%c  %c%c%c  %c%c%c  %c%c%c  %c%c  %c%c%c ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,11);
    printf("%c   %c %c  %c %c  %c %c  %c  %c  %c  %c %c  %c",219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,12);
    printf("%c %c %c %c%c%c%c %c%c%c  %c%c%c   %c  %c  %c %c%c%c ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,13);
    printf("%c %c %c %c  %c %c  %c %c  %c  %c  %c  %c %c  %c",219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,14);
    printf(" %c %c  %c  %c %c  %c %c  %c %c%c%c  %c%c  %c  %c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);}
if (type == 2){
    gotoxy(26,4);
    printf(" %c%c  %c  %c  %c%c   %c%c   %c%c%c %c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(26,5);
    printf("%c  %c %c  %c %c  %c %c  %c %c    %c   ",219,219,219,219,219,219,219,219,219,219);
    gotoxy(26,6);
    printf("%c    %c%c%c%c %c  %c %c  %c  %c%c  %c%c%c ",219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(26,7);
    printf("%c  %c %c  %c %c  %c %c  %c    %c %c   ",219,219,219,219,219,219,219,219,219,219);
    gotoxy(26,8);
    printf(" %c%c  %c  %c  %c%c   %c%c  %c%c%c  %c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);

    gotoxy(16,10);
    printf("%c%c%c  %c%c%c %c%c%c%c %c%c%c%c %c%c%c  %c%c  %c  %c %c   %c%c%c%c%c %c   %c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(16,11);
    printf("%c  %c  %c  %c    %c     %c  %c  %c %c  %c %c     %c    %c %c ",219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(16,12);
    printf("%c  %c  %c  %c%c%c  %c%c%c   %c  %c    %c  %c %c     %c     %c  ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(16,13);
    printf("%c  %c  %c  %c    %c     %c  %c  %c %c  %c %c     %c     %c  ",219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(16,14);
    printf("%c%c%c  %c%c%c %c    %c    %c%c%c  %c%c   %c%c  %c%c%c%c  %c     %c  ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
}
resetbgcolor();

}
/*
Update start game box when selected
*/
void drawmenuStart(){
        drawbox(30,22,50,26);

        fgcolor(2);
        drawbox(30,17,50,21);
        fgcolor(15);
}
/*
update help box when selected
*/
void drawmenuHelp(){
        drawbox(30,17,50,21);
        drawbox(30,27,50,31);

        fgcolor(2);
        drawbox(30,22,50,26);
        fgcolor(15);
}
/*
update credit box when selected
*/
void drawmenuCredits(){
        drawbox(30,22,50,26);
        drawbox(30,32,50,36);

        fgcolor(2);
        drawbox(30,27,50,31);
        fgcolor(15);
}
/*
Update quit box when selected
*/
void drawmenuQuit(){
        drawbox(30,27,50,31);

        fgcolor(2);
        drawbox(30,32,50,36);
        fgcolor(15);
}
/*
Enter the help menu
*/
void getHelp(){
clrscr();
uart_clear();
uint8_t input = 0;

drawWindow(22, 8, 57, 32, " HELP ME! ", 1);

gotoxy(28,12);
printf("Hvis du ikke kan finde");
gotoxy(28,13);
printf("ud af vores spil,");
gotoxy(28,16);
printf("så kan vi godt forstå det.");
gotoxy(28,20);
printf("Det er nemlig ikke færdigt endnu.");
gotoxy(28,24);
printf("noget");

fgcolor(2);
drawbox(30,34,50,38);
fgcolor(15);
gotoxy(36,36);
printf("Back");

//while(input =! 32){
while(input != 32){
    input = uart_get_char();
}
mainmenu();
}
/*
Enter the credits menu
*/
void getCredits(){
clrscr();
uart_clear();
uint8_t input = 0;

drawWindow(22, 8, 57, 32, " Credits ", 1);

//bgcolor(1);
gotoxy(36,15);
printf("Oda");
//resetbgcolor();

//bgcolor(2);
gotoxy(36,19);
printf("Patrick");
//resetbgcolor();

//bgcolor(3);
gotoxy(36,23);
printf("Marc");
//resetbgcolor();

fgcolor(2);
drawbox(30,34,50,38);
gotoxy(34,36);
fgcolor(15);
printf("Back");

while(input != 32){
    input = uart_get_char();
}
mainmenu();
}
/*
Enter the difficulty menu
*/
void getDifficulty(){
clrscr();
uart_clear();
uint8_t menu = 2, input = 0;
/*
Initialize the menu (Normal is chosen as default)
*/
drawTitle(2);

drawbox(30,17,50,21);
gotoxy(38,19);
printf("Easy");

fgcolor(2);
drawbox(30,22,50,26);
gotoxy(37,24);
fgcolor(15);
printf("Normal");

drawbox(30,27,50,31);
gotoxy(38,29);
printf("Hard");
drawbox(30,32,50,36);
gotoxy(35,34);
printf("Main Menu");

while(input != 32){
/*
press s to go back to normal, press enter to activate easy difficulty.
*/
while(input != 115 & input != 32 & menu == 1){
    input = uart_get_char();
    if (input == 115)
        menu++;
    if (input == 32)
        break;
}

if (menu == 2 & input != 32){
drawmenuNormal();
}
/*
Press w to choose the easy, press s to choose hard, press enter to activate normal difficulty
*/
while (input != 115 & input != 119 & input != 32 & menu == 2){
    input = uart_get_char();
    if (input == 115)
        menu++;
    if (input == 119)
        menu--;
    if (input == 32)
        break;
}

switch (menu) {
    case 1: {
        if (input == 32)
            break;
        if (input =! 32){
            input = 0;
            uart_clear();
        }
        drawmenuEasy();
        break;
    }

    case 3: {
        if (input == 32)
            break;
        drawmenuHard();
        input = 0;
        uart_clear();
        break;
    }
}

/*
Press w to go back to Normal, press s to go down to Main Menu
*/
while (input != 115 & input != 119 & input != 32 & menu == 3){
    input = uart_get_char();
    if (input == 115)
        menu++;
    if (input == 119)
        menu--;
    if (input == 32)
        break;
}

switch (menu) {
    case 2: {
        if (input == 32)
            break;
        drawmenuNormal();
        input=0;
        uart_clear();
        break;
    }
    case 4: {
        if (input == 32)
            break;
        drawmenuMainMenu();
        input = 0;
        uart_clear();
        break;
    }
}

/*
Press w to go back to Hard, press enter to go back to main menu.
*/
while (input != 119 & input != 32 & menu == 4){
input = uart_get_char();
    if (input == 119)
        menu--;
    if (input == 32)
    break;
}

if (menu == 3 & input != 32){
    drawmenuHard();
    input = 0;
    uart_clear();
}

}
if (menu == 1 & input == 32)
    printf("Easy Mode");
else if (menu == 2 & input == 32)
    printf("Normal Mode");
else if (menu == 3 & input == 32)
    printf("Hard Mode");
else if (menu == 4 & input == 32)
    mainmenu();
}
/*
Draw the Easy box
*/
void drawmenuEasy(){
    drawbox(30,22,50,26);

    fgcolor(2);
    drawbox(30,17,50,21);
    fgcolor(15);
}
/*
Draw the Normal difficulty menubar
*/
void drawmenuNormal(){
    drawbox(30,17,50,21);
    drawbox(30,27,50,31);

    fgcolor(2);
    drawbox(30,22,50,26);
    fgcolor(15);
}
/*
Draw the Hard difficulty menubar
*/
void drawmenuHard(){
    drawbox(30,22,50,26);
    drawbox(30,32,50,36);

    fgcolor(2);
    drawbox(30,27,50,31);
    fgcolor(15);
}
/*
Draw the main menu menubar
*/
void drawmenuMainMenu(){
    drawbox(30,27,50,31);

    fgcolor(2);
    drawbox(30,32,50,36);
    fgcolor(15);
}
/*
Deletes the symbol on x y coordinates on the screen
*/

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


