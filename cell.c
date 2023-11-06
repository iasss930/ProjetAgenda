//
// Created by Yannis on 06/11/2023.
//

#include <stdlib.h>
#include "cell.h"

/// Crée une cellule contenant l'élément passé en argument.
/// @param element L'élément que contiendra la cellule.
/// @return Retourne un pointeur sur la cellule créée.
p_cell createCell(void* element)
{
    p_cell myCell = (p_cell) malloc(sizeof(t_cell));

    myCell->value = element;
    myCell->next = NULL;

    return myCell;
}