#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "game.h"


void printHelper(){
    printf("========================================\n");
    printf("|                                      |\n");
    printf("|               COMMANDS               |\n");
    printf("|                                      |\n");
    printf("|   +------------------------------+   |\n");
    printf("|   |      GO UP : Press 'u'       |   |\n");
    printf("|   |      GO DOWN : Press 'd'     |   |\n");
    printf("|   |      GO LEFT : Press 'l'     |   |\n");
    printf("|   |      GO RIGHT : Press 'r'    |   |\n");
    printf("|   +------------------------------+   |\n");
    printf("|                                      |\n");
    printf("========================================\n");
    printf("\n\n");
    printf("Please enter your move (u, d, l, r) and press 'Enter'\n\n");
}

int main() {
    /*unsigned int l, c;
    l=8;
    c=8;
    map *myMap1 = initMap(l,c,1);
    map *myMap2 = initMap(l,c,2);
    map *myMap3 = initMap(l,c,3);
    printf("\n\n\n");
    printf("\t\t\tMAP 1\n\n");
    printMap(myMap1);
    printf("\n\n\n\n");
    printf("\t\t\tMAP 2\n\n");
    printMap(myMap2);
    printf("\n\n\n\n");
    printf("\t\t\tMAP 3\n\n");
    printMap(myMap3);*/

    game *myGame = newGame();
    int counter = 0;
    while(counter < 20){
        printf("\t\t\tMAP %d\n", myGame->p->currentMap);
        printAll(myGame);
        printHelper();

        char input[1];

        scanf("%s", input);
        if(strcmp(input, "u")==0)
            moveUp(myGame);
        if(strcmp(input, "d")==0)
            moveDown(myGame);
        if(strcmp(input, "l")==0)
            moveLeft(myGame);
        if(strcmp(input, "r")==0)
            moveRight(myGame);

        printAll(myGame);
        counter++;
    }

    return 0;
}