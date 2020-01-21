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

void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.
    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

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
        for (i=0; i<ekstraTegn+1;i++){
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
* The following functions are used to draw the main menu
*
*
*
*/

/*
Draw and enter the main menu
*/
uint8_t mainmenu(){
    clrscr();
    uart_clear();
    uint8_t menu = 1, input = 0, returnvalue;

    /*
    Initialize the menu (start game is chosen as default)
    */
    while(input != 32 || menu == 2 || menu == 3 ){

	    if (menu == 1){
	        gotoxy(23,38);
    		printf("w/s = up/down  -  spacebar = select\n");
    		drawTitle(1);

    		fgcolor(2);
		drawBox(30,17,50,21);
	    	gotoxy(35,19);
    		fgcolor(15);
    		printf("Start Game");

    		drawBox(30,22,50,26);
    		gotoxy(38,24);
    		printf("Help");
    		drawBox(30,27,50,31);
   		gotoxy(36,29);
   		printf("Credits");
   		drawBox(30,32,50,36);
    		gotoxy(38,34);
    		printf("Quit");
	    }

    // press s to choose the help menu, press enter to activate start game.
    while(input != 115 && input != 32 && menu == 1){
        input = uart_get_char();
        if (input == 115)
            menu++;
        if (input == 32)
            break;
        }

    if (menu == 2 && input != 32){
    drawmenuHelp();
    }

    // Press w to choose start game, press s to choose credits, press enter to activate help
    while (input != 115 && input != 119 && input != 32 && menu == 2){
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
            if (input != 32){
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

    // Press w to go back to help, press s to go down to Quit game
    while (input != 115 && input != 119 && input != 32 && menu == 3){
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

    // Press w to go back to credits
    while (input != 119 && input != 32 && menu == 4){
    input = uart_get_char();
        if (input == 119)
            menu--;
        if (input == 32)
        break;
    }

    if (menu == 3 && input != 32){
        drawmenuCredits();
        if (input != 32){
        input = 0;
        uart_clear();
        }
    }
	if (input == 32 && menu == 2){
        	getHelp();
        	clrscr();
        	input = 0;
        	menu = 1;
    	}
    	else if (input == 32 && menu == 3){
        	getCredits();
        	clrscr();
        	input = 0;
        	menu = 1;
    	}

} // end of while loop

    // If Enter is pressed leave the while loop & activate the chosen menu
if (input == 32 && menu == 1){
        returnvalue = getDifficulty();}
    else if (input == 32 && menu == 4){
        returnvalue = 0;
    }
return returnvalue;
}

/*
This function draws the title
*/
void drawTitle(uint8_t type){
    fgcolor(15);
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
This function updates start game box when selected
*/
void drawmenuStart(){
    drawBox(30,22,50,26);

    fgcolor(2);
    drawBox(30,17,50,21);
    fgcolor(15);
}

/*
This function updates help box when selected
*/
void drawmenuHelp(){
        drawBox(30,17,50,21);
        drawBox(30,27,50,31);

        fgcolor(2);
        drawBox(30,22,50,26);
        fgcolor(15);
}

/*
This function updates credit box when selected
*/
void drawmenuCredits(){
    drawBox(30,22,50,26);
    drawBox(30,32,50,36);

    fgcolor(2);
    drawBox(30,27,50,31);
    fgcolor(15);
}

/*
Thus function updates quit box when selected
*/
void drawmenuQuit(){
    drawBox(30,27,50,31);

    fgcolor(2);
    drawBox(30,32,50,36);
    fgcolor(15);
}

/*
This function makes you enter the help menu
*/
void getHelp(){
    clrscr();
    uart_clear();
    uint8_t input = 0;


    //making the help window from our drawWindow function
    drawWindow(9, 3, 74, 38, " HELP! ", 1);

    //the meaning of the game
    gotoxy(15,5);
    printf("The object of this game is to shoot down the enemy");
    gotoxy(15,6);
    printf("battleships before they reach your planet.");

    gotoxy(15,8);
    printf("If you get shot or miss an enemy, you will loose");
    gotoxy(15,9);
    printf("one of your lives.");


    //how to move your ship
    gotoxy(15,11);
    printf("How to move your ship:");

    //Drawing our ship
    fgcolor(2);
    gotoxy(38,15);
    printf("%c",220);
    gotoxy(36,16);
    printf("%c%c%c%c%c",173,205,186,205,173);
    fgcolor(15);

    //how to go left
    gotoxy(15,16);
    printf("left press A <-");

    //how to go  right
    gotoxy(46,16);
    printf(" -> right press D");

    //how to shoot
    gotoxy(38,12);
    printf("o  <-  Space shoots normal bullets");

    gotoxy(38,14);
    fgcolor(1);
    printf("!");
    fgcolor(15);
    gotoxy(39,14);
    printf("  <-  w shoots special bullets");

    //what kind of enemies do we have:
    gotoxy(15,18);
    printf("Things you will meet in space:");

    //enemy 1:
    gotoxy(33, 20);
    printf("*Shoots normal bullets");
    gotoxy(34, 21);
    printf("Immune to special bullets");


    fgcolor(9);
    gotoxy(19, 20);
    printf("%c",219);
    gotoxy(18, 20);
    printf("%c",219);
    gotoxy(20, 20);
    printf("%c",219);
    gotoxy(19, 21);
    printf("%c",219);
    fgcolor(15);

    //enemy 2:
    gotoxy(33, 24);
    printf("*Deflects normal bullets away");
    gotoxy(34,25);
    printf("Immune to normal bullets");

    fgcolor(5);
    gotoxy(19, 24);
    printf("%c",219);
    gotoxy(18, 24);
    printf("%c",219);
    gotoxy(20, 24);
    printf("%c",219);
    gotoxy(19, 23);
    printf("%c",219);
    fgcolor(6);
    gotoxy(18, 25);
    printf("%c%c%c",192,196,217);
    fgcolor(15);

    //enemy 3:
    gotoxy(33, 27);
    printf("*Only moves");
    gotoxy(34, 28);
    printf("Immune to special bullets");

    fgcolor(8);
    gotoxy(19, 27);
    printf("%c",219);
    gotoxy(18, 27);
    printf("%c",219);
    gotoxy(20, 27);
    printf("%c",219);
    fgcolor(15);

    // Power-up
    gotoxy(33, 30);
    printf("*This power-up gives you an extra life");
    fgcolor(1);
    gotoxy(18, 29);
    printf("%c",40);
    gotoxy(19, 29);
    printf("%c",92);
    gotoxy(20, 29);
    printf("%c",47);
    gotoxy(21, 29);
    printf("%c",41);
    gotoxy(19, 30);
    printf("%c",92);
    gotoxy(20, 30);
    printf("%c",47);
    fgcolor(15);

    fgcolor(2);
    drawBox(31,33,49,37);
    fgcolor(15);
    gotoxy(38,35);
    printf("Back");

    //while(input =! 32){
    while(input != 32){
        input = uart_get_char();
    }
}

/*
This function makes you enter the credits menu
*/
void getCredits(){
    clrscr();
    uart_clear();
    uint8_t input = 0;

    drawWindow(22, 8, 57, 32, " Credits ", 1);

    gotoxy(30,12);
    printf("Programming:");
    gotoxy(30,14);
    printf("Oda B. Aggerholm");
    gotoxy(30,16);
    printf("Patrick Strandberg");
    gotoxy(30,18);
    printf("Marc M. Guichard");

    gotoxy(30,21);
    printf("Teaching:");
    gotoxy(30,23);
    printf("Jose%cM.G. Merayo",239);

    gotoxy(30,26);
    printf("Teaching Assistance:");
    gotoxy(30,28);
    printf("Mads F. Madsen");

    fgcolor(2);
    drawBox(30,34,50,38);
    gotoxy(38,36);
    fgcolor(15);
    printf("Back");

    while(input != 32){
        input = uart_get_char();
    }
}

/*
This function makes you enter the difficulty menu
*/
uint8_t getDifficulty(){
    clrscr();
    uart_clear();
    uint8_t menu = 2, input = 0, returnvalue;

    // Initialize the menu (Normal is chosen as default)
    drawTitle(2);

    fgcolor(15);
    drawBox(30,17,50,21);
    gotoxy(38,19);
    printf("Easy");

    fgcolor(2);
    drawBox(30,22,50,26);
    gotoxy(37,24);
    fgcolor(15);
    printf("Normal");

    drawBox(30,27,50,31);
    gotoxy(38,29);
    printf("Hard");
    drawBox(30,32,50,36);
    gotoxy(35,34);
    printf("Main Menu");

    while(input != 32){

    // Press s to go back to normal, press enter to activate easy difficulty.
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

    // Press w to choose the easy, press s to choose hard, press enter to activate normal difficulty
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

    // Press w to go back to Hard, press enter to go back to main menu.
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
    if (menu == 1 & input == 32){
        //printf("Easy Mode");
        returnvalue = 1;
    }
    else if (menu == 2 & input == 32){
        //printf("Normal Mode");
        returnvalue = 2;
    }
    else if (menu == 3 & input == 32){
        //printf("Hard Mode");
        returnvalue = 3;
    }
    else if (menu == 4 & input == 32){
        returnvalue = mainmenu();
    }
    return returnvalue;

}

/*
This function draws the Easy difficulty box
*/
void drawmenuEasy(){
    drawBox(30,22,50,26);

    fgcolor(2);
    drawBox(30,17,50,21);
    fgcolor(15);
}

/*
This function draws the Normal difficulty box
*/
void drawmenuNormal(){
    drawBox(30,17,50,21);
    drawBox(30,27,50,31);

    fgcolor(2);
    drawBox(30,22,50,26);
    fgcolor(15);
}

/*
This function draws the Hard difficulty box
*/
void drawmenuHard(){
    drawBox(30,22,50,26);
    drawBox(30,32,50,36);

    fgcolor(2);
    drawBox(30,27,50,31);
    fgcolor(15);
}

/*
This function draws the main menu menubar
*/
void drawmenuMainMenu(){
    drawBox(30,27,50,31);

    fgcolor(2);
    drawBox(30,32,50,36);
    fgcolor(15);
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
This function draws the player's spaceship
*/
void drawSpaceship(struct spaceship_t *spaceship){

    // We convert the previous position to 32.0 fixed point
    uint32_t prevX = convertTo3200((*spaceship).prevPosX);
    uint32_t prevY = convertTo3200((*spaceship).prevPosY);

    // We delete the enemy at its last position
    deleteSymbol(prevX,prevY);
    deleteSymbol(prevX,prevY-1);
    deleteSymbol(prevX-1,prevY);
    deleteSymbol(prevX-2,prevY);
    deleteSymbol(prevX+1,prevY);
    deleteSymbol(prevX+2,prevY);


    // We define x- and y-components to use in the gotoxy-function
    uint8_t newX;
    uint8_t newY;

    // We convert the current position to 32.0 fixed point
    uint32_t curX = convertTo3200((*spaceship).posX);
    uint32_t curY = convertTo3200((*spaceship).posY);

    fgcolor(2); // Colors the spaceship blue
    gotoxy(curX,curY);
    printf("%c", 186);
    newY = curY - 1;
    gotoxy(curX,newY);
    printf("%c", 220);
    newX = curX - 1;
    gotoxy(newX,curY);
    printf("%c", 205);
    newX = curX - 2;
    gotoxy(newX,curY);
    printf("%c", 173);
    newX = curX + 1;
    gotoxy(newX,curY);
    printf("%c", 205);
    newX = curX + 2;
    gotoxy(newX,curY);
    printf("%c", 173);
    fgcolor(15);
}

/*
This function draws the bullet fired from the spaceship
*/
void drawSpaceshipBullet(struct bullet_t *bullet){

    if ((*bullet).posY < (2 << FIX14_SHIFT) || (*bullet).posX < (3 << FIX14_SHIFT) || (*bullet).posX > (67 << FIX14_SHIFT)){
            (*bullet).drawBullet = 0;

    }

    if ((*bullet).drawBullet == 1 ){

        // We convert the bullet's last position to 32.0 fixed point
        uint32_t prevX = convertTo3200((*bullet).prevPosX);
        uint32_t prevY = convertTo3200((*bullet).prevPosY);

        // We delete the bullet at its last position
        deleteSymbol(prevX, prevY);

        // We convert the bullet's position to 32.0 fixed point
        uint32_t curX = convertTo3200((*bullet).posX);
        uint32_t curY = convertTo3200((*bullet).posY);

        gotoxy(curX,curY);
        //printf("%c", 004); // draws a bullet shaped like a diamond
	if (curY > 2)
        printf("o"); // draws a bullet
    } else if ((*bullet).drawBullet == 0){
        // We convert the bullet's last position to 32.0 fixed point
        uint32_t prevX = convertTo3200((*bullet).prevPosX);
        uint32_t prevY = convertTo3200((*bullet).prevPosY);

        // We delete the bullet at its last position
        deleteSymbol(prevX, prevY);
    }
}

/*
This function draws the bullet fired from the spaceship that kills shielded enemies
*/
void drawSpaceshipShieldBullet(struct bullet_t *bullet){

    if (bullet->posY < (2 << FIX14_SHIFT)){
        bullet->drawBullet = 0;
    } else if (bullet->drawBullet == 1){

        // We convert the bullet's last position to 32.0 fixed point
        uint32_t prevX = convertTo3200((*bullet).prevPosX);
        uint32_t prevY = convertTo3200((*bullet).prevPosY);

        // We delete the bullet at its last position
        deleteSymbol(prevX, prevY);

        // We convert the bullet's position to 32.0 fixed point
        uint32_t curX = convertTo3200((*bullet).posX);
        uint32_t curY = convertTo3200((*bullet).posY);

        gotoxy(curX,curY);
            if (curY > 2){
                fgcolor(9); // Sets the bullet's color to red
                printf("!"); // draws a bullet shaped like a !
                fgcolor(15);
            }
    } else if (bullet->drawBullet == 0 ){
        // We convert the bullet's position to 32.0 fixed point
        uint32_t curX = convertTo3200((*bullet).posX);
        uint32_t curY = convertTo3200((*bullet).posY);

        // We delete the bullet
        deleteSymbol(curX, curY);
    }


}

/*
This function draws the bullet fired from the enemy
*/void drawEnemyBullet(struct bullet_t *enemyBullet){
    if ((*enemyBullet).drawBullet == 1 ){

        // We convert the bullet's last position to 32.0 fixed point
        uint32_t prevX = convertTo3200((*enemyBullet).prevPosX);
        uint32_t prevY = convertTo3200((*enemyBullet).prevPosY);

        // We delete the bullet at its last position
        deleteSymbol(prevX, prevY);

        // We convert the bullet's position to 32.0 fixed point
        uint32_t curX = convertTo3200((*enemyBullet).posX);
        uint32_t curY = convertTo3200((*enemyBullet).posY);

        gotoxy(curX,curY);
        printf("o"); // draws a bullet shaped like a diamond
    } else if ((*enemyBullet).drawBullet == 0){
        // We convert the bullet's last position to 32.0 fixed point
        uint32_t prevX = convertTo3200((*enemyBullet).prevPosX);
        uint32_t prevY = convertTo3200((*enemyBullet).prevPosY);

        // We delete the bullet at its last position
        deleteSymbol(prevX, prevY);
    }
}

/*
This function draws enemy1
*/
void drawEnemyOne(struct enemy_t *enemy){
    if (enemy->drawEnemy == 1 ){
        // We convert the enemy's last position to 32.0 fixed point
        uint32_t prevX = convertTo3200((*enemy).prevPosX);
        uint32_t prevY = convertTo3200((*enemy).prevPosY);

        // We delete the enemy at its last position
        deleteSymbol(prevX, prevY);
        deleteSymbol(prevX-1,prevY);
        deleteSymbol(prevX+1,prevY);
        deleteSymbol(prevX,prevY+1);

        // We convert the bullet's position to 32.0 fixed point
        uint32_t curX = convertTo3200((*enemy).posX);
        uint32_t curY = convertTo3200((*enemy).posY);

        fgcolor(9);
        gotoxy(curX, curY);
        printf("%c",219);
        gotoxy(curX-1, curY);
        printf("%c",219);
        gotoxy(curX+1, curY);
        printf("%c",219);
        gotoxy(curX, curY+1);
        printf("%c",219);
        fgcolor(15);

    } else if (enemy->drawEnemy == 0){
        // We convert the enemy's position to 32.0 fixed point
        uint32_t prevX = convertTo3200((*enemy).prevPosX);
        uint32_t prevY = convertTo3200((*enemy).prevPosY);

        // We delete the enemy at its last position
        deleteSymbol(prevX, prevY);
        deleteSymbol(prevX-1,prevY);
        deleteSymbol(prevX+1,prevY);
        deleteSymbol(prevX,prevY+1);
    }
}

/*
This function draws enemy2
*/
void drawEnemyTwo(struct enemy_t *enemy){
    if (enemy->drawEnemy == 1 ){
        // We convert the enemy's last position to 32.0 fixed point
        uint32_t prevX = convertTo3200((*enemy).prevPosX);
        uint32_t prevY = convertTo3200((*enemy).prevPosY);

        // We delete the enemy at its last position
        deleteSymbol(prevX, prevY);
        deleteSymbol(prevX-1,prevY);
        deleteSymbol(prevX+1,prevY);

        // We convert the bullet's position to 32.0 fixed point
        uint32_t curX = convertTo3200((*enemy).posX);
        uint32_t curY = convertTo3200((*enemy).posY);

        fgcolor(8); // Grey
        gotoxy(curX, curY);
        printf("%c",219);
        gotoxy(curX-1, curY);
        printf("%c",219);
        gotoxy(curX+1, curY);
        printf("%c",219);
        fgcolor(15);

    } else if (enemy->drawEnemy == 0 ){

        // We convert the enemy's position to 32.0 fixed point
        uint32_t prevX = convertTo3200((*enemy).prevPosX);
        uint32_t prevY = convertTo3200((*enemy).prevPosY);

        // We delete the enemy at its last position
        deleteSymbol(prevX, prevY);
        deleteSymbol(prevX-1,prevY);
        deleteSymbol(prevX+1,prevY);
    }
}

/*
This function draws enemy3
*/
void drawEnemyThree(struct enemy_t *enemy){
    if (enemy->drawEnemy == 1 ){
        // We convert the enemy's previous position to 32.0 fixed point
        uint32_t prevX = convertTo3200((*enemy).prevPosX);
        uint32_t prevY = convertTo3200((*enemy).prevPosY);

        // We delete the enemy
        deleteSymbol(prevX, prevY);
        deleteSymbol(prevX-1, prevY+1);
        deleteSymbol(prevX, prevY+1);
        deleteSymbol(prevX+1, prevY+1);
        deleteSymbol(prevX-1, prevY+2);
        deleteSymbol(prevX, prevY+2);
        deleteSymbol(prevX+1, prevY+2);

        // We convert the enemy's position to 32.0 fixed point
        uint32_t curX = convertTo3200((*enemy).posX);
        uint32_t curY = convertTo3200((*enemy).posY);

        fgcolor(5);
        gotoxy(curX, curY);
        printf("%c",219);
        gotoxy(curX-1, curY+1);
        printf("%c",219);
        gotoxy(curX+1, curY+1);
        printf("%c",219);
        gotoxy(curX, curY+1);
        printf("%c",219);
        fgcolor(15);

        fgcolor(6);
        gotoxy(curX-1, curY+2);
        printf("%c%c%c",192,196,217);
        fgcolor(15);

    } else if (enemy->drawEnemy == 0 ){

        // We convert the enemy's previous position to 32.0 fixed point
        uint32_t prevX = convertTo3200((*enemy).prevPosX);
        uint32_t prevY = convertTo3200((*enemy).prevPosY);

        // We delete the enemy
        deleteSymbol(prevX, prevY);
        deleteSymbol(prevX-1, prevY+1);
        deleteSymbol(prevX, prevY+1);
        deleteSymbol(prevX+1, prevY+1);
        deleteSymbol(prevX-1, prevY+2);
        deleteSymbol(prevX, prevY+2);
        deleteSymbol(prevX+1, prevY+2);
    }
}

/*
This function draws the heart-powerup
*/
void drawHeart(struct enemy_t *heart){
    if (heart->drawEnemy == 1 ){
        // We convert the heart's last position to 32.0 fixed point
        uint32_t prevX = convertTo3200((*heart).prevPosX);
        uint32_t prevY = convertTo3200((*heart).prevPosY);

        // We delete the enemy at its last position
        deleteSymbol(prevX, prevY);
        deleteSymbol(prevX-1,prevY);
        deleteSymbol(prevX+1,prevY);
        deleteSymbol(prevX+2,prevY);
        deleteSymbol(prevX,prevY+1);
        deleteSymbol(prevX+1,prevY+1);

        // We convert the heart's position to 32.0 fixed point
        uint32_t curX = convertTo3200((*heart).posX);
        uint32_t curY = convertTo3200((*heart).posY);

        fgcolor(1);
        gotoxy(curX-1, curY);
        printf("%c",40);
        gotoxy(curX, curY);
        printf("%c",92);
        gotoxy(curX+1, curY);
        printf("%c",47);
        gotoxy(curX+2, curY);
        printf("%c",41);
        gotoxy(curX, curY+1);
        printf("%c",92);
        gotoxy(curX+1, curY+1);
        printf("%c",47);
        fgcolor(15);

    } else if (heart->drawEnemy == 0){
        // We convert the heart's position to 32.0 fixed point
        uint32_t curX = convertTo3200((*heart).prevPosX);
        uint32_t curY = convertTo3200((*heart).prevPosY);

        // We delete the heart at its last position
        deleteSymbol(curX, curY);
        deleteSymbol(curX-1,curY);
        deleteSymbol(curX+1,curY);
        deleteSymbol(curX+2,curY);
        deleteSymbol(curX,curY+1);
        deleteSymbol(curX+1,curY+1);
    }
}
/*
Game-over screen
*/
void gameOver(uint32_t enemyOneKilled, uint32_t enemyTwoKilled, uint32_t enemyThreeKilled){
    uint8_t input = 0;
    clrscr();

    fgcolor(15);
    gotoxy(23,4);
    printf("  %c%c%c%c     %c%c%c    %c%c   %c%c  %c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,5);
    printf(" %c%c       %c%c %c%c   %c%c%c %c%c%c  %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,6);
    printf("%c%c       %c%c   %c%c  %c%c%c%c%c%c%c  %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,7);
    printf("%c%c  %c%c%c  %c%c   %c%c  %c%c %c %c%c  %c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,8);
    printf("%c%c   %c%c  %c%c%c%c%c%c%c  %c%c   %c%c  %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,9);
    printf(" %c%c  %c%c  %c%c   %c%c  %c%c   %c%c  %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,10);
    printf("  %c%c%c%c%c  %c%c   %c%c  %c%c   %c%c  %c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,13);
    printf(" %c%c%c%c%c   %c%c   %c%c  %c%c%c%c%c%c%c  %c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,14);
    printf("%c%c   %c%c  %c%c   %c%c  %c%c       %c%c   %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,15);
    printf("%c%c   %c%c  %c%c   %c%c  %c%c       %c%c   %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,16);
    printf("%c%c   %c%c  %c%c   %c%c  %c%c%c%c%c%c%c  %c%c  %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,17);
    printf("%c%c   %c%c   %c%c %c%c   %c%c       %c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,18);
    printf("%c%c   %c%c    %c%c%c    %c%c       %c%c %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(23,19);
    printf(" %c%c%c%c%c      %c     %c%c%c%c%c%c%c  %c%c  %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);


    // Print the kill-rate

    gotoxy(36,24);
    printf("KILL-RATE:");

    fgcolor(9);
    gotoxy(40, 27);
    printf("%c",219);
    gotoxy(39, 27);
    printf("%c",219);
    gotoxy(41, 27);
    printf("%c",219);
    gotoxy(40, 28);
    printf("%c",219);
    fgcolor(15);
    gotoxy(40,30);
    printf("%d",enemyOneKilled);

    fgcolor(8); // Grey
    gotoxy(32, 27);
    printf("%c",219);
    gotoxy(31, 27);
    printf("%c",219);
    gotoxy(33, 27);
    printf("%c",219);
    fgcolor(15);
    gotoxy(32,30);
    printf("%d",enemyTwoKilled);

    fgcolor(5);
    gotoxy(48, 26);
    printf("%c",219);
    gotoxy(47, 27);
    printf("%c",219);
    gotoxy(49, 27);
    printf("%c",219);
    gotoxy(48, 27);
    printf("%c",219);
    fgcolor(15);

    fgcolor(6);
    gotoxy(47, 28);
    printf("%c%c%c",192,196,217);
    fgcolor(15);
    gotoxy(48,30);
    printf("%d",enemyThreeKilled);

    fgcolor(2);
    drawBox(30,33,50,37);
    gotoxy(34,35);
    fgcolor(15);
    printf("Back to menu");

    while(input != 32){
    input = uart_get_char();
    }
    clrscr();

}

//Draw the gamewindow
void drawGameWindow(int8_t playerHits){

//GAME-window:
fgcolor(15);
drawWindow(2, 1, 68, 39,"GAME",1);


//STATS display:
drawWindow(69, 1, 79, 39,"STATS",1);

//
getHealth(playerHits);

gotoxy(72,20);
printf("KILLS;");

//printing enemy1
fgcolor(9);
gotoxy(74, 22);
printf("%c",219);
gotoxy(73, 22);
printf("%c",219);
gotoxy(75, 22);
printf("%c",219);
gotoxy(74, 23);
printf("%c",219);
fgcolor(15);

//printing enemy2
fgcolor(8); // Grey
gotoxy(74, 28);
printf("%c",219);
gotoxy(73, 28);
printf("%c",219);
gotoxy(75, 28);
printf("%c",219);
fgcolor(15);

//printing enemy3
fgcolor(5);
gotoxy(74, 34);
printf("%c",219);
gotoxy(73, 34);
printf("%c",219);
gotoxy(75, 34);
printf("%c",219);
gotoxy(74, 33);
printf("%c",219);
fgcolor(15);

fgcolor(6);
gotoxy(73, 35);
printf("%c%c%c",192,196,217);
fgcolor(15);

}


void getHealth(int8_t hits){

    //printing lives
    gotoxy(71,3);
    printf("LIVES:");

    if (hits==0){
    //green
    fgcolor(2);
    gotoxy(72,4);
    printf("%c%c%c%c", 219, 219, 219, 219);
    gotoxy(72,5);
    printf("%c%c%c%c", 219, 219, 219, 219);

    //yellow
    fgcolor(11);
    gotoxy(72,6);
    printf("%c%c%c%c", 219, 219, 219, 219);
    gotoxy(72,7);
    printf("%c%c%c%c", 219, 219, 219, 219);

    //red
    fgcolor(1);
    gotoxy(72,8);
    printf("%c%c%c%c", 219, 219, 219, 219);
    gotoxy(72,9);
    printf("%c%c%c%c", 219, 219, 219, 219);
    fgcolor(15);
}
    if (hits==1){
     //black
    fgcolor(0);
    gotoxy(72,4);
    printf("%c%c%c%c", 219, 219, 219, 219);
    gotoxy(72,5);
    printf("%c%c%c%c", 219, 219, 219, 219);

    //yellow
    fgcolor(11);
    gotoxy(72,6);
    printf("%c%c%c%c", 219, 219, 219, 219);
    gotoxy(72,7);
    printf("%c%c%c%c", 219, 219, 219, 219);

    //red
    fgcolor(1);
    gotoxy(72,8);
    printf("%c%c%c%c", 219, 219, 219, 219);
    gotoxy(72,9);
    printf("%c%c%c%c", 219, 219, 219, 219);
    fgcolor(15);
}
    if (hits==2){
    //black
    fgcolor(0);
    gotoxy(72,4);
    printf("%c%c%c%c", 219, 219, 219, 219);
    gotoxy(72,5);
    printf("%c%c%c%c", 219, 219, 219, 219);

    //black
    fgcolor(0);
    gotoxy(72,6);
    printf("%c%c%c%c", 219, 219, 219, 219);
    gotoxy(72,7);
    printf("%c%c%c%c", 219, 219, 219, 219);

    //red
    fgcolor(1);
    gotoxy(72,8);
    printf("%c%c%c%c", 219, 219, 219, 219);
    gotoxy(72,9);
    printf("%c%c%c%c", 219, 219, 219, 219);
    fgcolor(15);
}
    if (hits==3){
    //black
    fgcolor(0);
    gotoxy(72,4);
    printf("%c%c%c%c", 219, 219, 219, 219);
    gotoxy(72,5);
    printf("%c%c%c%c", 219, 219, 219, 219);

    //black
    fgcolor(0);
    gotoxy(72,6);
    printf("%c%c%c%c", 219, 219, 219, 219);
    gotoxy(72,7);
    printf("%c%c%c%c", 219, 219, 219, 219);

    //black
    fgcolor(0);
    gotoxy(72,8);
    printf("%c%c%c%c", 219, 219, 219, 219);
    gotoxy(72,9);
    printf("%c%c%c%c", 219, 219, 219, 219);
    fgcolor(15);
}

}

/*
Boss-key. If 'b' is pressed while playing, the boss-key screen will be activated
*/
void bossKey(char temp){

    if (temp == 'b' || temp == 'B'){
        clrscr();
        printf("Microsoft [Version 10.0.18362.535]\n");
        printf("(c) 2019 Microsoft Corporation. Alle rettigheder forbeholdes\n");
        printf("\n");
        printf("\n");
        printf("C:/Users/LookBusy>\n");
        while(uart_get_count() < 1){}
        clrscr();
        drawGameWindow(0);
    }
}

/*
This functions draws a thank you screen
*/
void thankYou(){
    gotoxy(21,6);
    printf("%c%c%c%c%c%c  %c%c  %c%c   %c%c%c%c   %c%c  %c%c  %c%c  %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(21,7);
    printf("%c%c%c%c%c%c  %c%c  %c%c  %c%c%c%c%c%c  %c%c  %c%c  %c%c %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(21,8);
    printf("  %c%c    %c%c  %c%c  %c%c  %c%c  %c%c%c %c%c  %c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(21,9);
    printf("  %c%c    %c%c%c%c%c%c  %c%c  %c%c  %c%c%c%c%c%c  %c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(21,10);
    printf("  %c%c    %c%c%c%c%c%c  %c%c%c%c%c%c  %c%c%c%c%c%c  %c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(21,11);
    printf("  %c%c    %c%c  %c%c  %c%c  %c%c  %c%c %c%c%c  %c%c%c%c%c ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(21,12);
    printf("  %c%c    %c%c  %c%c  %c%c  %c%c  %c%c  %c%c  %c%c %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(21,13);
    printf("  %c%c    %c%c  %c%c  %c%c  %c%c  %c%c  %c%c  %c%c  %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);

    gotoxy(16,16);
    printf("%c%c  %c%c   %c%c%c%c   %c%c  %c%c    %c%c%c%c%c%c   %c%c%c%c   %c%c%c%c%c ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(16,17);
    printf("%c%c  %c%c  %c%c%c%c%c%c  %c%c  %c%c    %c%c%c%c%c%c  %c%c%c%c%c%c  %c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(16,18);
    printf("%c%c  %c%c  %c%c  %c%c  %c%c  %c%c    %c%c      %c%c  %c%c  %c%c  %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(16,19);
    printf("%c%c%c%c%c%c  %c%c  %c%c  %c%c  %c%c    %c%c%c%c    %c%c  %c%c  %c%c  %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(16,20);
    printf(" %c%c%c%c   %c%c  %c%c  %c%c  %c%c    %c%c%c%c    %c%c  %c%c  %c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(16,21);
    printf("  %c%c    %c%c  %c%c  %c%c  %c%c    %c%c      %c%c  %c%c  %c%c  %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(16,22);
    printf("  %c%c    %c%c%c%c%c%c  %c%c%c%c%c%c    %c%c      %c%c%c%c%c%c  %c%c  %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(16,23);
    printf("  %c%c     %c%c%c%c    %c%c%c%c     %c%c       %c%c%c%c   %c%c  %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);

    gotoxy(13,26);
    printf("%c%c%c%c%c   %c%c       %c%c%c%c   %c%c  %c%c  %c%c%c%c%c%c  %c%c  %c%c   %c%c%c%c ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(13,27);
    printf("%c%c%c%c%c%c  %c%c      %c%c%c%c%c%c  %c%c  %c%c  %c%c%c%c%c%c  %c%c  %c%c  %c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(13,28);
    printf("%c%c  %c%c  %c%c      %c%c  %c%c  %c%c  %c%c    %c%c    %c%c%c %c%c  %c%c  %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(13,29);
    printf("%c%c  %c%c  %c%c      %c%c  %c%c  %c%c%c%c%c%c    %c%c    %c%c%c%c%c%c  %c%c    ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(13,30);
    printf("%c%c%c%c%c   %c%c      %c%c%c%c%c%c   %c%c%c%c     %c%c    %c%c%c%c%c%c  %c%c %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(13,31);
    printf("%c%c      %c%c      %c%c  %c%c    %c%c      %c%c    %c%c %c%c%c  %c%c  %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(13,32);
    printf("%c%c      %c%c%c%c%c%c  %c%c  %c%c    %c%c    %c%c%c%c%c%c  %c%c  %c%c  %c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(13,33);
    printf("%c%c      %c%c%c%c%c%c  %c%c  %c%c    %c%c    %c%c%c%c%c%c  %c%c  %c%c   %c%c%c%c ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
}
