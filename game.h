#include "lib.h"
#include "map.h"
#include "player.h"

// GAME CLASS CONTAINS THE FULL GAME MANAGING THANKS TO OTHER CLASSES (MAP, PLAYER, ...)
// WE CAN OPERATE ON EVERY ASPECTS OF THE GAME RIGHT HERE
// THE MAIN FUNCTION IN 'main.c' CALLS PRINCIPLY THE GAME FUNCTIONS 

typedef struct game{
    // GAME STRUCT IS DEFINED BY A PLAYER AND A MAPSET (TAB OF SEVERAL MAPS) => WE HAVE ALL THE MAPS CREATED AT THE CREATION OF A GAME (4 MAPS)
    player *p;
    map **mapSet;
    int nbOfMap;
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

// PRINTING FUNCTION FOR THE CURRENT GAME MAP AND THE PLAYER STATS
void printAll(game *myGame){
    assert(myGame);
    assert(myGame->p);
    assert(myGame->mapSet[myGame->p->currentMap-1]);
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

int indexToolNeeded(item **myInventory, int resourceValue){
    assert(myInventory);
    int index = -1;
    switch (resourceValue)
    {
    case _HERBE_:
        index = itemAlreadyPresent(myInventory, _SERPE_EN_BOIS_);
        index = index < 0 ? itemAlreadyPresent(myInventory, _SERPE_EN_PIERRE_) : index;
        index = index < 0 ? itemAlreadyPresent(myInventory, _SERPE_EN_FER_) : index;
        return index;

    case _PIERRE_:
        index = itemAlreadyPresent(myInventory, _PIOCHE_EN_BOIS_);
        index = index < 0 ? itemAlreadyPresent(myInventory, _PIOCHE_EN_PIERRE_) : index;
        index = index < 0 ? itemAlreadyPresent(myInventory, _PIOCHE_EN_FER_) : index;
        return index;

    case _SAPIN_:
        index = itemAlreadyPresent(myInventory, _HACHE_EN_BOIS_);
        index = index < 0 ? itemAlreadyPresent(myInventory, _HACHE_EN_PIERRE_) : index;
        index = index < 0 ? itemAlreadyPresent(myInventory, _HACHE_EN_FER_) : index;
        return index;

    case _LAVANDE_:
        index = itemAlreadyPresent(myInventory, _SERPE_EN_PIERRE_);
        index = index < 0 ? itemAlreadyPresent(myInventory, _SERPE_EN_FER_) : index;
        return index;

    case _FER_:
        index = itemAlreadyPresent(myInventory, _PIOCHE_EN_PIERRE_);
        index = index < 0 ? itemAlreadyPresent(myInventory, _PIOCHE_EN_FER_) : index;
        return index;

    case _HETRE_:
        index = itemAlreadyPresent(myInventory, _HACHE_EN_PIERRE_);
        index = index < 0 ? itemAlreadyPresent(myInventory, _HACHE_EN_FER_) : index;
        return index;

    case _CHANVRE_:
        index = itemAlreadyPresent(myInventory, _SERPE_EN_FER_);
        return index;

    case _DIAMANT_:
        index = itemAlreadyPresent(myInventory, _PIOCHE_EN_FER_);
        return index;

    case _CHENE_:
        index = itemAlreadyPresent(myInventory, _HACHE_EN_FER_);
        return index;
        
    
    default:
        return index;
    }
    return index;
}

int findNextDurability(item *tool, int resourceValue){
    if(resourceValue == _PIERRE_ || resourceValue == _SAPIN_ || resourceValue == _HERBE_){
        return (tool->durability - ( (tool->maxDurability) / 10));
    }

    if(resourceValue == _FER_ || resourceValue == _HETRE_ || resourceValue == _LAVANDE_){
        return (tool->durability - ( (tool->maxDurability) /10) * 2);
    }

    if(resourceValue == _DIAMANT_ || resourceValue == _CHENE_ || resourceValue == _CHANVRE_){
        return (tool->durability - ( (tool->maxDurability) / 10) * 4);
    }
    return -1;
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

    if(index < 0){
        addItem(myGame->p->inventory, itmValue);
    }

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