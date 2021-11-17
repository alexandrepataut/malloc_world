#include "lib.h"

#ifndef _TP_CASE_2_TO_3
#define _TP_CASE_2_TO_3 -3
#endif
#ifndef _TP_CASE_3_TO_2 
#define _TP_CASE_3_TO_2 -3
#endif
#ifndef _TP_CASE_1_TO_2
#define _TP_CASE_1_TO_2 -2
#endif
#ifndef _TP_CASE_2_TO_1
#define _TP_CASE_2_TO_1  -2
#endif
#ifndef _INFRANCHISSABLE_
#define _INFRANCHISSABLE_  -1
#endif
#ifndef _FREE_CASE_ 
#define _FREE_CASE_ 0
#endif
#ifndef _PLAYER_
#define _PLAYER_ 1
#endif
#ifndef _PNJ_CASE_
#define _PNJ_CASE_ 2
#endif
#ifndef _PLANT_1_
#define _PLANT_1_ 3
#endif
#ifndef _ROC_1_
#define _ROC_1_ 4
#endif
#ifndef _BOIS_1_
#define _BOIS_1_ 5
#endif
#ifndef _PLANT_2_
#define _PLANT_2_ 6
#endif
#ifndef _ROC_2_
#define _ROC_2_ 7
#endif
#ifndef _BOIS_2_
#define _BOIS_2_ 8
#endif
#ifndef _PLANT_3_
#define _PLANT_3_ 9
#endif
#ifndef _ROC_3_
#define _ROC_3_ 10
#endif
#ifndef _BOIS_3_
#define _BOIS_3_ 11
#endif
#ifndef _MIN_MONSTER_1_
#define _MIN_MONSTER_1_ 12
#endif
#ifndef _MAX_MONSTER_1_
#define _MAX_MONSTER_1_ 44
#endif
#ifndef _MIN_MONSTER_2_
#define _MIN_MONSTER_2_ 45
#endif
#ifndef _MAX_MONSTER_2_
#define _MAX_MONSTER_2_ 69
#endif
#ifndef _MIN_MONSTER_3_
#define _MIN_MONSTER_3_ 70
#endif
#ifndef _MAX_MONSTER_3_
#define _MAX_MONSTER_3_ 98
#endif
#ifndef _BOSS_
#define _BOSS_ 99
#endif

#ifndef _IS_RESOURCE_
#define _IS_RESOURCE_ 100
#endif
#ifndef _IS_TP_CASE_
#define _IS_TP_CASE_ 101
#endif
#ifndef _IS_MONSTER_CASE_
#define _IS_MONSTER_CASE_ 102
#endif

typedef struct map
{
    int **map;
    int rank;
    int rows, cols;
    int nbTrees, nbMonsters, nbPlants, nbRocs;
    int treeVal, plantVal, rocVal;
    int lvlRequired;
}map;

void freeMap(map *myMap){
    assert(myMap);
    free(myMap->map);
    free(myMap);
}

void freeMapSet(map **myMapSet, int nbOfMaps){
    assert(myMapSet);
    for(int i=0; i<nbOfMaps; i++){
        assert(myMapSet[i]);
        freeMap(myMapSet[i]);
    }
    free(myMapSet);
}

// GETTERS FOR PLAYER POSITION
int getXPlayerPos(map *myMap){
    for(int i = 0; i < myMap->rows; i++){
        for(int j = 0; j < myMap->cols; j++){
            if(myMap->map[i][j] == 1) {
                return i;
            }
        }
    }
    return 0;
}
int getYPlayerPos(map *myMap){
    for(int i = 0; i < myMap->rows; i++){
        for(int j = 0; j < myMap->cols; j++){
            if(myMap->map[i][j] == 1) {
                return j;
            }
        }
    }
    return 0;
}

void putTrees(map *myMap){
    int nbTrees, x, y, i, val;
    // NUMBER OF TREES DEPENDS ON THE RANK OF THE MAP
    nbTrees = myMap->nbTrees;
    val = 1 ? 5 : (myMap->rank == 2 ? 8 : 11);
    i = 0;

    while(i<nbTrees){
        // RANDOM POSITION ON MAP
        x = rand()%(myMap->rows);
        y = rand()%(myMap->cols);
        

        if(myMap->map[x][y]==0){
            // PUT TREE VALUE ON THE [X, Y] RANDOM POSITION GENERATED
            // ONLY IF THE MAP[X, Y] CASE IS FREE
            myMap->map[x][y] = val;
            i++;
        }
    }
}

void putMonsters(map *myMap){
    int nbMonsters, x, y, i, min_val, max_val, randMonster;
    // NUMBER OF MONSTERS DEPENDS ON THE RANK OF THE MAP
    nbMonsters = myMap->nbMonsters;
    i = 0;
    // MONSTER LEVELS DEPENDS ON THE CURRENT RANK OF THE MAP [MAP 1 : 12-44] [MAP 2 : 45-69] [MAP 3 : 70-98]
    // BOSS MONSTER IS AN EXCEPTION WITH VALUE 99
    min_val = myMap->rank == 1 ? 12 : (myMap->rank == 2 ? 45 : 70);
    max_val = myMap->rank == 1 ? 44 : (myMap->rank == 2 ? 69 : 98);

    while(i<nbMonsters){
        // RANDOM POSITION ON MAP
        x = rand()%(myMap->rows);
        y = rand()%(myMap->cols);

        // GENERATE A RANDOM MONSTER VALUE DEPENDING ON PREVIOUS CALCULATED VALUES
        randMonster = (rand()%(max_val - min_val +1)) + min_val;

        if(myMap->map[x][y] == 0){
            // PUT MONSTER VALUE ON THE [X, Y] RANDOM POSITION GENERATED
            // ONLY IF THE MAP[X, Y] CASE IS FREE
            myMap->map[x][y] = randMonster;
            i++;
        }
    }
}

void putPlants(map *myMap){
    int nbPlants, x, y, i, val;
    // NUMBER OF PLANTS DEPENDS ON THE RANK OF THE MAP
    nbPlants = myMap->nbPlants;
    val = myMap->rank == 1 ? 3 : (myMap->rank == 6 ? 8 : 9);
    i = 0;

    while(i<nbPlants){
        // RANDOM POSITION ON MAP
        x = rand()%(myMap->rows);
        y = rand()%(myMap->cols);
        

        if(myMap->map[x][y] == 0){
            // PUT PLANT VALUE ON THE [X, Y] RANDOM POSITION GENERATED
            // ONLY IF THE MAP[X, Y] CASE IS FREE
            myMap->map[x][y] = val;
            i++;
        }
    }
}

int getNbTpCases(map *myMap){
    int nbTpCases = 0;
    if(myMap->rank == 1){
        for(int i=0; i<myMap->rows; i++){
            for(int j=0; j<myMap->cols; j++){
                if(myMap->map[i][j] == -2)
                    nbTpCases += 1;
            }
        }
    }

    if(myMap->rank == 2){
        for(int i=0; i<myMap->rows; i++){
            for(int j=0; j<myMap->cols; j++){
                if(myMap->map[i][j] == -2 || myMap->map[i][j] == -3)
                    nbTpCases += 1;
            }
        }
    }

    if(myMap->rank == 3){
        for(int i=0; i<myMap->rows; i++){
            for(int j=0; j<myMap->cols; j++){
                if(myMap->map[i][j] == -3)
                    nbTpCases += 1;
            }
        }
    }

    return nbTpCases;
}

void putTpCases(map *myMap){
    int x, y;

    if(myMap->rank == 1){
        while(getNbTpCases(myMap) != 1){
            x = rand()%(myMap->rows);
            y = rand()%(myMap->cols);
            if(myMap->map[x][y] == _FREE_CASE_)
                myMap->map[x][y] = _TP_CASE_1_TO_2;
        }
    }

    if(myMap->rank == 3){
        while(getNbTpCases(myMap) != 1){
            x = rand()%(myMap->rows);
            y = rand()%(myMap->cols);
            if(myMap->map[x][y] == _FREE_CASE_)
                myMap->map[x][y] = _TP_CASE_3_TO_2;
        }
    }

    if(myMap->rank == 2){
        int tp_2_to_1 = 0;
        int tp_2_to_3 = 0;
        while(getNbTpCases(myMap) != 2){
            x = rand()%(myMap->rows);
            y = rand()%(myMap->cols);
            if(myMap->map[x][y] == _FREE_CASE_ && tp_2_to_1 == 0){
                myMap->map[x][y] = _TP_CASE_2_TO_1;
                tp_2_to_1 = 1;
            }
            x = rand()%(myMap->rows);
            y = rand()%(myMap->cols);
            if(myMap->map[x][y] == _FREE_CASE_ && tp_2_to_3 == 0){
                myMap->map[x][y] = _TP_CASE_2_TO_3;
                tp_2_to_3 = 1;
            }
        }
    }
}

void putRocs(map *myMap){
    int nbRocs, x, y, i, val;
    // NUMBER OF ROCS DEPENDS ON THE RANK OF THE MAP
    nbRocs = myMap->nbPlants;
    val = myMap->rank == 1 ? 4 : (myMap->rank == 2 ? 7 : 10);
    i = 0;

    while(i<nbRocs){
        // RANDOM POSITION ON MAP
        x = rand()%(myMap->rows);
        y = rand()%(myMap->cols);
        

        if(myMap->map[x][y] == 0){
            // PUT ROC VALUE ON THE [X, Y] RANDOM POSITION GENERATED
            // ONLY IF THE MAP[X, Y] CASE IS FREE
            myMap->map[x][y] = val;
            i++;
        }
    }
}

void putPnj(map *myMap){
    int i, x, y;
    i = 0;

    while(i<1){
        x = rand()%(myMap->rows);
        y = rand()%(myMap->cols);
        // PUT PNJ VALUE ON THE [X, Y] RANDOM POSITION GENERATED
        // ONLY IF THE MAP[X, Y] CASE IS FREE
        if(myMap->map[x][y] == _FREE_CASE_){
            myMap->map[x][y] = 2;
            i++;
        }
    }
}

void putPlayer(map *myMap){
    int i, x, y;
    i = 0;

    while(i<1){
        x = rand()%(myMap->rows);
        y = rand()%(myMap->cols);
        // PUT PLAYER VALUE ON THE [X, Y] RANDOM POSITION GENERATED
        // ONLY IF THE MAP[X, Y] CASE IS FREE
        if(myMap->map[x][y] == _FREE_CASE_){
            myMap->map[x][y] = 1;
            i++;
        }
    }
}

void putAll(map *myMap){
    putTrees(myMap);
    putPlants(myMap);
    putRocs(myMap);
    putMonsters(myMap);
    putTpCases(myMap);
    putPnj(myMap);
}

map *initMap(int l, int c, int rank){
    // CREATING MAP TAB OF TABS ALLOCATING INT TAB FIRSTLY ...
    map *myMap = malloc(sizeof(myMap));
    assert(myMap);
    myMap->map = malloc(l*sizeof(int *));
    assert(myMap->map);
    myMap->rows = l;
    myMap->cols = c;
    myMap->rank = rank;
    // NUMBER OF EACH RESOURCE (TREES, PLANTS, MONSTERS, ROCS) DEPENDS ON THE RANK OF THE MAP
    myMap->nbTrees = 3 + 4 * rank;
    myMap->nbMonsters = 10 + 3 * rank;
    myMap->nbRocs = 3 + 4 * rank;
    myMap->nbPlants = 3 + 4 * rank;
    // TREE VALUE ON MAP DEPENDS ON THE RANK OF THE MAP [MAP 1 : 5] [MAP 2 : 8] [MAP 3 : 11]
    myMap->treeVal = myMap->rank == 1 ? 5 : (myMap->rank == 2 ? 8 : 11);
    // PLANT VALUE ON MAP DEPENDS ON THE RANK OF THE MAP [MAP 1 : 3] [MAP 2 : 6] [MAP 3 : 9]
    myMap->plantVal = myMap->rank == 1 ? 3 : (myMap->rank == 6 ? 8 : 9);
    // ROC VALUE ON MAP DEPENDS ON THE RANK OF THE MAP [MAP 1 : 4] [MAP 2 : 7] [MAP 3 : 10]
    myMap->rocVal = myMap->rank == 1 ? 4 : (myMap->rank == 2 ? 7 : 10);
    myMap->lvlRequired = rank == 1 ? 0 : (rank == 2 ? 3 : 7);

    for(int i=0; i<myMap->rows; i++){
        // ALLOCATING TABS OF MAP FOR EACH ROW
        myMap->map[i] = malloc(c*sizeof(int));
        assert(myMap->map[i]);
        // INITIALIZING EACH CASE TO '0' VALUE
        for(int j=0; j<myMap->cols; j++){
            myMap->map[i][j] = 0;
        }
    }
    // PUT EVERY RESOURCES ON THE BLANK MAP
    putAll(myMap);
    return myMap;
}

void printMap(map *myMap){
    int isPlayer = 0;
    if (myMap->rank == 1){
        printf("                __________________________\n");
        printf("               /                          \\\n");
        printf("               |           MAP %d          |\n", myMap->rank);        
        printf("               |                          |\n");
        printf("               +--------------------------+\n");
        printf("               |                          |\n");
        for(int i=0; i<myMap->rows; i++){
            printf("               |  ");
            for(int j=0; j<myMap->cols; j++){
                printf("%d ", myMap->map[i][j]);
                if(myMap->map[i][j] / 10 == 0 && myMap->map[i][j] > -1){
                    printf(" ");
                }
                if(myMap->map[i][j] == 1 && isPlayer == 0){
                    isPlayer = 1;
                }
            }
            printf("|");
            if(isPlayer == 1){
                printf(" <- Player is on this line");
                isPlayer = 0;
            }
            printf("\n");
        }
        printf("               |                          |\n");
        printf("               \\__________________________/\n");
        return;
    }

    if (myMap->rank == 2){
        printf("                ______________________________________\n");
        printf("               /                                      \\\n");
        printf("               |                 MAP %d                |\n", myMap->rank);
        printf("               |                                      |\n");
        printf("               +--------------------------------------+\n");
        printf("               |                                      |\n");
        for(int i=0; i<myMap->rows; i++){
            printf("               |  ");
            for(int j=0; j<myMap->cols; j++){
                printf("%d ", myMap->map[i][j]);
                if(myMap->map[i][j] / 10 == 0 && myMap->map[i][j] > -1){
                    printf(" ");
                }
                if(myMap->map[i][j] == 1 && isPlayer == 0){
                    isPlayer = 1;
                }
            }
            printf("|");
            if(isPlayer == 1){
                printf(" <- Player is on this line");
                isPlayer = 0;
            }
            printf("\n");
        }
        printf("               |                                      |\n");
        printf("               \\______________________________________/\n");
        return;
    }

    if (myMap->rank == 3){
        printf("                _______________________________________________\n");
        printf("               /                                               \\\n");
        printf("               |                     MAP %d                     |\n", myMap->rank);
        printf("               |                                               |\n");
        printf("               +-----------------------------------------------+\n");
        printf("               |                                               |\n");
        for(int i=0; i<myMap->rows; i++){
            printf("               |  ");
            for(int j=0; j<myMap->cols; j++){
                printf("%d ", myMap->map[i][j]);
                if(myMap->map[i][j] / 10 == 0 && myMap->map[i][j] > -1){
                    printf(" ");
                }
                if(myMap->map[i][j] == 1 && isPlayer == 0){
                    isPlayer = 1;
                }
            }
            printf("|");
            if(isPlayer == 1){
                printf(" <- Player is on this line");
                isPlayer = 0;
            }
            printf("\n");
        }
        printf("               |                                               |\n");
        printf("               \\_______________________________________________/\n");
        return;
    }
}

int findCaseType(int value) {
    if(value < _TP_CASE_2_TO_3 && value > _BOSS_)
        return value;

    switch (value)
    {
    case _TP_CASE_2_TO_3:
        return _IS_TP_CASE_;
    case _TP_CASE_1_TO_2:
        return _IS_TP_CASE_;
    case _INFRANCHISSABLE_:
        return _INFRANCHISSABLE_;
    case _FREE_CASE_:
        return _FREE_CASE_;
    case _PLANT_1_:
        return _IS_RESOURCE_;
    case _ROC_1_:
        return _IS_RESOURCE_;
    case _BOIS_1_:
        return _IS_RESOURCE_;
    case _PLANT_2_:
        return _IS_RESOURCE_;
    case _ROC_2_:
        return _IS_RESOURCE_;
    case _BOIS_2_:
        return _IS_RESOURCE_;
    case _PLANT_3_:
        return _IS_RESOURCE_;
    case _ROC_3_:
        return _IS_RESOURCE_;
    case _BOIS_3_:
        return _IS_RESOURCE_;
    case _BOSS_:
        return _BOSS_;
    default:
        return _IS_MONSTER_CASE_;
    }
}


