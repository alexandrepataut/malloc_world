#include "malloc_world.h"
#include "resource.h"

#ifndef ITEM_H
#define ITEM_H
#endif

typedef struct item{
    int value;
    int quantity;
    char type;
    int durability;
    int damage;
    int maxQuant;
    int dmgResist;
    int healPt;
    int maxDurability;
}item;

void printItem(item *itm);

item *createItem(int value, int qty){
    item *itm = malloc(sizeof(itm)+9*sizeof(int));
    assert(itm);
    itm->value = value;
    itm->quantity = qty;
    itm->type = findType(value);
    itm->durability     = itm->type == 'w' || itm->type == 't' ? findDurability(value) : 0;
    itm->maxDurability  = itm->durability;
    itm->damage         = itm->type == 'w' ? findDamage(value) : 0;
    itm->maxQuant       = itm->type == 'r' ? 20 : 0;
    itm->dmgResist      = itm->type == 's' ? findDmgResist(value) : 0;
    itm->healPt         = itm->type == 'h' ? findHealPt(value) : 0;

    return itm;
}

void freeItem(item *itm){
    assert(itm);
    free(itm);
}

item **initInventory(){
    item **myInventory = malloc(10*sizeof(item *)+10*9*sizeof(int));
    assert(myInventory);
    
    for(int i=0; i<10; i++){
        myInventory[i] = malloc(sizeof(item *));
        myInventory[i] = createItem(0, 0);
        assert(myInventory[i]);
    }
    myInventory[0]->type = '0';
    myInventory[0]->value = 0;

    return myInventory;
}

void freeInventory(item **myInventory){
    assert(myInventory);
    for(int i=0; i<10; i++){
        assert(myInventory[i]);
        free(myInventory[i]);
    }
    free(myInventory);
}

void printItem(item *itm){
    assert(itm);
    printf("%d\t", itm->quantity);
    printResource(itm->value);
    printf("\n");
    switch (itm->type)
    {
    case 'w':
        printf("ARME\n\tDEGATS : %d\n\tDURABILITE : %d", itm->damage, itm->durability);
        break;
    case 't':
        printf("OUTIL\n\tDURABILITE : %d", itm->durability);
        break;
    case 's':
        printf("ARMURE\n\tRESISTANCE : %d%% REDUCTION DES DEGATS", itm->dmgResist);
        break;
    case 'h':
        printf("HP RESTAURES : %dHP", itm->healPt);
        break;
    case 'r':
        printf("RESSOURCE\n\tQUANTITE MAX : %d", itm->maxQuant);
        break;
    
    default:
        break;
    }
    printf("\n");
}

int itemAlreadyPresent(item **myInventory, int value){
    assert(myInventory);
    for(int i=0; i<10; i++){
        assert(myInventory[i]);
        if(myInventory[i]->value == value){
            return i;
        }
    }
    return -1;
}

void addItem(item **myInventory, int value){
    assert(myInventory);
    int index = itemAlreadyPresent(myInventory, value);
    if(index == -1){
        for(int i=0; i<10; i++){
            assert(myInventory[i]);
            if(myInventory[i]->type == '0'){
                free(myInventory[i]);
                myInventory[i] = malloc(sizeof(item));
                assert(myInventory[i]);
                myInventory[i] = createItem(value, 1);
                assert(myInventory[i]);
                return;
            }
        }
    } else {
        if(index > -1 && index < 10 && findType(value) == 'r'){
            assert(myInventory[index]);
            if(findType(value))
                myInventory[index]->quantity += 1;
        }
        return;
    }
}

void delItem(item** myInventory, int index){
    assert(myInventory);
    if(myInventory[index]->quantity != 1 && myInventory[index]->quantity > 0){
        assert(myInventory[index]);
        myInventory[index]->quantity -= 1;
        return;
    } else {
        free(myInventory[index]);
        myInventory[index] = createItem(_ESPACE_LIBRE, 0);
        assert(myInventory[index]);
        return;
    }
}

void reduceQuantity(item **myInventory, int value, int quantity){
    assert(myInventory);
    int index = itemAlreadyPresent(myInventory, value);
    if(index > -1){
        assert(myInventory[index]);
        if(myInventory[index]->quantity >= quantity){
            myInventory[index]->quantity -= quantity;
        }
        if(myInventory[index]->quantity == 0){
            delItem(myInventory, index);
        }
    }
}

void freeWeaponSet(item **myWeaponSet){
    assert(myWeaponSet);
    for(int i=0; i<3; i++){
        assert(myWeaponSet[i]);
        free(myWeaponSet[i]);
    }
    free(myWeaponSet);
}

item **initWeaponSet(){
    item **myWeaponSet = malloc(3*sizeof(item *) + 3*9*sizeof(int));
    assert(myWeaponSet);
    for(int i=0; i<3; i++){
        myWeaponSet[i] = malloc(sizeof(item *));
        myWeaponSet[i] = createItem(0, 0);
        assert(myWeaponSet[i]);
    }
    return myWeaponSet;
}

void addWeapon(item **myWeaponSet, int value){
    assert(myWeaponSet);
    if(findType(value) != 'w')
        return;
    for(int i=0; i<3; i++){
        if(myWeaponSet[i]->value == _ESPACE_LIBRE){
            free(myWeaponSet[i]);
            myWeaponSet[i] = malloc(sizeof(item));
            assert(myWeaponSet[i]);
            myWeaponSet[i] = createItem(value, 1);
            assert(myWeaponSet[i]);
            return;
        }
    }
}

void equipWeaponFromInventory(item **myWeaponSet, item **myInventory, int value, int durability){
    assert(myWeaponSet);
    int index = itemAlreadyPresent(myInventory, value);
    if(index < 0 || index > 10)
        return;
    for(int i=0; i<3; i++){
        if(myWeaponSet[i]->value == _ESPACE_LIBRE){
            myWeaponSet[i] = createItem(value, 1);
            myWeaponSet[i]->durability = durability;
            delItem(myInventory, index);
            return;
        }
    }
}

void delWeapon(item **myWeaponSet, int index){

    assert(myWeaponSet);
    free(myWeaponSet[index]);
    myWeaponSet[index] = createItem(_ESPACE_LIBRE, 0);
    assert(myWeaponSet[index]);
    return;
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