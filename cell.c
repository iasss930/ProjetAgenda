#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.h"

// Créer une cellule : on donne sa valeur et le nombre de niveaux que possède
// cette cellule, pour obtenir un pointeur vers cette cellule
t_d_cell *create_cell(int value, int n_levels) {
    t_d_cell *cell = malloc(sizeof(t_d_cell)); // alloue de la mémoire
    cell->value = value;        // cell pointe value qui prendra la valeur
    cell->max_level = n_levels; // le nombre de niveau de la cellule
    cell->next = malloc(
            n_levels * sizeof(t_d_cell *)); // alloue la mémoire des pointeur suivant
    for (int i = 0; i < n_levels; i++) {
        cell->next[i] = NULL; // les pointeur pointe à null
    }
    return cell;
}