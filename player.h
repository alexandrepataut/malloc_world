#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <assert.h>

typedef struct player{
    // PLAYER STRUCT IS USED WHEN MAKING MOVE OR ANY ACTION TO UPDATE EACH ATTRIBUTE
    int level, currentHp, hp; // currentHp & hp ARE USED TO HAVE A 'currentHp'/'hp' INDEX (EX : 78 / 100 HP)
    // HP ATTRIBUTE CORRESPONDS WITH THE MAX HP WHICH THE PLAYER CAN HAVE
    int posX, posY;
    int currentMap;
}player;

// CREATE A NEW PLAYER
player *newPlayer(){
    player *p = malloc(sizeof(p));
    assert(p);
    p->level = 1;
    p->currentHp = 100;
    p->hp = 100; // MAX HP
    p->currentMap = 1;
    return p; 
}

// PRINTING FUNCTION FOR PLAYER STATS
void printPlayer(player *p){
    printf("                 ________________________\n");
    printf("                /                        \\\n");
    printf("                |      PLAYER STATS      |\n");
    printf("                |                        |\n");
    printf("                +------------------------+\n");
    printf("    \t\t| HP : %d/%d\n", p->currentHp, p->hp);
    printf("    \t\t| PLAYER LEVEL : %d\n", p->level);
    printf("    \t\t| POSITION :  [%d, %d]\n", p->posX, p->posY);
    printf("    \t\t| CURRENT MAP : %d\n", p->currentMap);
    printf("                \\_______________________/\n");
}