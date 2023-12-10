#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"


t_d_list *create_list(int lvl){
    t_d_list *list = malloc(sizeof(t_d_list));
    list->max_level = lvl;
    list->head = malloc(lvl * sizeof(t_d_cell*));
    for (int i = 0; i < lvl; i++){
        list->head[i] = NULL;
    }
    return list
}


void insert_tete(t_d_list *list, t_d_cell *cell, int lvl){
    for(int i = 0; i <= lvl; i++){
        cell->next[i] = list->head[i];
        list->head[i] = cell;
    }
}


void display_level(t_d_list list, int lvl){
    printf("[list head_%2d @-]-->",lvl);
    t_d_cell* cell = list.head[lvl];
    while(cell!=NULL)
    {
        printf("[%3d|@-]-->",cell->value);
        cell = cell->next[lvl];
    }
    printf("NULL\n");
    return;
}


void display_all(t_d_list list){
    for(int i = 0; i < list.max_level; i++){
        printf("[list head_%2d @-]", i);
        t_d_cell *cell0 = list.head[0];
        t_d_cell *cell_lvl = list.head[i];
        while(cell0 != NULL){
            if (cell_lvl == cell0){
                printf("-->[ %3d|@-]"; cell_lvl.value);
                cell_lvl = cell_lvl->next[i];
            }
            else{
                printf("--------");
            }
            cell0 = cell0->next[0];
        }
    }
    return;
}


void insert_cell(t_d_list *list, t_d_cell *cell, int lvl){
    t_d_cell* temp = list->head[lvl];
    if (temp == NULL || temp->value > cell->value){
        insert_tete(list, cell, lvl);
    }
    else {
        for int(i = 0; i <= lvl){
            t_d_cell *prev = temp;
            while ((temp->value < cell->value) && (temp->next[lvl] != NULL)) {
                temp = temp->next[lvl];
            }
            if (temp->next[lvl] == NULL && temp->value < cell->value) {
                temp->next[lvl] = cell;
            } else {
                cell->next[lvl] = prev->next[lvl];
                prev->next[lvl] = cell;
            }
        }
    }
    return;
}


void fill_list(t_d_list *list){
    int taille = 2;
    for (int i = 1; i <= list->max_level; i++) {
        taille = taille * 2;
    }
    taille -= 1;
    int *tab[taille] = [0];
    for (int i = 0; i < taille; i++){
        int pas = taille / (i+2);
        int indice = 0;
        for (int j = 1; j <= i + 1; i++){
            indice += pas;
            tab[indice] += 1;
        }
    }
    for(int i = 0; i < taille; i++){
        t_d_cell  *cell = create_cell(i + 1, list->max_level);
        insert_cell(list, cell, *tab[i]);
    }
    return;
}