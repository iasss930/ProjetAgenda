#ifndef UNTITLED_PARTIE3_H
#define UNTITLED_PARTIE3_H

// Structure pour stocker un rendez-vous
typedef struct s_rendezvous {
    int jour, mois, annee;
    int heure, minute;
    int duree_heure, duree_minute;
    char *objet;
    struct s_rendezvous *next;
} t_rendezvous;

// Structure pour stocker un contact
typedef struct s_contact {
    char *nom;
    char *prenom;
    char *nom_prenom;
    struct s_rendezvous *rendezvous; // Un tableau dynamique de rendez-vous
    struct s_contact **next;
    int max_level;
} t_contact;

// Structure pour l'agenda
typedef struct s_agenda {
    t_contact **contacts; // Un tableau dynamique de contacts
    int max_level;        // nombre de niveau de la liste
} t_agenda;


typedef struct s_recherchecontact {
    t_contact *prec;
    t_contact *current;
    int niveau;
}t_recherchecontact;


char *scanString(char *);
char *minuscule(char *);



#endif