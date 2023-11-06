//
// Created by Yannis on 06/11/2023.
//

#ifndef PROJETAGENDA_LIST_H
#define PROJETAGENDA_LIST_H

#include "cell.h"


// Définition des types
typedef struct s_ht_list
{
    p_cell head;
    p_cell tail;
} t_ht_list, *p_ht_list;

typedef struct s_lvl_list
{
    void * heads;
    int max_level;
} t_lvl_list;


// Fonctions associées
t_ht_list * createEmptyHtList();


#endif //PROJETAGENDA_LIST_H
