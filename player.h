#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <assert.h>

typedef struct player{
    int level, currentHp, hp;
    int posX, posY;
    int currentMap;
}player;

player *newPlayer(){
    player *p = malloc(sizeof(p));
    p->level = 1;
    p->currentHp = 100;
    p->hp = 100;
    p->currentMap = 1;
    return p; 
}

void printPlayer(player *p){
    printf("-------------------------------------------------\n");
    printf("|\t\tPLAYER STATS\t\t\t|\n");
    printf("-------------------------------------------------\n");
    printf("|\t\tHP : %d/%d\t\t\t|\n", p->currentHp, p->hp);
    printf("|\t\tPLAYER LEVEL : %d\t\t|\n", p->level);
    printf("|\t\tPOSITION :  [%d, %d]\t\t|\n", p->posX, p->posY);
    printf("|\t\tCURRENT MAP : %d\t\t\t|\n", p->currentMap);
    printf("-------------------------------------------------\n");
}