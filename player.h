#include "malloc_world.h"
#include "direction.h"
#include "item.h"

#ifndef PLAYER_H
#define PLAYER_H
#endif

typedef struct player{
    // PLAYER STRUCT IS USED WHEN MAKING MOVE OR ANY ACTION TO UPDATE EACH ATTRIBUTE
    int level, currentHp, hp; // currentHp & hp ARE USED TO HAVE A 'currentHp'/'hp' INDEX (EX : 78 / 100 HP)
    // HP ATTRIBUTE CORRESPONDS WITH THE MAX HP WHICH THE PLAYER CAN HAVE
    int posX, posY;
    int currentMap;
    int direction;
    item **inventory;
    item **weaponSet;
    item *plastron;
}player;

// CREATE A NEW PLAYER
player *newPlayer(){
    player *p = malloc(sizeof(p));
    assert(p);
    p->level = 1;
    p->currentHp = 100;
    p->hp = 100; // MAX HP
    p->currentMap = 1;
    p->inventory = malloc(10*sizeof(item *) + 10*9*sizeof(int));
    p->inventory = initInventory();
    
    addItem(p->inventory, _PIOCHE_EN_BOIS_);
    addItem(p->inventory, _SERPE_EN_BOIS_);
    addItem(p->inventory, _HACHE_EN_BOIS_);
    
    p->direction = _SOUTH_;
    
    p->weaponSet = malloc(3*sizeof(item *) + 3*9*sizeof(int));
    p->weaponSet = initWeaponSet();
    addWeapon(p->weaponSet, _EPEE_EN_BOIS_);
    addWeapon(p->weaponSet, _HACHE_EN_PIERRE_);

    p->plastron = createItem(_ESPACE_LIBRE, 0);
    
    return p;
}

void freePlayer(player *p){
    assert(p);
    assert(p->weaponSet);
    assert(p->inventory);
    assert(p->plastron);
    freeWeaponSet(p->weaponSet);
    freeInventory(p->inventory);
    free(p->plastron);
    free(p);
}

/* void printPlayer(player *p){
    printf("                 ________________________\n");
    printf("                /                        \\\n");
    printf("                |      PLAYER STATS      |\n");
    printf("                |                        |\n");
    printf("                +------------------------+\n");
    printf("    \t\t| HP : %d/%d\n", p->currentHp, p->hp);
    printf("    \t\t| PLAYER LEVEL : %d\n", p->level);
    printf("    \t\t| POSITION :  [%d, %d]\n", p->posX, p->posY);
    printf("    \t\t| DIRECTION :  ");
    switch (p->direction)
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
    printf("    \t\t| CURRENT MAP : %d\n", p->currentMap);
    printf("                \\_______________________/\n");
}
*/

void printWeaponSet(player *p){
    printf("                 ___________________________________________________\n");
    printf("                /                                                   \\\n");
    printf("                |                    WEAPON SET                     |\n");
    printf("                |                                                   |\n");
    printf("                +---------------------------------------------------+\n");
    printf("                |                                                   |\n");
    printf("                |----+ [EMPLACEMENT]--[ARME]                        |\n");
    printf("                |    | SPECS                                        |\n");
    printf("                |    +-------------------------------------------+  |\n");
    printf("                +---------------------------------------------------+\n");
    printf("                |\n");

    for(int i=0; i<3; i++){
            printf("                +----+ [%d]--[", i);
            printResource(p->weaponSet[i]->value);  
            printf("]\n");
            if(p->weaponSet[i]->value != _ESPACE_LIBRE){
                printf("                |    | DURABILITY | DAMAGE |\n");
                printf("                |    |     %d     ", p->weaponSet[i]->durability);
                if(p->weaponSet[i]->durability < 10)
                    printf(" ");
                printf("| ");
                printf("  %d   ", p->weaponSet[i]->damage);
                if(p->weaponSet[i]->damage < 10)
                    printf(" ");
                printf("| ");

            }
            else
                printf("                |    |");
            printf("\n                |    +-------------------------------------------+\n");
    }
    printf("                \\___________________________________________________/\n");
}

void printInventory(player *p){
    printf("                 ___________________________________________________\n");
    printf("                /                                                   \\\n");
    printf("                |                     INVENTORY                     |\n");
    printf("                |                                                   |\n");
    printf("                +---------------------------------------------------+\n");
    printf("                |                                                   |\n");
    printf("                |----+ [EMPLACEMENT]--[ITEM]                        |\n");
    printf("                |    | SPECS                                        |\n");
    printf("                |    +-------------------------------------------+  |\n");
    printf("                +---------------------------------------------------+\n");
    printf("                |\n");

    for(int i=0; i<10; i++){
        printf("                +----+ [%d]--[", i);
        printResource(p->inventory[i]->value);  
        printf("]\n");
        if(p->inventory[i]->type != '0')
            printf("                |    | QTY |");
        else 
            printf("                |    |");
        switch (p->inventory[i]->type)
        {
        case 'w':
            printf("    TYPE     | DURABILITY | DAMAGE\n");
            printf("                |    |  %d ", p->inventory[i]->quantity);
            if(p->inventory[i]->quantity < 10)
                printf(" ");
            printf("| ");
             printf("   Weapon   |     %d     |    %d", p->inventory[i]->durability, p->inventory[i]->damage);
            break;

        case 't':
            printf("    TYPE     | DURABILITY\n");
            printf("                |    |  %d ", p->inventory[i]->quantity);
            if(p->inventory[i]->quantity < 10)
                printf(" ");
            printf("| ");
             printf("   Tool     |      %d", p->inventory[i]->durability);
            break;

        case 'r':
            printf("    TYPE     | MAX QUANTITY\n");
            printf("                |    |  %d ", p->inventory[i]->quantity);
            if(p->inventory[i]->quantity < 10)
                printf(" ");
            printf("| ");
             printf(" Resource   |       %d", p->inventory[i]->maxQuant);
            break;
        
        case 's':
            printf("    TYPE     | DAMAGE RESISTANCE\n");
            printf("                |    |  %d ", p->inventory[i]->quantity);
            if(p->inventory[i]->quantity < 10)
                printf(" ");
            printf("| ");
             printf("  Shield    |        %d%%", p->inventory[i]->dmgResist);
            break;

        case 'h':
            printf("    TYPE     | HP HEALED\n");
            printf("                |    |  %d ", p->inventory[i]->quantity);
            if(p->inventory[i]->quantity < 10)
                printf(" ");
            printf("| ");
             printf("   Heal     |     %dHP", p->inventory[i]->healPt);
            break;
        
        default:
            break;
        }
        //TYPE  | MAX QUANTITY | DURABILITY | DAMAGE | RESISTANCE | HP HEALED |\n");

        printf("\n");
        //if(i != 10){
            printf("                |    +-------------------------------------------+\n");
        //}
    }
    printf("                \\___________________________________________________/\n");

}