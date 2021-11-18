#include "malloc_world.h"

#ifndef CASE_VALUES_H
#define CASE_VALUES_H
#endif

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