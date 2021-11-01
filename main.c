#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "game.h"

// PRINTING FUNCTION FOR COMMANDS
void printHelper(){
    printf("          ______________________________________\n");
    printf("         /                                      \\\n");
    printf("         |               COMMANDS               |\n");
    printf("         |                                      |\n");
    printf("         |   +------------------------------+   |\n");
    printf("         |   |      GO UP : Press 'u'       |   |\n");
    printf("         |   |      GO DOWN : Press 'd'     |   |\n");
    printf("         |   |      GO LEFT : Press 'l'     |   |\n");
    printf("         |   |      GO RIGHT : Press 'r'    |   |\n");
    printf("         |   +------------------------------+   |\n");
    printf("         |                                      |\n");
    printf("         \\______________________________________/\n");
    printf("\n\n");
}

void makeMove(game *myGame){
    // CREATE A CHAR TO RECEIVE THE COMMAND INPUT
    char input[1];
    printf("Please enter your move (u, d, l, r) and press 'Enter'\n'h' for help\n\n");
    scanf("%s", input);

    // PRINT INSTRUCTION ON COMMAND LINE

    // MAKE MOVE DEPENDING ON THE INPUT
    if(strcmp(input, "u")==0 || strcmp(input, "U")==0){
        moveUp(myGame);
        return;
    }
    if(strcmp(input, "d")==0 || strcmp(input, "D")==0){
        moveDown(myGame);
        return;
    }
    if(strcmp(input, "l")==0 || strcmp(input, "L")==0){
        moveLeft(myGame);
        return;
    }
    if(strcmp(input, "r")==0 || strcmp(input, "R")==0){
        moveRight(myGame);
        return;
    }
    if(strcmp(input, "h")==0 || strcmp(input, "H")==0){
        printHelper();
        return;
    }
    printf("Invalid input (try again with 'u', 'd', 'l', 'r' or 'h' for help\n");
}

int main() {
    game *myGame = newGame();
    int counter = 0;
    printAll(myGame);

    // LAUNCH THE GAME WITH A LOOP
    while(counter < 3000){
        makeMove(myGame);
        printAll(myGame);
        counter++;
    }

    return 0;
}