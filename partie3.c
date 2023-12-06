#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "partie3.h"

const int *LOG = "../log3.txt";// nom du fichier des log (temps)
const int *SAV = "../sauvegarde.txt";// nom du fichier de sauvegarde

int nbcontact=0, nbrdv=0; // Variables globales, communes à toutes les fonction si ajouter à un ajouter a tous

// Fonction effectuant la saisie, retournant un tableau dynamique stockant
// uniquement les caractères jusqu'à touche Entrée
char *scanString(char *question) {
    char *texte = NULL;
    int taille = 0;
    char caractere;

    printf("%s", question);
    while ((caractere = getchar()) != '\n' || taille < 3) {
        if ((caractere >= 'a' && caractere <= 'z') ||
            (caractere >= 'A' && caractere <= 'Z') ||
            caractere == ' ' || caractere == '\'' || caractere == '-') {
            taille++;
            texte = (char *)realloc(texte, taille * sizeof(char));
            if (texte == NULL) {
                printf("Erreur d'allocation de mémoire.\n");
                exit;
            }
            texte[taille - 1] = caractere;
        }
        else {
            printf("\b");
        }
    }
    texte = (char *)realloc(texte, (taille + 1) * sizeof(char)); // Ajout de mémoire pour le caractère de fin de chaine
    texte[taille] = '\0';  // caractère de fin de chaine

    return texte;
}

// fonction pour renvoyer chaine en minuscule
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

// fonction pour renvoyer chaine concaténer
/*char *concatener(char *chaine1, char *chaine2) {
  char *resultat = (char *)malloc(strlen(chaine1) + strlen(chaine2) + 1);
  if (resultat == NULL) {
    printf("Allocation de mémoire a échoué.");
    exit;
  }
  strcpy(resultat, chaine1); // Copiez la première chaîne
  strcat(resultat, chaine2); // Concaténez la deuxième chaîne
  return resultat;
}*/

// fonction de création d'agenda
t_agenda *creerAgenda(void) {
    t_agenda *agenda = (t_agenda *)malloc(sizeof(t_agenda));
    agenda->contacts =
            (t_contact *)malloc(4 * sizeof(t_contact)); // aloue la mémoire
    for (int i = 0; i < 4; i++) {
        agenda->contacts[i] = NULL; // met les pointeur à null
    }
    agenda->max_level = 4; //à la list on lui met le nombre de niveau total
    return agenda;
}

// Afficher l’ensembles des cellules de la liste pour un niveau donné alligne
void afficher1niveau(t_agenda *agenda, int level) {
    t_contact *contact =
            agenda->contacts[level]; // on commence par la tête de la liste
    printf("[Agenda_%d @-]", level);
    if (contact == NULL) {
        printf("-->NULL\n"); // si la cellule est nulle on affiche NULL (fonctionne
        // que si la liste est vide)
        return;
    }

    while (contact != NULL) { // on parcourt le niveau, on refait la même chose
        printf("-->[%s|@-]",
               contact->nom_prenom);    // affiche la valeur de la cellule
        contact = contact->next[level]; // on passe à la suivante
    }
    printf("-->NULL\n");
}

// Afficher tous les niveaux de la liste
void afficherAgenda(t_agenda *agenda) {
    for (int i = 0; i < agenda->max_level; i++) {
        afficher1niveau(
                agenda, i); // on appelle la fonction pour afficher un niveau de la
        // liste autant de fois qu'il a de niveau à a l'aide du for
    }
}

// Fonction pour créer un contact
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

// fonction ajouter contact en tête d'agenda
/*void addContact(t_agenda *agenda, t_contact *contact) {
  for (int i = 0; i < contact->max_level && i < agenda->max_level; i++) {
    contact->next[i] =
        agenda->contacts[i]; // il prend l'adresse de la cellule et pour chaque
                             // niveau chaque cellule égale à tel adresse
  }
  for (int i = contact->max_level - 1; i >= 0 && i < agenda->max_level; i--) {
    agenda->contacts[i] =
        contact; // chaque cellule devient la cellule de tête de liste
  }
  nbcontact++;
}*/
// fonction ajouter contact au bon endroit dans la liste
void addContactTri(t_agenda *agenda, t_contact *contact, t_contact *prec, t_contact *suiv) {
    if (prec != NULL) {
        for (int i = 0; i < contact->max_level && i < agenda->max_level; i++) {
            contact->next[i] = prec->next[i]; // il prend l'adresse de la cellule et pour chaque niveau chaque cellule égale à tel adresse
        }
        for (int i = contact->max_level - 1; i >= 0 && i < agenda->max_level; i--) {
            prec->next[i] = contact; // chaque cellule devient la cellule de tête de liste
        }
        if (strcmp(prec->nom_prenom, contact->nom_prenom) > 0) {
            char *t_c;
            t_rendezvous *t_r;
            t_c = prec->nom;
            prec->nom = contact->nom;
            contact->nom = t_c;
            t_c = prec->prenom;
            prec->prenom = contact->prenom;
            contact->prenom = t_c;
            t_c = prec->nom_prenom;
            prec->nom_prenom = contact->nom_prenom;
            contact->nom_prenom = t_c;
            t_r=prec->rendezvous;
            prec->rendezvous=contact->rendezvous;
            contact->rendezvous=t_r;
        }
    }
    else {
        for (int i = 0; i < contact->max_level && i < agenda->max_level; i++) {
            contact->next[i] =
                    agenda->contacts[i]; // il prend l'adresse de la cellule et pour chaque
            // niveau chaque cellule égale à tel adresse
        }
        for (int i = contact->max_level - 1; i >= 0 && i < agenda->max_level; i--) {
            agenda->contacts[i] =
                    contact; // chaque cellule devient la cellule de tête de liste
        }
    }
    nbcontact++;
}


t_recherchecontact Recherche(t_agenda *agenda, char *nom, char *prenom, int log) {//paramètre int log pour savoir si enregistrer log ou pas dans la recherche
    t_recherchecontact r; // structure de retour de la fonction pour avoir les bornes pour ajouter le contact en cas de valeur non trouvée et e niveau pour créer le contact
    r.current = agenda->contacts[0];
    r.prec = agenda->contacts[0];
    r.niveau = 4;

    char *nom_prenom;
    int comp;

    clock_t debut, fin; // Variable pour stocker les temps d'écécution des recherches
    char time_lvl0[15];
    char time_all_levels[15];
    FILE *log_file = NULL;
    char format[] = "%c\t%s\t%s\n";

    if (log == 0) { // Pas d"enregistrement des log si Log différent(<>) 0
        log_file = fopen(LOG, "a"); // fichier des logs des temps

        debut = clock(); // Enregistrez le temps de début
    }
    nom_prenom = (char *)malloc(strlen(nom) + strlen(prenom) + 2); // allocation de mémoire pour le nom_prenom plus 1 et pour le caractère de fin plus 1
    strcpy(nom_prenom, minuscule(nom));
    strcat(nom_prenom, "_"); // ajoute la chaine à la suite à l'aide de strcat
    strcat(nom_prenom, minuscule(prenom));

    // Recherche directe au niveau 0
    while (r.current != NULL) {        // on boucle tant que la fin de la liste
        comp=strcmp(r.current->nom_prenom, nom_prenom); // comparaison de 2 chaines de caractères
        if (comp == 0) { // valeurs identiques, on indique trouvée avec niveau=-1 et on sort de la boucle
            r.niveau=-1;
            break;
        } else if (comp < 0){ // valeur courante plus petite que valeur cherchée, on passe à la suivante en sauvegardant la valeur courante dans prec avant
            r.prec=r.current;
            r.current = r.current->next[0];
        }
        else if (comp > 0) { //valeur courante plus grande que valeur cherchée, on arrête la recherche
            break;
        }
    }

    if (log == 0) {
        fin = clock(); // Enregistrez le temps de fin
        sprintf(time_lvl0,"%.6f",((double)(fin - debut)) / CLOCKS_PER_SEC * 1000000);


        debut = clock(); // Enregistrez le temps de début
    }
    // Recherche au niveau 4
    r.niveau = 4;
    r.current = agenda->contacts[3];
    r.prec = agenda->contacts[2];
    char *val = malloc(sizeof(char) * 3);
    char *cur = malloc(sizeof(char) * 3);
    val[0] = nom_prenom[0];
    val[1] = '\0';
    while (r.current != NULL) {        // on boucle tant que la fin de la liste
        cur[0] = r.current->nom_prenom[0];
        cur[1] = '\0';
        comp=strcmp(cur, val); // comparaison de 2 chaines de caractères
        if (comp == 0) { // valeurs identiques, on indique trouvée avec niveau=-1 et on sort de la boucle
            r.niveau=3;
            break;
        } else if (comp < 0){ // valeur courante plus petite que valeur cherchée, on passe à la suivante en sauvegardant la valeur courante dans prec avant
            r.prec=r.current;
            r.current = r.current->next[0];
        }
        else if (comp > 0) { //valeur courante plus grande que valeur cherchée, on arrête la recherche
            break;
        }
    }
    free(val);
    free(cur);
    // Recherche au niveau 3
    r.current = r.prec;
    r.prec = agenda->contacts[1];
    val = malloc(sizeof(char) * 3);
    cur = malloc(sizeof(char) * 3);
    val[0] = nom_prenom[0];
    val[1] = nom_prenom[1];
    val[2] = '\0';
    while (r.current != NULL) {        // on boucle tant que la fin de la liste
        cur[0] = r.current->nom_prenom[0];
        cur[1] = r.current->nom_prenom[1];
        cur[2] = '\0';
        comp=strcmp(cur, val); // comparaison de 2 chaines de caractères
        if (comp == 0) { // valeurs identiques, on indique trouvée avec niveau=-1 et on sort de la boucle
            r.niveau=2;
            break;
        } else if (comp < 0){ // valeur courante plus petite que valeur cherchée, on passe à la suivante en sauvegardant la valeur courante dans prec avant
            r.prec=r.current;
            r.current = r.current->next[0];
        }
        else if (comp > 0) { //valeur courante plus grande que valeur cherchée, on arrête la recherche
            break;
        }
    }
    free(val);
    free(cur);
    // Recherche au niveau 2
    r.current = r.prec;
    r.prec = agenda->contacts[0];
    val = malloc(sizeof(char) * 4);
    cur = malloc(sizeof(char) * 4);
    val[0] = nom_prenom[0];
    val[1] = nom_prenom[1];
    val[2] = nom_prenom[2];
    val[3] = '\0';
    while (r.current != NULL) {        // on boucle tant que la fin de la liste
        cur[0] = r.current->nom_prenom[0];
        cur[1] = r.current->nom_prenom[1];
        cur[2] = r.current->nom_prenom[2];
        cur[3] = '\0';
        comp=strcmp(cur, val); // comparaison de 2 chaines de caractères
        if (comp == 0) { // valeurs identiques, on indique trouvée avec niveau=-1 et on sort de la boucle
            r.niveau=1;
            break;
        } else if (comp < 0){ // valeur courante plus petite que valeur cherchée, on passe à la suivante en sauvegardant la valeur courante dans prec avant
            r.prec=r.current;
            r.current = r.current->next[0];
        }
        else if (comp > 0) { //valeur courante plus grande que valeur cherchée, on arrête la recherche
            break;
        }
    }
    free(val);
    free(cur);
    // Recherche au niveau 1
    r.current = r.prec;
    r.prec = agenda->contacts[0];
    while (r.current != NULL) {        // on boucle tant que la fin de la liste
        comp=strcmp(r.current->nom_prenom, nom_prenom); // comparaison de 2 chaines de caractères
        if (comp == 0) { // valeurs identiques, on indique trouvée avec niveau=-1 et on sort de la boucle
            r.niveau=-1;
            break;
        } else if (comp < 0){ // valeur courante plus petite que valeur cherchée, on passe à la suivante en sauvegardant la valeur courante dans prec avant
            r.prec=r.current;
            r.current = r.current->next[0];
        }
        else if (comp > 0) { //valeur courante plus grande que valeur cherchée, on arrête la recherche
            break;
        }
    }
    if (log == 0) {
        fin = clock(); // Enregistrez le temps de fin

        sprintf(time_all_levels,"%.6f",((double)(fin - debut)) / CLOCKS_PER_SEC * 1000000);//permet d'écrire dans une chaine de caractère, printf ca écrit à l'écran, sprintf écrit dans la varianle time_all_levels

        fprintf(log_file, format, nom[0], time_lvl0, time_all_levels);//fprintf écrit dans le fichier log_file
        fclose(log_file); // fermeture du fichier log_file
    }
    return r;
}



// Fonction pour créer un rendez-vous
t_rendezvous *creerRendezVous(int jour, int mois, int annee, int heure,int minute, int duree_heure, int duree_minute, char *objet) {
    t_rendezvous *rdv = (t_rendezvous *)malloc(sizeof(t_rendezvous));
    rdv->jour = jour;
    rdv->mois = mois;
    rdv->annee = annee;
    rdv->heure = heure;
    rdv->minute = minute;
    rdv->duree_heure = duree_heure;
    rdv->duree_minute = duree_minute;
    rdv->objet = (char *)malloc(strlen(objet) + 1);
    strcpy(rdv->objet, objet);
    rdv->next = NULL;
    return rdv;
}


// Fonction pour ajouter un rendez-vous à un contact
void ajouterRendezVous(t_contact *contact, t_rendezvous *rdv) {
    rdv->next = contact->rendezvous;
    contact->rendezvous = rdv;
    nbrdv++;
}

// Fonction pour supprimer le nième rendez-vous dun contact
void SupRendezVous(t_contact *contact, int nb) {
    t_rendezvous *rdv=contact->rendezvous;//quelle contact le rdv appartient
    t_rendezvous *rdv_prec=contact->rendezvous;//numéro du rdv
    if (nb == 1) {
        contact->rendezvous = rdv->next;//l'adresse de contact devient celle de next(rdv que l'on va supprimer)
    }
    else {//supérieur à1
        for (int i=0; i<nb-1; i++) {
            rdv_prec=rdv;//rdv devient rdv prec
            rdv=rdv->next;//rdv devient rdv suivant lui celui qu'on veut supprimer après toutes les itération
        }
        rdv_prec->next=rdv->next;  //on met l'adresse de celui que l'on veut supprimer
    }
    nbrdv--;
    free(rdv->objet);//on libère l'espace mémoire de l'objet
    free(rdv);//on libère l'espace mémoire de rdv
}


// Fonction pour afficher un rendez-vous
void afficherRendezVous(t_rendezvous *rendez_vous) {
    t_rendezvous *rdv = rendez_vous;
    if (rdv == NULL) {
        printf("Pas de rendez vous\n");
        return;
    }

    while (rdv != NULL) {
        // On affiche la date du rendez-vous
        printf("Date : %02d/%02d/%04d\n", rdv->jour, rdv->mois, rdv->annee);

        // On affiche l'heure du rendez-vous
        printf("Heure : %02d:%02d\n", rdv->heure, rdv->minute);

        // On affiche la durée du rendez-vous
        printf("Durée : ");
        if (rdv->duree_heure !=0) {
            printf("%d heures ",rdv->duree_heure);
        }
        if (rdv->duree_heure !=0 && rdv->duree_minute != 0) {
            printf("et ");
        }
        if (rdv->duree_minute != 0) {
            printf("%d minutes", rdv->duree_minute);
        }
        printf("\n");
        // On affiche l'objet du rendez-vous
        printf("Objet : %s\n", rdv->objet);
        printf("-------------\n");
        rdv = rdv->next;
    }
}

// fonction pour supprimer le rendez vous d'un contact

// Fonction pour vérifier l'existance de la sauvegarde
int ExisteSauvegarde() {
    FILE *fichier = fopen(SAV, "r");

    if (fichier != NULL) {
        fclose(fichier);
        return 0; // Succès : Le fichier existe et on peut le lire
    }
    else {
        return 1; // Echec : // Le fichier n'existe pas ou on ne peut pas le lire
    }
}
// Fonction pour vérifier si la sauvegarde est possible
int SauvegardePossible() {
    FILE *fichier = fopen(SAV, "a");

    if (fichier != NULL) {
        fclose(fichier);
        return 0; // Succès : Le fichier existe et on peut ecrire
    }
    else {
        return 1; // Echec : // Le fichier n'existe pas ou on ne peut pas ecrire
    }
}

// Fonction pour importer un fichier de rendez-vous
void ImportContactRdv(t_agenda *agenda) {
    FILE *f = fopen(SAV, "r");//défini fichier
    char l[256];
    char *nom = NULL, *prenom = NULL, *objet = NULL;
    int jour, mois, annee, heure, minutes, heure2, minutes2;
    t_contact *contact;
    t_rendezvous *rdv;
    t_recherchecontact search;


    size_t s = 0;
    while (fgets (l,sizeof(l),f) != NULL) //récupere une ligne du fichier -1 fin du fichier
    {
        for (int i = 0; i < strlen(l); i++) {
            if (l[i] == '\n') {
                // Remplacer le caractère
                l[i] = '\0';
            }
        }
        nom = strtok(l, "\t");//permet de récupérer premier terme jusqu'à la tabulation
        prenom = strtok(NULL, "\t");
        jour = atoi(strtok(NULL, "\t"));//atoi permet de transformer en entier
        mois = atoi(strtok(NULL, "\t"));
        annee = atoi(strtok(NULL, "\t"));
        heure = atoi(strtok(NULL, "\t"));
        minutes = atoi(strtok(NULL, "\t"));
        heure2 = atoi(strtok(NULL, "\t"));
        minutes2 = atoi(strtok(NULL, "\t"));
        objet = strtok(NULL, "\t");

        //récupérer nom prenom rdv  1 ligne 1 rdv

        search = Recherche(agenda, nom, prenom, 1);//recherche du contact
        if (search.niveau != -1) {//contact non trouvée
            contact = creerContact(nom, prenom, search.niveau);//création du contact
            addContactTri(agenda, contact, search.prec, search.current);//ajout du contact dans l'agenda
            if (jour != 0) {
                rdv = creerRendezVous(jour, mois, annee, heure, minutes, heure2, minutes2, objet);//création du rendez-vous
                ajouterRendezVous(contact, rdv);// ajout du rendez vous au contact
            }
        }
        else {
            if (jour != 0) {
                rdv = creerRendezVous(jour, mois, annee, heure, minutes, heure2, minutes2, objet);//création du rendez-vous
                ajouterRendezVous(search.current, rdv);//ajout du rendez-vous au contact
            }
        }
    }
}


void ExportContactRdv(t_agenda *agenda) {//sauvegarde du fichier
    FILE *f = fopen(SAV, "w");//défini fichier
    t_contact *contact = agenda->contacts[0]; // on commence par la tête de la liste

    t_rendezvous *rdv = NULL; // on commence par la tête de la liste
    while (contact != NULL) { // on parcourt le niveau, on refait la même chose
        rdv = contact->rendezvous;
        if (rdv == NULL) {
            fprintf(f, "%s\t%s\t0\t0\t0\t0\t0\t0\t0\t0\n", contact->nom, contact->prenom);//on ecrit dans le fichier
        }
        else {
            while (rdv != NULL) { // on parcourt le niveau, on refait la même chose
                fprintf(f, "%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n", contact->nom, contact->prenom, rdv->jour, rdv->mois, rdv->annee, rdv->heure, rdv->minute, rdv->duree_heure, rdv->duree_minute, rdv->objet);
                rdv = rdv->next;
            }
        }
        contact = contact->next[0];
    }
    fclose(f);//ferme le fichier
}


void MenuEntete(int on) {//le paramètre on signigie que le menu est actif sinon on ne peux pas retaper dessus
    system("cls"); //system("clear"); // Clear screan
    printf("________________________________________________________________________\n");
    printf("|        o o o o                                                       |\n");
    printf("|       o        o                                      o              |\n");
    printf("|      o    o o   o    o o o o                          o              |\n");
    printf("|      o   o  o   o   o     o    o o o   o  o o    o o oo   o o o      |\n");
    printf("|      o  o   o   o   o     o   o     o  o o   o  o     o        o     |\n");
    printf("|      o   o o o o     o o o    o o o o  o     o  o     o   o o  o     |\n");
    printf("|       o             o         o        o     o  o   o o  o   o o     |\n");
    printf("|        o o o o o    o o o o    o o o   o     o   o o  o   o o  o     |\n");
    printf("|                     o     o                                          |\n");
    printf("|                      o o o                                           |\n");
    printf("|----------------------------------------------------------------------|\n");
    if (on == 0) {
        printf("| Ajout [C]ontact | [A]jout RDV | [S]upr. RDV | A[f]f. RDV | [Q]uitter |\n");
    }
    else {
        printf("|  Ajout Contact  |  Ajout RDV  |  Supr. RDV  |  Aff. RDV  |  Quitter  |\n");
    }
}
void MenuPied() {//s'affiche en bas contact et rdv nombre chacun
    float v0=0, vall=0, min_0['z'-'a'+2], max_0['z'-'a'+2], moy_0['z'-'a'+2], min_all['z'-'a'+2], max_all['z'-'a'+2], moy_all['z'-'a'+2], moy_max=0;//v0 vall valeur que l'on lit, min max permet d'avoir la plus petite/grande valeur pour la lettre des code Ascii 1 indice car 1 valeur en plus plus 1
    int nbl['z'-'a'+2];//nombre de ligne
    size_t s = 0;
    char l[256], *t=NULL;//pointeur vers ligne

    printf("|----------------------------------------------------------------------|\n");
    printf("| %6d contacts / %6d rendez-vous                                 |\n",nbcontact, nbrdv);
    printf("|----------------------------------------------------------------------|\n");

    // lecture des temps dans le fichier des log
    FILE *f = fopen(LOG, "r");//défini fichier
    if (f == NULL) {
        printf("2\n");
        f = fopen(LOG, "w");//défini fichier
    }

    // Initialisation des variables (les min à 9999 une grande valeur...)
    for (int i=0; i<'z'-'a'+2; i++) {
        max_0[i]=moy_0[i]=max_all[i]=moy_all[i]=0.0;
        min_all[i]=min_0[i]=9999.99;
        nbl[i]=0;
    }

    while (fgets (l,sizeof(l),f) != NULL) { //récupere une ligne du fichier -1 fin du fichier
        for (int i = 0; i < strlen(l); i++) {
            if (l[i] == '\n') {
                // Remplacer le caractère
                l[i] = '\0';
            }
        }
        t = strtok(l, "\t");//permet de récupérer premier terme jusqu'à la tabulation
        v0 = atof(strtok(NULL, "\t"));//atof transformer en float et strtok récupère tout ce qui dans la variable jusqu'à la tab
        vall = atof(strtok(NULL, "\t"));

        // indice 0 : global
        nbl[0]++;
        if (min_0[0] > v0) {min_0[0]=v0;}//commence première valeur
        if (max_0[0] < v0) {max_0[0]=v0;}
        moy_0[0]+=v0;//somme de toute les valeurs
        if (min_all[0] > vall) {min_all[0]=vall;}
        if (max_all[0] < vall) {max_all[0]=vall;}
        moy_all[0]+=vall;
        // Indice de 1 (t-'a'+1) à 26 (t-'z'+1) pour chaque lettre
        nbl[t[0]-'a'+1]++;
        if (min_0[t[0]-'a'+1] > v0) {min_0[t[0]-'a'+1]=v0;}//t -> caractère qui est lu dans le fichier attention chaine de caractère donc prendre le premier element
        if (max_0[t[0]-'a'+1] < v0) {max_0[t[0]-'a'+1]=v0;}
        moy_0[t[0]-'a'+1]+=v0;
        if (min_all[t[0]-'a'+1] > vall) {min_all[t[0]-'a'+1]=vall;}
        if (max_all[t[0]-'a'+1] < vall) {max_all[t[0]-'a'+1]=vall;}
        moy_all[t[0]-'a'+1]+=vall;
    }

    // Calcul de de la moyenne max pour des lettres pour optimiser l'affichage
    for (int i=1; i<'z'-'a'+2; i++) {
        if (moy_max<(moy_0[i]/nbl[i])) {moy_max=moy_0[i]/nbl[i];}
        if (moy_max<(moy_all[i]/nbl[i])) {moy_max=moy_all[i]/nbl[i];}
    }
    fclose(f);//ferme le fichier


    int j=10;//le graphisque 10 ligne en hauteur
    printf("|                                       %3d ",(int)round(moy_max/(10.0/j)));
    for (int i='a'; i<='z'; i++) {
        if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("0");//si la moyenne est égale à j et la moyenne de tous les niveau est égale à j alors on affiche
        }
        else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("o");//si la moyenne au niveau 0 est j on affiche
        }
        else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("-");//si la moyenne de tous les niveau c'est j (donc on en a qu'un) on affiche
        }
        else {
            printf(" "); //si aucun de ces cas on affiche
        }
    }
    j--;//on passe à la ligne suivante du hauut vers le bas
    printf(" |\n");
    printf("|                                       %3d ",(int)round(moy_max/(10.0/j)));
    for (int i='a'; i<='z'; i++) {
        if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("0");
        }
        else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("o");
        }
        else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("-");
        }
        else {
            printf(" ");
        }
    }
    j--;// dès 3e ligne début affichage avec tableau également
    printf(" |\n");
    printf("| ____________________________________  %3d ",(int)round(moy_max/(10.0/j)));
    for (int i='a'; i<='z'; i++) {
        if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("0");
        }
        else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("o");
        }
        else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("-");
        }
        else {
            printf(" ");
        }
    }
    j--;
    printf(" |\n");
    printf("| |Temps (us) |  min  |  max  |  moy  | %3d ",(int)round(moy_max/(10.0/j)));
    for (int i='a'; i<='z'; i++) {
        if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("0");
        }
        else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("o");
        }
        else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("-");
        }
        else {
            printf(" ");
        }
    }
    j--;
    printf(" |\n");
    printf("| |-----------|-------|-------|-------| %3d ",(int)round(moy_max/(10.0/j)));
    for (int i='a'; i<='z'; i++) {
        if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("0");
        }
        else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("o");
        }
        else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("-");
        }
        else {
            printf(" ");
        }
    }
    j--;
    printf(" |\n");
    if (nbl==0) {//zi nb ligne = 0 peux pas affiche de moyenne donc cas particulier on calcule rien
        printf("| |Niveau 0   |  N/A  |  N/A  |  N/A  | %3d ",(int)round(moy_max/(10.0/j)));
        for (int i='a'; i<='z'; i++) {
            if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("0");
            }
            else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("o");
            }
            else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        j--;
        printf(" |\n");
        printf("| |-----------|-------|-------|-------| %3d ",(int)round(moy_max/(10.0/j)));
        for (int i='a'; i<='z'; i++) {
            if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("0");
            }
            else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("o");
            }
            else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        j--;
        printf(" |\n");
        printf("||Tous niveau|  N/A  |  N/A  |  N/A  | %3d ",(int)round(moy_max/(10.0/j)));//N/A = non applicable
        for (int i='a'; i<='z'; i++) {
            if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("0");
            }
            else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("o");
            }
            else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        j--;
        printf(" |\n");
    }
    else {
        printf("| |Niveau 0   |%7.3f|%7.3f|%7.3f| %3d ",min_0[0], max_0[0], moy_0[0]/nbl[0], (int)round(moy_max/(10.0/j)));//affiche la moyenne sur 7 caractère avec 3 décimal
        for (int i='a'; i<='z'; i++) {
            if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("0");
            }
            else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("o");
            }
            else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        j--;
        printf(" |\n");
        printf("| |-----------|-------|-------|-------| %3d ",(int)round(moy_max/(10.0/j)));
        for (int i='a'; i<='z'; i++) {
            if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("0");
            }
            else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("o");
            }
            else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        j--;
        printf(" |\n");
        printf("| |Tous niveau|%7.3f|%7.3f|%7.3f| %3d ", min_all[0], max_all[0], moy_all[0]/nbl[0],(int)round(moy_max/(10.0/j)));
        for (int i='a'; i<='z'; i++) {
            if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("0");
            }
            else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("o");
            }
            else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        j--;
        printf(" |\n");
    }

    printf("| |___________|_______|_______|_______| %3d ",(int)round(moy_max/(10.0/j)));
    for (int i='a'; i<='z'; i++) {
        if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("0");
        }
        else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("o");
        }
        else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("-");
        }
        else {
            printf(" ");
        }
    }
    j--;
    printf(" |\n");

    printf("|                                       %3d ",(int)round(moy_max/(10.0/j)));
    for (int i='a'; i<='z'; i++) {
        if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j && (int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("0");
        }
        else if ((int)round((moy_0[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("o");
        }
        else if ((int)round((moy_all[i-'a'+1]/nbl[i-'a'+1])*10/moy_max)==j) {
            printf("-");
        }
        else {
            printf(" ");
        }
    }
    printf(" |\n");
    printf("|                                       tps ");
    for (int i='a'; i<='z'; i++) {
        printf("%c",i);
    }
    printf(" |\n");
    printf("|                                      (us)  o Niveau 0 - Tous niveaux |\n");
    printf("|______________________________________________________________________|\n");
}

//pour afficher les paramètre
void MenuCorp(char *c1, char *c2, char *c3) {
    int sp=66;
    char sp1[sp];

    for (int i = 0; i < sp-strlen(c1); i++) { sp1[i]=' '; } sp1[sp-strlen(c1)]='\0';

    printf("|______________________________________________________________________|\n");
    printf("|                                                                      |\n");
    printf("|                                                                      |\n");
    switch (c1[0]) {
        case '|': // Affichage des RDV

            break;
        default:
            printf("|   %s %s|\n",c1,sp1);
            break;
    }

    if (c2 != NULL) {
        for (int i = 0; i < sp-strlen(c2); i++) { sp1[i]=' '; } sp1[sp-strlen(c2)]='\0';
        printf("|   %s %s|\n",c2,sp1);
    }
    if (c3 != NULL) {
        sp=57-strlen(c3);
        for (int i = 0; i < sp-strlen(c3); i++) { sp1[i]=' '; } sp1[sp-strlen(c3)]='\0';
        printf("|   %s %s|\n",c3,sp1);
    }
    printf("|                                                                      |\n");
    printf("|                                                                      |\n");
}

//pour afficher les rdv
int MenuCorpR(t_contact *contact, int ab, char *Question) { // Si ab=0 on ajoute un menu pour abandonné l'opération
    int cpt=0;
    int sp=68;
    char sp1[sp], sp2[sp], ch[sp], l[sp+15];
    char h, m;

    printf("|_______________________________________________________________________|\n");
    printf("|                                                                      |\n");
    printf("|                                                                      |\n");
    t_rendezvous *rdv = contact->rendezvous;
    if (rdv == NULL) {
        sprintf(ch, "Aucun rendez-vous pour %s %s",contact->prenom, contact->nom);
        for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
        printf("| %s %s|\n",ch,sp1);

    }
    else {
        sprintf(ch,"Rendez-vous de %s %s",contact->prenom, contact->nom);
        for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
        printf("| %s %s|\n",ch,sp1);
        for (int i = 0; i < strlen(ch); i++) { sp2[i]='-'; } sp2[strlen(ch)]='\0';
        sprintf(l,"| %s%s |\n", sp2, sp1);
        printf("%s", l);
        while (rdv != NULL) {
            cpt++;
// On affiche la date du rendez-vous
            sprintf(ch, "%2d. Date : %02d/%02d/%04d", cpt, rdv->jour, rdv->mois, rdv->annee);
            for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
            printf("| %s %s|\n",ch,sp1);
            // On affiche l'heure du rendez-vous
            sprintf(ch, "    Heure : %02d:%02d", rdv->heure, rdv->minute);
            for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
            printf("| %s %s|\n",ch,sp1);
            // On affiche la durée du rendez-vous
            if (rdv->duree_heure > 1) { h='s'; } else { h=' ';}
            if (rdv->duree_minute > 1) { m='s'; } else { m=' ';}
            if ((rdv->duree_heure !=0) && (rdv->duree_minute !=0)) {
                sprintf(ch, "    Duree : %d heure%c et %d minute%c", rdv->duree_heure, h, rdv->duree_minute, m);
            }
            else if (rdv->duree_heure ==0) {
                sprintf(ch, "    Duree : %d minute%c", rdv->duree_minute, m);
            }
            else if (rdv->duree_minute ==0) {
                sprintf(ch, "    Duree : %d heure%c", rdv->duree_heure, h);
            }
            else {
                sprintf(ch, "    Duree : %d heure%c et %d minute%c", rdv->duree_heure, h, rdv->duree_minute, m);
            }
            for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
            printf("| %s %s|\n",ch,sp1);
            // On affiche l'objet du rendez-vous
            for (int i = 0; i < sp-strlen(rdv->objet)-4; i++) { sp1[i]=' '; } sp1[sp-strlen(rdv->objet)-4]='\0';
            printf("|     %s %s|\n",rdv->objet,sp1);
            printf("%s", l);
            rdv = rdv->next;
        }
    }
    if (ab==0){
        sprintf(ch, "999. <Abandon de l'operation>");
        for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
        printf("| %s %s|\n",ch,sp1);
    }
    if (strcmp(Question,"")!=0){
        printf("|                                                                      |\n");
        for (int i = 0; i < sp-strlen(Question); i++) {  sp1[i]=' '; } sp1[sp-strlen(Question)]='\0';
        printf("| %s %s|\n",Question,sp1);
    }
    printf("|                                                                      |\n");
    return(cpt);
}
//pour afficher les contact
int MenuCorpC(t_contact *contact, int new, char *rech, char *Question) {//corps pour le contact
    int cpt=0;
    int sp=68;
    char sp1[sp], ch[sp], n[4];
    printf("|______________________________________________________________________|\n");//affichage du cadre
    printf("|                                                                      |\n");
    printf("|                                                                      |\n");
    t_contact *c = contact;
    if (c==NULL) { // pas de contact trouvé
        sprintf(ch, "Aucun contact correspondant a la recherche : %s", rech);
        for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';//pour créer une chaine d'espace pour aligner la barre au fond
        printf("| %s %s|\n",ch,sp1);
    }

    if (new==0) {//si new=0 alors affichier la ligne 0. <Nouveau contact>
        sprintf(ch, "  0. <Creation d'un nouveau contact>");
        for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
        printf("| %s %s|\n",ch,sp1);
    }
    while (c != NULL) {//lire les contact
        for (int i=0; i<3; i++){ n[i]=c->nom_prenom[i];} n[3]='\0';//récupère les 3 première lettre de non prénom
        if (strcmp(n, minuscule(rech)) != 0) { // on est plus sur les 3 mêmes caractère
            break;
        }
        cpt++;//nom a 3 meme caractère que la recherche faire plus 1
        sprintf(ch, "%3d. %s %s", cpt, c->prenom, c->nom);
        for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
        printf("| %s %s|\n",ch,sp1);
        c=c->next[0];
    }

    sprintf(ch, "999. <Abandon de l'operation>");//abandonner l'opération en cours
    for (int i = 0; i < sp-strlen(ch); i++) { sp1[i]=' '; } sp1[sp-strlen(ch)]='\0';
    printf("| %s %s|\n",ch,sp1);
    //si Question<>"" alors afiicher un ligne vide + afficher Question
    if (strcmp(Question,"")!=0){
        printf("|                                                                      |\n");
        for (int i = 0; i < sp-strlen(Question); i++) { sp1[i]=' '; } sp1[sp-strlen(Question)]='\0';
        printf("| %s %s|\n",Question,sp1);
    }
    printf("|                                                                      |\n");
    return cpt;
}

int DateValide(int jour, int mois, int annee) {//validé une date
    if (mois < 1 || mois > 12) {//moi entre 1-12 sinon impossible
        return 1;
    }

    int NbJoursparMois[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//par rapport au mois on peux pas dépasser pour chaque mois
    if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0)) { // Année bixestile
        NbJoursparMois[1] = 29;
    }

    if (jour < 1 || jour > NbJoursparMois[mois - 1]) {//jour entre 1 et le nombre de jours du mois
        return 1;//retourne faux
    }

    return 0;
}

int HeureValide(int heure, int minute) {//heure valide
    if (heure < 0 || heure > 23) {//heure négative ou supérieur à 23 impossible
        return 1;
    }
    if (minute < 0 || minute > 59) {//minute négative ou supérieur à 59 impossible
        return 1;
    }

    return 0;
}

int DureeValide(int heure, int minute) {//renvoie si la durée est valide ou pas c'est à dire
    if (heure < 0 || heure > 23) {//heure négative ou supérieur à 23 impossible
        return 1;
    }
    if (minute < 0 || minute > 59) {//minute négative ou supérieur à 59 impossible
        return 1;
    }
    if (minute == 0 && heure == 0) {//impossible si 0h ou 0min
        return 1;
    }

    return 0;
}