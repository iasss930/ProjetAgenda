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
char *concatener(char *, char *);

t_agenda *creerAgenda(void);
void afficher1niveau(t_agenda *, int);
void afficherAgenda(t_agenda *);

t_contact *creerContact(char *, char *, int);
void addContact(t_agenda *, t_contact *);
void addContactTri(t_agenda *, t_contact *, t_contact *, t_contact *);
t_recherchecontact Recherche(t_agenda *, char *, char *, int log);

t_rendezvous *creerRendezVous(int, int, int, int, int, int, int, char *);
void ajouterRendezVous(t_contact *, t_rendezvous *);
void SupRendezVous(t_contact *, int );
void afficherRendezVous(t_rendezvous *);

void ImportContactRdv(t_agenda *);
void ExportContactRdv(t_agenda *);
int ExisteSauvegarde();
int SauvegardePossible();


void MenuEntete(int );
void MenuPied();
void MenuCorp(char *, char*, char *);
int MenuCorpR(t_contact *, int, char *);
int MenuCorpC(t_contact *, int, char *, char *);

int DateValide(int ,int ,int );
int HeureValide(int ,int );
int DureeValide(int ,int );

#endif // UNTITLED_CELL_H
