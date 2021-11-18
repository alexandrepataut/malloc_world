#include "malloc_world.h"
#include "game.h"

// PRINTING FUNCTION FOR COMMANDS
void printCommands(){
    printf("          _______________________________________\n");
    printf("         /                                       \\\n");
    printf("         |                COMMANDS                |\n");
    printf("         |                                        |\n");
    printf("         |   +--------------------------------+   |\n");
    printf("         |   |      GO UP : Press 'z'         |   |\n");
    printf("         |   |      GO DOWN : Press 's'       |   |\n");
    printf("         |   |      GO LEFT : Press 'q'       |   |\n");
    printf("         |   |      GO RIGHT : Press 'd'      |   |\n");
    printf("         |   |      CONSULT                   |   |\n");
    printf("         |   |                                |   |\n");
    printf("         |   |        -INVENTORY : Press 'i'  |   |\n");
    printf("         |   |        -WEAPON SET : Press 'w' |   |\n");
    printf("         |   |                                |   |\n");
    printf("         |   |      ACT : Press 'a'           |   |\n");
    printf("         |   +--------------------------------+   |\n");
    printf("         |                                        |\n");
    printf("         |        Press 'Enter' to confirm        |\n");
    printf("         |                                        |\n");
    printf("         \\________________________________________/\n");
    printf("\n\n");
}

void takeInput(game *myGame){
    // CREATE A CHAR TO RECEIVE THE COMMAND INPUT
    char input[50];
    printf("What is your entry ?\n\n\tPress 'c' to see commands instructions, then press 'Enter'\n");
    scanf("%s", input);

    // PRINT INSTRUCTION ON COMMAND LINE

    // MAKE MOVE DEPENDING ON THE INPUT
    if (strcmp(input, "z")==0 || strcmp(input, "Z")==0) {
        moveUp(myGame);
        return;
    }
    if (strcmp(input, "s")==0 || strcmp(input, "S")==0) {
        moveDown(myGame);
        return;
    }
    if (strcmp(input, "q")==0 || strcmp(input, "Q")==0) {
        moveLeft(myGame);
        return;
    }
    if (strcmp(input, "d")==0 || strcmp(input, "D")==0) {
        moveRight(myGame);
        return;
    }
    if (strcmp(input, "i")==0 || strcmp(input, "I")==0) {
        printInventory(myGame->p);
        return;
    }
    if (strcmp(input, "c")==0 || strcmp(input, "C")==0) {
        printCommands();
        return;
    }
    if (strcmp(input, "w")==0 || strcmp(input, "W")==0) {
        printWeaponSet(myGame->p);
        return;
    }
    if (strcmp(input, "a")==0 || strcmp(input, "A")==0) {
        makeAction(myGame);
        return;
    }
    printf("    +-----------------------------------------------------------------------------+\n");
    printf("    |                                                                             |\n");
    printf("    | %s : Invalid input (Type 'c' and press 'Enter' to see commands instructions) |\n", input);
    printf("    |                                                                             |\n");
    printf("    +-----------------------------------------------------------------------------+\n");
    return;
}

int main() {
    game *myGame = newGame();
    // LAUNCH THE GAME WITH A LOOP
    myGame->p->level = 666;
    int counter = 0;
    while(counter < 3000){
        printAll(myGame);
        takeInput(myGame);
        counter++;
    }
    
    closeGame(myGame);
    return 0;
}