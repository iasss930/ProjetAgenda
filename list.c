//
// Created by Yannis on 06/11/2023.
//

#include <stdlib.h>
#include "list.h"

/// Permet d'initialiser une liste head-tail vide.
/// @return Un pointeur vers la nouvelle liste créée.
t_ht_list * createEmptyHtList()
{
    t_ht_list *myHtList = (p_ht_list) malloc(sizeof(t_ht_list));

    myHtList->head = NULL;
    myHtList->tail = NULL;

    return myHtList;
}
