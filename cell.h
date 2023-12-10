
#ifndef UNTITLED_CELL_H
#define UNTITLED_CELL_H


typedef struct s_d_cell {
    int value;
    struct s_d_cell **next;
} t_d_cell;

t_d_cell *create_cell(int, int);

#endif