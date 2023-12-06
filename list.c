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
        list->head[i] = NULL; // met les pointeur à null
    }
    list->max_level = max_level; //à la list on lui met le nombre de niveau total
    return list;
}

// Insérer une cellule à niveaux en tête de liste (attention à bien tenir compte
// du nombre de niveaux de la cellule)
void insert_list(t_d_list *list, t_d_cell *cell) {
    for (int i = 0; i < cell->max_level && i < list->max_level; i++) {
        cell->next[i] =
                list->head[i]; // il prend l'adresse de la cellule et pour chaque niveau
        // chaque cellule égale à tel adresse
    }
    for (int i = cell->max_level - 1; i >= 0 && i < list->max_level; i--) {
        list->head[i] = cell; // chaque cellule devient la cellule de tête de liste
    }
}

// Afficher l’ensembles des cellules de la liste pour un niveau donné alligne
void display_one_level(t_d_list *list, int level) {
    t_d_cell *cell = list->head[level]; // on commence par la tête de la liste
    printf("[list head_%d @-]", level);
    if (cell == NULL) {
        printf("NULL\n"); // si la cellule est nulle on affiche NULL (fonctionne que
        // si la liste est vide)
        return;
    }
    t_d_cell *cell0;       // valeur 1er cellule de la liste du niveau 0
    int old = cell->value; // la valeur de la cellule courante
    int cpt = 0;           // un compteur
    if (list->head[0]->value !=
        list->head[level]->value) { // si la tête de la liste n'est pas la même
        // que la 1er cellule trouvé
        cell0 = list->head[0];
        while (cell0 != NULL) {
            if (cell0->value < cell->value) {
                cpt++;
            }
            cell0 = cell0->next[0]; // on passe à la suivante
        }
        for (int i = 0; i < cpt; i++) {
            printf(
                    "-----------"); // boucle sur le nombre de fois puis on met les tiret
        }
    }

    while (cell != NULL) { // on parcourt le niveau, on refait la même chose
        cell0 = list->head[0];
        cpt = 0;
        while (cell0 != NULL) {
            if (cell0->value > old && cell0->value < cell->value) {
                cpt++;
            }
            cell0 = cell0->next[0];
        }
        for (int i = 0; i < cpt; i++) {
            printf("-----------");
        }
        // nombre de cellule entre old et new
        printf("-->[%3d|@-]", cell->value); // affiche la valeur de la cellule
        old = cell->value;
        cell = cell->next[level]; // on passe à la suivante
    }
    cpt = 0;
    int last0;
    cell0 = list->head[0];
    while (cell0 != NULL) { // on compte le nombre de cellule en fin de liste
        last0 = cell0->value;
        cell0 = cell0->next[0];
    }
    if (last0 != old) {
        cell0 = list->head[0];
        while (cell0 != NULL) {
            if (cell0->value > old) {
                cpt++;
            }
            cell0 = cell0->next[0];
        }
        for (int i = 0; i < cpt; i++) {
            printf("-----------");
        }
    }
    printf("-->NULL\n");
}

// Afficher tous les niveaux de la liste
void display_all_levels(t_d_list *list) {
    for (int i = 0; i < list->max_level; i++) {
        display_one_level(
                list, i); // on appelle la fonction pour afficher un niveau de la liste
        // autant de fois qu'il a de niveau à a l'aide du for
    }
}

// Insérer une cellule à niveau dans la liste, au bon endroit, de manière à ce
// que la liste reste triée par ordre croissant
void insert_cell(t_d_list *list, t_d_cell *cell) {
    int level;
    t_d_cell *current;
    for (level = 0; level < cell->max_level; level++) { // on parcourt les niveaux
        if (list->head[level] == NULL) {
            list->head[level] = cell; // si la liste est vide on y insère la cellule
        } else if (cell->value < list->head[level]->value) {
            t_d_cell *temp = list->head[level]; // on crée une cellule temporaire
            list->head[level] = cell;           // on y insère la cellule
            cell->next[level] = temp;
        } else { // on insère la cellule car le bon niveau est trouvé
            current = list->head[level];
            while (current->next[level] != NULL &&
                   current->next[level]->value <
                   cell->value) { // cherche la bonne position
                current = current->next[level];
            }
            cell->next[level] = current->next[level]; // insère à la bonne position
            current->next[level] = cell;
        }
    }
}

int classical_search(t_d_list *list, int value, int level) {
    t_d_cell *current;
    current = list->head[level];     // variable temporaire
    while (current != NULL) {        // on boucle tant que la fin de la liste
        if (current->value == value) { // valeur trouvée
            return 0;
        } else { // valeur non trouvée on passe à la suivante
            current = current->next[level];
        }
    }
    return 1; // valeur non trouvé
}

int expert_search(t_d_list *list, t_d_cell *first, t_d_cell *last, int value,
                  int level) {

    t_d_cell *current = first;
    t_d_cell *prec = first;

    while (current != last && current != NULL) { // on boucle tant que list!=NULL
        if (current->value > value) {
            if (level == 0) {
                return 1;
            } else {
                return expert_search(list, prec, current, value, level - 1);
            }
        } else if (current->value < value) { // on cherche la bonne position
            prec = current;
            current = current->next[level]; // on passe à la suivante
        } else {
            return 0; // valeur trouvée
        }
    }
    if (level == 0) {
        return 1; // valeur non trouvée
    } else {
        if (prec == first) {//jamais trouvé de valeur plus petite
            return expert_search(list, list->head[level - 1], NULL, value, level - 1);//on cherche dans le niveau précédent en commencant à la 1er valeur du niveau précédent
        } else {
            return expert_search(list, prec, NULL, value, level - 1);
        }
    }
}
