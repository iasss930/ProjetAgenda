#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "agenda.h"


const int *LOG = "../log3.txt";
const int *SAV = "../sauvegarde.txt";

int cobtacts=0;
int rdv=0;

char *scanString(char *question) {
    char *txt = NULL;
    int taille = 0;
    char lettre;

    printf("%s", question);
    while ((lettre = getchar()) != '\n' || taille < 3) {
        if ((lettre >= 'a' && lettre <= 'z') ||
            (lettre >= 'A' && lettre <= 'Z') ||
            lettre == ' ' || lettre == '\'' || lettre == '-') {
            taille++;
            txt = (char *)realloc(txt, taille * sizeof(char));
            if (txt == NULL) {
                printf("Erreur d'allocation de mémoire.\n");
                exit;
            }
            txt[taille - 1] = lettre;
        }
        else {
            printf("\b");
        }
    }
    txt = (char *)realloc(txt, (taille + 1) * sizeof(char));
    txt[taille] = '\0';

    return txt;
}


char *minuscule(char *nom_prenom) {
    char *result = (char *)malloc(strlen(nom_prenom) + 1);
    if (result == NULL) {
        printf("Allocation de mémoire a échoué.");
        exit;
    }
    for (int i = 0; nom_prenom[i] != '\0'; i++) {
        result[i] = tolower(nom_prenom[i]);
    }
    result[strlen(nom_prenom)] = '\0';

    return result;
}


t_agenda *creerAgenda(void) {
    t_agenda *agenda = (t_agenda *)malloc(sizeof(t_agenda));
    agenda->max_level = 4;
    agenda->contacts = (t_contact *)malloc(4 * sizeof(t_contact));
    for (int i = 0; i < 4; i++) {
        agenda->contacts[i] = NULL;
    }
    return agenda;
}


t_contact *creerContact(char *nom, char *prenom, int max_level) {
    t_contact *contact = (t_contact *)malloc(
            sizeof(t_contact)); // allocation de mémoire pour contact
    contact->nom =
            (char *)malloc(strlen(nom) + 1); // allocation de mémoire pour le nom plus
    // 1 pour le caractère de fin de chaine
    strcpy(contact->nom, nom); // on copie le nom
    contact->prenom = (char *)malloc(
            strlen(prenom) + 1); // allocation de mémoire pour le prénom plus 1 pour
    // le caractère de fin de chaine
    strcpy(contact->prenom, prenom); // on copie le prénom
    contact->nom_prenom =
            (char *)malloc(strlen(nom) + strlen(prenom) +
                           2); // allocation de mémoire pour le nom_prenom plus 1 et
    // pour le caractère de fin plus 1
    strcpy(contact->nom_prenom, minuscule(nom));
    strcat(contact->nom_prenom,
           "_"); // ajoute la chaine à la suite à l'aide de strcat
    strcat(contact->nom_prenom, minuscule(prenom));
    contact->rendezvous = NULL;
    contact->max_level = max_level;
    contact->next = (t_contact *)malloc(
            max_level * sizeof(t_contact)); // alloue la mémoire des pointeur suivant
    for (int i = 0; i < max_level; i++) {
        contact->next[i] = NULL; // met les pointeur à null
    }
    return contact;
}
