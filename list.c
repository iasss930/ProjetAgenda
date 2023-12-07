#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

// Créer une liste à niveau vide : on donnera le nombre maximal de niveaux que
// possède cette liste
t_d_list *create_list(int max_level) {
    t_d_list *list = malloc(sizeof(t_d_list));
    list->head = malloc(max_level * sizeof(t_d_cell *)); // aloue la mémoire
    for (int i = 0; i < max_level; i++) {
        list->head[i] = NULL; // met les pointeurs à null
    }
    list->max_level = max_level;
    return list;
}


// Insérer une cellule à niveaux en tête de liste
void insere_tete_list(t_d_list* list, t_d_cell* cell,int level){
        cell->next[level] = list->head[level];
        list->head[level]=cell;
}


// Affiche l’ensemble des cellules de la liste pour un niveau donné
void display_level(t_d_list list, int level){
    printf("[list head_%d @-]-->",level);
    t_d_cell* temp = list.head[level];
    while(temp!=NULL)
    {
        printf("[ %d|@-]-->",temp->value);
        temp=temp->next[level];
    }
    printf("NULL\n");
}


// Afficher tous les niveaux de la liste
void display_all(t_d_list *list){
    for (int i=0;i<list.max_level;i++)
    {
        display_level(list,i);
    }
}


// Insére une cellule à niveau dans la liste, au bon endroit, en maintenant la liste triée par ordre croissant
void insere_cell(t_d_list *list, t_d_cell *cell, int level){
    t_d_cell* temp = list->head[level];
    if (list->head[level] == NULL || temp->value > cell->value)
    {
        insere_tete_list(list, cell, level);
    }
    else
    {
        t_d_cell *prev = temp;
        while((temp->value < cell->value) && (temp->next[level] != NULL))
        {
            temp=temp->next[level];
        }
        if (temp->next[level] == NULL && temp->value < cell->value)
        {
            temp->next[level] = cell;
        }
        else
        {
            cell->next[level] = prev->next[level];
            prev->next[level] = cell;
        }
    }
}


int level_search(t_d_list *list, int value, int level){
    t_d_cell* researchcell = list.head[level];
    while(researchcell != NULL) {
        if (researchcell->value==val) {
            return 1;
        }
        researchcell = researchcell->next[level];
    }
    return 0;
}

int opti_research(t_d_list *list, int value){
    t_d_cell* temp;
    t_d_cell * prev;
    int j=list.max_level-1;
    temp = list.head[j];
    while (temp!=NULL)
    {
        if (temp->value == value)
        {
            return 1;
        }
        else if (temp->value >value && temp == list.head[j])
        {
            if(j>0){
                j--;
            }
            temp = list.head[j];
        }
        else if (value > temp->value)
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

