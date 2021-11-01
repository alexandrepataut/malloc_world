#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <assert.h>
#include "map.h"
#include "player.h"

// GAME CLASS CONTAINS THE FULL GAME MANAGING THANKS TO OTHER CLASSES (MAP, PLAYER, ...)
// WE CAN OPERATE ON EVERY ASPECTS OF THE GAME RIGHT HERE
// THE MAIN FUNCTION IN 'main.c' CALLS PRINCIPLY THE GAME FUNCTIONS 

typedef struct game{
    // GAME STRUCT IS DEFINED BY A PLAYER AND A MAPSET (TAB OF SEVERAL MAPS) => WE HAVE ALL THE MAPS CREATED AT THE CREATION OF A GAME (4 MAPS)
    player *p;
    map **mapSet;
}game;

// FUNCTION FOR CREATING A NEW GAME
game *newGame(){
    game *myGame = malloc(sizeof(myGame));
    myGame->mapSet = malloc(4*sizeof(map));
    // BASICALLY WE MAKE :
    //      MAP 1 : 8 ROWS AND COLS, RANK 1
    //      MAP 2 : 12"                  "2
    //      MAP 3 : 15"                  "3
    //      MAP 4 : 20"                  "3 -> IN 4TH POSITION BUT SAME PARAMETERS THAN MAP 3
    myGame->mapSet[0] = initMap(8, 8, 1);
    myGame->mapSet[1] = initMap(12, 12, 2);
    myGame->mapSet[2] = initMap(15, 15, 3);
    myGame->mapSet[3] = initMap(20, 20, 3);
    // PUT THE PLAYER ON THE FIRST MAP ON A RAND POSITION
    putPlayer(myGame->mapSet[0]);

    myGame->p = newPlayer();

    // UPDATE PLAYER STRUCT ATTRIBUTES
    myGame->p->posX = getXPlayerPos(myGame->mapSet[0]);
    myGame->p->posY = getYPlayerPos(myGame->mapSet[0]);
    myGame->p->currentMap = myGame->mapSet[0]->rank;
    
    return myGame;
}

// PRINTING FUNCTION FOR THE CURRENT GAME MAP AND THE PLAYER STATS
void printAll(game *myGame){
    printf("\n\n");
    printMap(myGame->mapSet[myGame->p->currentMap-1]);
    printf("\n\n");
    printPlayer(myGame->p);
    printf("\n\n");
}

// MOVING FUNCTIONS
// PLAYER CAN MOVE ON A CASE ONLY IF THIS ONE IS FREE (i.e 'myGame->mapSet[currentMap]->[x, y] = 0')

    // myGame                           REPRESENTS THE ACTUAL GAME PLAYED
    // myGame->mapSet                   REPRESENTS THE SET OF MAPS WHICH CONSTITUTE THE GAME
    // myGame->p                        REPRESENTS THE PLAYER STRUCT OF THE GAME
    // myGame->p->currentMap            CORRESPONDS WITH THE CURRENT "RANK" OF THE MAP -> NOT THE POSITION OF THIS MAP IN THE MAPSET
    // myGame->mapSet[currentMap - 1]   CORRESPONDS WITH THE POSITION OF THE CURRENT MAP IN THE MAPSET

// MOVEUP FUNCTION -> FROM myGame->mapSet[currentMap]->map[x][y] TO myGame->mapSet[currentMap]->map[x - 1][y]
void moveUp(game *myGame){
    // CHECK IF WE ARE GOING OUT OF MAP
    if(myGame->p->posX-1 < 0)
        return;

    // GET NEXT COORD(x, y) POSITION 
    int posXNextCase = myGame->p->posX-1;
    int posYNextCase = myGame->p->posY;

    // GET VALUES OF NEXT CASE AND CURRENT POSITION OF THE PLAYER
    int nextCaseValue = myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase];
    int currentXPos = getXPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);
    int currentYPos = getYPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);

    // CHECK IF NEXT CASE IS FREE AND IF WE STAY IN THE MAP ZONE -> ELSE, DON'T DO NOTHING
    if(posXNextCase >= 0 && posXNextCase < myGame->mapSet[myGame->p->currentMap-1]->rows && nextCaseValue == 0){
        myGame->mapSet[myGame->p->currentMap-1]->map[currentXPos][currentYPos] = 0;
        myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase] = 1;
        myGame->p->posX = posXNextCase;
        myGame->p->posY = posYNextCase;
    }
    return;
}

// MOVEDOWN FUNCTION -> FROM myGame->mapSet[currentMap]->map[x][y] TO myGame->mapSet[currentMap]->map[x + 1][y]
void moveDown(game *myGame){
    // CHECK IF WE ARE GOING OUT OF MAP
    if(myGame->p->posX+1 >= myGame->mapSet[myGame->p->currentMap-1]->rows)
        return;

    // GET NEXT COORD(x, y) POSITION 
    int posXNextCase = myGame->p->posX+1;
    int posYNextCase = myGame->p->posY;

    // GET VALUES OF NEXT CASE AND CURRENT POSITION OF THE PLAYER
    int nextCaseValue = myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase];
    int currentXPos = getXPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);
    int currentYPos = getYPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);

    // CHECK IF NEXT CASE IS FREE AND IF WE STAY IN THE MAP ZONE -> ELSE, DON'T DO NOTHING
    if(posXNextCase >= 0 && posXNextCase < myGame->mapSet[myGame->p->currentMap-1]->rows && nextCaseValue == 0){
        myGame->mapSet[myGame->p->currentMap-1]->map[currentXPos][currentYPos] = 0;
        myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase] = 1;
        myGame->p->posX = posXNextCase;
        myGame->p->posY = posYNextCase;
    }
    return;
}

// MOVELEFT FUNCTION -> FROM myGame->mapSet[currentMap]->map[x][y] TO myGame->mapSet[currentMap]->map[x][y - 1]
void moveLeft(game *myGame){
    // CHECK IF WE ARE GOING OUT OF MAP
    if(myGame->p->posY-1 < 0)
        return;

    // GET NEXT COORD(x, y) POSITION 
    int posXNextCase = myGame->p->posX;
    int posYNextCase = myGame->p->posY-1;

    // GET VALUES OF NEXT CASE AND CURRENT POSITION OF THE PLAYER
    int nextCaseValue = myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase];
    int currentXPos = getXPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);
    int currentYPos = getYPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);

    // CHECK IF NEXT CASE IS FREE AND IF WE STAY IN THE MAP ZONE -> ELSE, DON'T DO NOTHING
    if(posYNextCase >= 0 && posYNextCase < myGame->mapSet[myGame->p->currentMap-1]->cols && nextCaseValue == 0){
        myGame->mapSet[myGame->p->currentMap-1]->map[currentXPos][currentYPos] = 0;
        myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase] = 1;
        myGame->p->posX = posXNextCase;
        myGame->p->posY = posYNextCase;
    }
    return;
}

// MOVERIGHT FUNCTION -> FROM myGame->mapSet[currentMap]->map[x][y] TO myGame->mapSet[currentMap]->map[x][y + 1]
void moveRight(game *myGame){
    // CHECK IF WE ARE GOING OUT OF MAP
    if(myGame->p->posY+1 > myGame->mapSet[myGame->p->currentMap-1]->cols)
        return;

    // GET NEXT COORD(x, y) POSITION 
    int posXNextCase = myGame->p->posX;
    int posYNextCase = myGame->p->posY+1;

    // GET VALUES OF NEXT CASE AND CURRENT POSITION OF THE PLAYER
    int nextCaseValue = myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase];
    int currentXPos = getXPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);
    int currentYPos = getYPlayerPos(myGame->mapSet[myGame->p->currentMap-1]);

    // CHECK IF NEXT CASE IS FREE AND IF WE STAY IN THE MAP ZONE -> ELSE, DON'T DO NOTHING
    if(posYNextCase >= 0 && posYNextCase < myGame->mapSet[myGame->p->currentMap-1]->cols && nextCaseValue == 0){
        myGame->mapSet[myGame->p->currentMap-1]->map[currentXPos][currentYPos] = 0;
        myGame->mapSet[myGame->p->currentMap-1]->map[posXNextCase][posYNextCase] = 1;
        myGame->p->posX = posXNextCase;
        myGame->p->posY = posYNextCase;
    }
    return;
}