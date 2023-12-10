
#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H

#include "cell.h"

typedef struct s_d_list {
    t_d_cell **head;
    int max_level;
} t_d_list;


t_d_list *create_list(int);
void insert_tete(t_d_list *, t_d_cell *, int);
void display_level(t_d_list, int);
void display_all(t_d_list);
void insert_cell(t_d_list *, t_d_cell *, int);
void fill_list(t_d_list *);