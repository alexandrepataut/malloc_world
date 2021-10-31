#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <assert.h>
#include "map.h"
#include "player.h"

typedef struct game{
    player *p;
    map **mapSet;
}game;

game *newGame(){
    game *myGame = malloc(sizeof(myGame));
    myGame->mapSet = malloc(4*sizeof(map));
    myGame->mapSet[0] = initMap(8, 8, 1);
    myGame->mapSet[1] = initMap(12, 12, 2);
    myGame->mapSet[2] = initMap(15, 15, 3);
    myGame->mapSet[3] = initMap(20, 20, 3);
    putPlayer(myGame->mapSet[0]);

    myGame->p = newPlayer();

    myGame->p->posX = getXPlayerPos(myGame->mapSet[0]);
    myGame->p->posY = getYPlayerPos(myGame->mapSet[0]);
    myGame->p->currentMap = myGame->mapSet[0]->rank;
    
    return myGame;
}

void printAll(game *myGame){
    printMap(myGame->mapSet[myGame->p->currentMap-1]);
    printPlayer(myGame->p);
}


void moveUp(game *myGame){
    if(myGame->p->posX-1 < 0)
        return;

    int posXNextCase = myGame->p->posX-1;
    int posYNextCase = myGame->p->posY;
    int nextCaseValue = myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase];
    int currentXPos = getXPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);
    int currentYPos = getYPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);

    if(posXNextCase >= 0 && posXNextCase < myGame->mapSet[myGame->p->currentMap-1]->rows && nextCaseValue == 0){
        myGame->mapSet[myGame->p->currentMap-1]->map[currentXPos][currentYPos] = 0;
        myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase] = 1;
        myGame->p->posX = posXNextCase;
        myGame->p->posY = posYNextCase;
    }
    return;
}

void moveDown(game *myGame){
    if(myGame->p->posX+1 >= myGame->mapSet[myGame->p->currentMap-1]->rows)
        return;

    int posXNextCase = myGame->p->posX+1;
    int posYNextCase = myGame->p->posY;
    int nextCaseValue = myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase];
    int currentXPos = getXPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);
    int currentYPos = getYPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);

    if(posXNextCase >= 0 && posXNextCase < myGame->mapSet[myGame->p->currentMap-1]->rows && nextCaseValue == 0){
        myGame->mapSet[myGame->p->currentMap-1]->map[currentXPos][currentYPos] = 0;
        myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase] = 1;
        myGame->p->posX = posXNextCase;
        myGame->p->posY = posYNextCase;
    }
    return;
}

void moveLeft(game *myGame){
    if(myGame->p->posY-1 < 0)
        return;

    int posXNextCase = myGame->p->posX;
    int posYNextCase = myGame->p->posY-1;
    int nextCaseValue = myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase];
    int currentXPos = getXPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);
    int currentYPos = getYPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);

    if(posYNextCase >= 0 && posYNextCase < myGame->mapSet[myGame->p->currentMap-1]->cols && nextCaseValue == 0){
        myGame->mapSet[myGame->p->currentMap-1]->map[currentXPos][currentYPos] = 0;
        myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase] = 1;
        myGame->p->posX = posXNextCase;
        myGame->p->posY = posYNextCase;
    }
    return;
}

void moveRight(game *myGame){
    if(myGame->p->posY+1 > myGame->mapSet[myGame->p->currentMap-1]->cols)
        return;

    int posXNextCase = myGame->p->posX;
    int posYNextCase = myGame->p->posY+1;
    int nextCaseValue = myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase];
    int currentXPos = getXPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);
    int currentYPos = getYPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);

    if(posYNextCase >= 0 && posYNextCase < myGame->mapSet[myGame->p->currentMap-1]->cols && nextCaseValue == 0){
        myGame->mapSet[myGame->p->currentMap-1]->map[currentXPos][currentYPos] = 0;
        myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase] = 1;
        myGame->p->posX = posXNextCase;
        myGame->p->posY = posYNextCase;
    }
    return;
}