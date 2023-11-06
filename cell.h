//
// Created by Yannis on 06/11/2023.
//

#ifndef PROJETAGENDA_CELL_H
#define PROJETAGENDA_CELL_H


// Définition des types
typedef struct s_cell
{
    void* value;
    struct s_cell * next;
} t_cell, *p_cell;

typedef struct s_lvl_cell
{
    int value;
    void * next;
} t_lvl_cell;


// Fonctions associées
p_cell createCell(void*);

#endif //PROJETAGENDA_CELL_H
