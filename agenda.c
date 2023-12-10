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


t_agenda *create_agenda(void) {
    t_agenda *agenda = (t_agenda *)malloc(sizeof(t_agenda));
    agenda->max_level = 4;
    agenda->contacts = (t_contact *)malloc(4 * sizeof(t_contact));
    for (int i = 0; i < 4; i++) {
        agenda->contacts[i] = NULL;
    }
    return agenda;
}


t_contact *create_contact(char *nom, char *prenom, int max_level) {
    t_contact *contact = (t_contact *) malloc(sizeof(t_contact));
    contact->nom = (char *) malloc(strlen(nom) + 1);
    strcpy(contact->nom, nom);
    contact->prenom = (char *) malloc(strlen(prenom) + 1);
    strcpy(contact->prenom, prenom);
    contact->nom_prenom = (char *) malloc(strlen(nom) + strlen(prenom) + 2);
    strcpy(contact->nom_prenom, minuscule(nom));
    strcat(contact->nom_prenom, "_");
    strcat(contact->nom_prenom, minuscule(prenom));
    contact->rendezvous = NULL;
    contact->max_level = max_level;
    contact->next = (t_contact *) malloc(max_level * sizeof(t_contact));
    for (int i = 0; i < max_level; i++) {
        contact->next[i] = NULL;
        return contact;
    }
}


