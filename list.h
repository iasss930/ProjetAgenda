
#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H

#include "cell.h"

// structure à n niveau pour un tableau de n ligne avec une valeur max et un
// tableau de pointeur
typedef struct s_d_list {
    t_d_cell **head;
    int max_level;
} t_d_list;

t_d_list *create_list(int);
void insere_tete_list(t_d_list *, t_d_cell *, int);
void insere_cell(t_d_list *, t_d_cell *, int);
void display_level(t_d_list *, int);
void display_all(t_d_list *);
int level_search(t_d_list *, int, int);
int opti_research(t_d_list *, int, int);

#endif