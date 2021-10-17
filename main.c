#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <assert.h>
#include "map.h"

int main() {
    unsigned int l, c;
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
    printMap(myMap3);

    return 0;
}