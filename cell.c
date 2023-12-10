#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.h"

t_d_cell *create_cell(int value, int n_levels) {
    t_d_cell *cell = malloc(sizeof(t_d_cell)); // alloue de la mémoire
    cell->value = value;        // cell pointe value qui prendra la valeur
    cell->next = malloc(n_levels * sizeof(t_d_cell *)); // alloue la mémoire des pointeurs suivants
    for (int i = 0; i < n_levels; i++) {
        cell->next[i] = NULL; // les pointeurs pointe à null
    }
    return cell;
}