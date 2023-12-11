#ifndef UNTITLED_PARTIE3_H
#define UNTITLED_PARTIE3_H


typedef struct s_rendezvous {
    int jour, mois, annee;
    int heure, minute;
    int duree_heure, duree_minute;
    char *objet;
    struct s_rendezvous *next;
} t_rendezvous;


typedef struct s_contact {
    char *nom;
    char *prenom;
    char *nom_prenom;
    struct s_rendezvous *rendezvous;
    struct s_contact **next;
    int max_level;
} t_contact;

typedef struct s_agenda {
    t_contact **contacts;
    int max_level;
} t_agenda;

typedef struct s_recherchecontact {
    t_contact *prec;
    t_contact *current;
    int niveau;
}t_recherchecontact;


char *scanString(char *);
t_agenda *create_agenda(void);
t_contact *create_contact(char *, char *, int);
void display_ag_level(t_agenda, int );
void display_agenda(t_agenda);
void insert_contact(t_agenda *agenda, t_contact *contact, t_contact *prev, t_contact *next);
char *minuscule(char *);


#endif