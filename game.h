#include "malloc_world.h"
#include "map.h"
#include "player.h"

#ifndef GAME_H
#define GAME_H
#endif

// GAME CLASS CONTAINS THE FULL GAME MANAGING THANKS TO OTHER CLASSES (MAP, PLAYER, ...)
// WE CAN OPERATE ON EVERY ASPECTS OF THE GAME RIGHT HERE
// THE MAIN FUNCTION IN 'main.c' CALLS PRINCIPLY THE GAME FUNCTIONS 

typedef struct game{
    // GAME STRUCT IS DEFINED BY A PLAYER AND A MAPSET (TAB OF SEVERAL MAPS) => WE HAVE ALL THE MAPS CREATED AT THE CREATION OF A GAME (4 MAPS)
    player *p;
    map **mapSet;
    int nbOfMap;
}game;
int caseValToItemVal(int caseValue);
int findTargetValueCase(game *myGame, int posX, int posY);
int findTargetXPos(game *myGame);
int findTargetYPos(game *myGame);

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
    myGame->nbOfMap = 4;
    
    return myGame;
}

void closeGame(game *myGame){
    assert(myGame);
    assert(myGame->mapSet);
    //freeMapSet(myGame->mapSet, 4);
    //freePlayer(myGame->p);
    //free(myGame);
}

void printPlayer(game *myGame){
    printf("                 ________________________\n");
    printf("                /                        \\\n");
    printf("                |      PLAYER STATS      |\n");
    printf("                |                        |\n");
    printf("                +------------------------+\n");
    printf("    \t\t| HP : %d/%d\n", myGame->p->currentHp, myGame->p->hp);
    printf("    \t\t| PLAYER LEVEL : %d\n", myGame->p->level);
    printf("    \t\t| POSITION :  [%d, %d]\n", myGame->p->posX, myGame->p->posY);
    printf("    \t\t| DIRECTION :  ");
    switch (myGame->p->direction)
    {
    case _NORTH_:
        printf("NORTH\n");
        break;
    case _SOUTH_:
        printf("SOUTH\n");
        break;
    case _EAST_:
        printf("EAST\n");
        break;
    case _WEST_:
        printf("WEST\n");
        break;
    
    default:
        break;
    }
    printf("    \t\t| CURRENT MAP : %d\n", myGame->p->currentMap);
    printf("    \t\t| TARGET : ");
    int targetXPos = findTargetXPos(myGame);
    int targetYPos = findTargetYPos(myGame);
    if(targetXPos >= 0 && targetXPos < myGame->mapSet[myGame->p->currentMap-1]->rows && targetYPos >= 0 && targetYPos < myGame->mapSet[myGame->p->currentMap-1]->cols){
        switch (findCaseType(findTargetValueCase(myGame, findTargetXPos(myGame), findTargetYPos(myGame))))
        {
        case _IS_RESOURCE_:
            printResource(caseValToItemVal(findTargetValueCase(myGame, findTargetXPos(myGame), findTargetYPos(myGame))));
            //printFarming(myGame->mapSet[myGame->p->currentMap - 1]->map[myGame->p->posX][myGame->p->posY]);
            break;
        case _IS_MONSTER_CASE_:
            printf("Monster");
            break;
        case _IS_TP_CASE_:
            printf("Make teleportation ?");
            break;
        case _PNJ_CASE_:
            printf("Talk to Pr. Malloc ?");
            break;
        default:
            break;
        }
    }
    printf("\n");
    printf("                \\_______________________/\n");
}
// PRINTING FUNCTION FOR THE CURRENT GAME MAP AND THE PLAYER STATS
void printAll(game *myGame){
    assert(myGame);
    assert(myGame->p);
    assert(myGame->mapSet[myGame->p->currentMap-1]);
    printf("\n\n");
    printMap(myGame->mapSet[myGame->p->currentMap-1]);
    printf("\n\n");
    printPlayer(myGame);
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
    // CHECK IF PLAYER IS ORIENTED ON NORTH, IF NOT SET HIS DIRECTION ON
    if(myGame->p->direction != _NORTH_){
        myGame->p->direction = _NORTH_;
        return;
    }
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
    // CHECK IF PLAYER IS ORIENTED ON SOUTH, IF NOT SET HIS DIRECTION ON
    if(myGame->p->direction != _SOUTH_){
        myGame->p->direction = _SOUTH_;
        return;
    }
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
        // CHECK IF PLAYER IS ORIENTED ON EAST, IF NOT SET HIS DIRECTION ON
    if(myGame->p->direction != _WEST_){
        myGame->p->direction = _WEST_;
        return;
    }
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
    // CHECK IF PLAYER IS ORIENTED ON WEST, IF NOT SET HIS DIRECTION ON
    if(myGame->p->direction != _EAST_){
        myGame->p->direction = _EAST_;
        return;
    }
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

int findTargetValueCase(game *myGame, int posX, int posY){
    assert(myGame);
    assert(myGame->p);
    assert(myGame->mapSet);
    assert(myGame->mapSet[myGame->p->currentMap-1]);

    if(posX < 0 || posY < 0 || posX > myGame->mapSet[myGame->p->currentMap-1]->rows || posY > myGame->mapSet[myGame->p->currentMap-1]->cols)
        return _INFRANCHISSABLE_;

    return myGame->mapSet[myGame->p->currentMap-1]->map[posX][posY];
}

int findTargetXPos(game *myGame){
    assert(myGame);
    assert(myGame->p);
    assert(myGame->mapSet);
    assert(myGame->mapSet[myGame->p->currentMap-1]);

    int currentMapIndex = myGame->p->currentMap - 1;
    int posXPlayer = getXPlayerPos(myGame->mapSet[currentMapIndex]);

    int posXtarget = -1;

    if(posXPlayer < 0 || posXPlayer > myGame->mapSet[currentMapIndex]->rows)
        return -1;

    switch (myGame->p->direction)
    {
    case _NORTH_:
        posXtarget = posXPlayer - 1;
        return (posXtarget < 0) ? -1 : posXtarget;

    case _SOUTH_:
        posXtarget = posXPlayer + 1;
        return (posXtarget > myGame->mapSet[currentMapIndex]->rows) ? -1 : posXtarget;

    case _EAST_:
        return posXPlayer;
    case _WEST_:
        return posXPlayer;
    
    default:
        return posXtarget;
    }
}

int findTargetYPos(game *myGame){
    assert(myGame);
    assert(myGame->p);
    assert(myGame->mapSet);
    assert(myGame->mapSet[myGame->p->currentMap-1]);

    int currentMapIndex = myGame->p->currentMap - 1;
    int posYPlayer = getYPlayerPos(myGame->mapSet[currentMapIndex]);

    int posYtarget = -1;

    if(posYPlayer < 0 || posYPlayer > myGame->mapSet[currentMapIndex]->cols)
        return -1;

    switch (myGame->p->direction)
    {
    case _NORTH_:
        return posYPlayer;

    case _SOUTH_:
        return posYPlayer;

    case _EAST_:
        posYtarget = posYPlayer + 1;
        return (posYtarget > myGame->mapSet[currentMapIndex]->rows) ? -1 : posYtarget;
    case _WEST_:
        posYtarget = posYPlayer - 1;
        return (posYtarget > myGame->mapSet[currentMapIndex]->rows) ? -1 : posYtarget;
    
    default:
        return posYtarget;
    }
}


void farmResource(game *myGame, int caseValue, int posX, int posY){
    assert(myGame);
    assert(myGame->p);
    assert(myGame->mapSet);
    assert(myGame->mapSet[myGame->p->currentMap-1]);
    assert(myGame->p->inventory);
    
    int itmValue = 0;
    switch (caseValue)
    {
    case _PLANT_1_:
        itmValue = _HERBE_;
        break;
    case _ROC_1_:
        itmValue = _PIERRE_;
        break;
    case _BOIS_1_:
        itmValue = _SAPIN_;
        break;
    case _PLANT_2_:
        itmValue = _LAVANDE_;
        break;
    case _ROC_2_:
        itmValue = _FER_;
        break;
    case _BOIS_2_:
        itmValue = _HETRE_;
        break;
    case _PLANT_3_:
        itmValue = _CHANVRE_;
        break;
    case _ROC_3_:
        itmValue = _DIAMANT_;
        break;
    case _BOIS_3_:
        itmValue = _CHENE_;
        break;
    default:
        return;
    }

    int index = itemAlreadyPresent(myGame->p->inventory, itmValue);
    int indexTool = indexToolNeeded(myGame->p->inventory, itmValue);

    if(indexTool < 0 || indexTool > 9){
        return;
    }

    int nextDurability = findNextDurability(myGame->p->inventory[indexTool], itmValue);
    if(nextDurability < 0)
        return;
    myGame->p->inventory[indexTool]->durability = nextDurability;

    if(index < 0)
        addItem(myGame->p->inventory, itmValue);
    else{
        if(myGame->p->inventory[index]->quantity < 20){
            addItem(myGame->p->inventory, itmValue);
        }
    }
    myGame->mapSet[myGame->p->currentMap - 1]->map[posX][posY] = _FREE_CASE_;

}

void makeTp(game *myGame, int caseValue){
    assert(myGame);
    assert(myGame->mapSet);

    switch(myGame->p->currentMap){
        case 1 :
            if(myGame->p->level < myGame->mapSet[1]->lvlRequired){
                return;
            }
            myGame->mapSet[0]->map[myGame->p->posX][myGame->p->posY] = _FREE_CASE_;
            putPlayer(myGame->mapSet[1]);
            myGame->p->currentMap += 1;
            myGame->p->posX = getXPlayerPos(myGame->mapSet[1]);
            myGame->p->posY = getYPlayerPos(myGame->mapSet[1]);
            return;
        case 2 :
            switch(caseValue){
                case _TP_CASE_2_TO_1 :
                    myGame->mapSet[1]->map[myGame->p->posX][myGame->p->posY] = _FREE_CASE_;
                    putPlayer(myGame->mapSet[0]);
                    myGame->p->currentMap -= 1;
                    myGame->p->posX = getXPlayerPos(myGame->mapSet[0]);
                    myGame->p->posY = getYPlayerPos(myGame->mapSet[0]);
                    return;
                case _TP_CASE_2_TO_3 :
                    if(myGame->p->level < myGame->mapSet[2]->lvlRequired)
                        return;
                    myGame->mapSet[1]->map[myGame->p->posX][myGame->p->posY] = _FREE_CASE_;
                    putPlayer(myGame->mapSet[2]);
                    myGame->p->currentMap += 1;
                    myGame->p->posX = getXPlayerPos(myGame->mapSet[2]);
                    myGame->p->posY = getYPlayerPos(myGame->mapSet[2]);
                    return;
                default :
                    return;
                }
        case 3 :
            myGame->mapSet[2]->map[myGame->p->posX][myGame->p->posY] = _FREE_CASE_;
            putPlayer(myGame->mapSet[1]);
            myGame->p->currentMap -= 1;
            myGame->p->posX = getXPlayerPos(myGame->mapSet[1]);
            myGame->p->posY = getYPlayerPos(myGame->mapSet[1]);
            return;
        default :
            return;
    }
}

void makeAction(game *myGame){
    assert(myGame);
    int posX = findTargetXPos(myGame);
    int posY = findTargetYPos(myGame);
    if(posX == -1 || posY == -1)
        return;
    int caseValue = findTargetValueCase(myGame, posX, posY);
    if(caseValue == _INFRANCHISSABLE_)
        return;
    switch (findCaseType(caseValue))
    {
    case _IS_RESOURCE_:
        farmResource(myGame, caseValue, posX, posY);
        return;
    
    case _IS_TP_CASE_ :
        makeTp(myGame, caseValue);
        return;
    
    case _IS_MONSTER_CASE_ :
        //fight(myGame, posX, posY);
        return;

    case _PNJ_CASE_ :
        //dealWithPNJ(myGame);
        return;

    default:
        return;
    }
}

int caseValToItemVal(int caseValue){
    switch (caseValue)
    {
    case _PLANT_1_:
        return _HERBE_;
    case _PLANT_2_:
        return _LAVANDE_;
    case _PLANT_3_:
        return _CHANVRE_;
    case _ROC_1_:
        return _PIERRE_;
    case _ROC_2_:
        return _FER_;
    case _ROC_3_:
        return _DIAMANT_;
    case _BOIS_1_:
        return _SAPIN_;
    case _BOIS_2_:
        return _HETRE_;
    case _BOIS_3_:
        return _CHENE_;
    case _TP_CASE_1_TO_2:
        return _TP_CASE_1_TO_2;
    case _TP_CASE_2_TO_3 :
        return _TP_CASE_2_TO_3;
    case _FREE_CASE_:
        return _FREE_CASE_;
    case _INFRANCHISSABLE_:
        return _INFRANCHISSABLE_;
    default:
        if(findCaseType(caseValue) == _IS_MONSTER_CASE_)
            return _IS_MONSTER_CASE_;
        return _INFRANCHISSABLE_;
    }
}