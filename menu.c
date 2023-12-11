#include "menu.h"
#include "stdio.h"
#include "stdlib.h"


void add_contact(t_agenda *agenda){
    char *nom = scanString("Quel est le nom du contact ?\n");
    char *prenom = scanString(("Quel est son prénom ?\n"));
    t_contact *contact = create_contact(nom, prenom, 4);
    insert_contact(agenda, contact);
}

void affiche_level(t_agenda *agenda){
    printf("Quel niveau voulez-vous afficher ?\n"
               "0 : tous les contacts\n"
               "1 : Les contacts n'ayant pas les 2 premieères lettres similaires\n"
               "2 : Les contacts n'ayant pas les 3 premieères lettres similaires\n"
               "3 : Les contacts n'ayant pas les 4 premieères lettres similaires\n");
    int level;
    scanf("%d", level);
    if(level == 1 || level == 2 || level == 3 || level == 4){
        display_ag_level(*agenda, level);
        return;
    }
    else{
        affiche_level(agenda);
    }
}