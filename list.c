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
    return list;
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
                printf("-->[ %3d|@-]", cell_lvl->value);
                cell_lvl = cell_lvl->next[i];
            }
            else{
                printf("--------");
            }
            cell0 = cell0->next[0];
        }
        printf("\n");
    }
    return;
}


void fill_list(t_d_list *list){
    int taille = 2;
    for (int i = 1; i <= list->max_level; i++) {
        taille = taille * 2;
    }
    taille -= 1;
    int tab[taille];
    for (int i = 0; i < taille; i++){
        tab[i] = 0;
    }
    for (int i = 0; i < list->max_level; i++){
        int pas = taille / (i+2);
        int indice = 0;
        for (int j = 1; j <= i + 1; i++){
            indice += pas;
            tab[indice] += 1;
        }
    }
    for(int i = 0; i < taille; i++){
        t_d_cell  *cell = create_cell(i + 1, list->max_level);
        insert_cell(list, cell, tab[i]);
    }
    return;
}


void insert_cell(t_d_list *list, t_d_cell *cell){
    int level;
    t_d_cell *cell0;
    cell0 = list->head[0];
    while (cell0->next[0] != NULL &&
           cell0->next[0]->value <
           cell->value) {
        cell0 = cell0->next[0];
    }
    cell->next[0] = cell0->next[0];
    cell0->next[0] = cell;
    int taille = 2;
    for (int i = 1; i <= list->max_level; i++) {
        taille = taille * 2;
    }
    taille -= 1;
    int tab[taille];
    for (int i = 0; i < taille; i++){
        tab[i] = 0;
    }
    for (int i = 0; i < list->max_level - 1; i++){
        int pas = taille / (i+2);
        int indice = 0;
        for (int j = 1; j <= i + 1; i++){
            indice += pas;
            tab[indice] += 1;
        }
    }
    t_d_cell *next = list->head[0];
    while(cell0->next != NULL){
        int indice = 0;
        for (int i = 1; i <= tab[indice]; i++){
            t_d_cell *prev = list->head[i];
            if (prev == NULL) {
                list->head[i] = next;
            }
            else {
                while (prev->next != NULL) {
                    prev = prev->next;
                }
                prev->next = next;
            }
        }
    }
}

int search(t_d_list list,int val, int lvl){
    t_d_cell* researchcell = list.head[lvl];
    while(researchcell!=NULL) {
        if (researchcell->value==val) {
            return 1;
        }
        researchcell = researchcell->next[lvl];
    }
    return 0;
}


int dicho_search(t_d_list list, int val){
    t_d_cell* temp;
    t_d_cell * prev;
    int j=list.max_level-1;
    temp = list.head[j];
    while (temp!=NULL)
    {
        if (temp->value == val)
        {
            return 1;
        }
        else if (temp->value >val && temp == list.head[j])
        {
            if(j>0){
                j--;
            }
            temp = list.head[j];
        }
        else if (val > temp->value)
        {
            prev=temp;
            if(j>0){
                j--;
            }
            temp = temp->next[j];
        }
        else
        {
            if(j>0){
                j--;
            }
            temp=prev->next[j];
        }
    }
    return 0;
}