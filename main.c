#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <locale.h>



#include "cell.h"
#include "list.h"
#include "timer.h"
#include "partie3.h"


int main(void) {
    setlocale(LC_ALL, "fr_FR.UTF-8"); // Définir la locale en UTF-8
    //créer un agenda
    t_agenda *agenda = creerAgenda();
    t_recherchecontact search;
    char *nom;
    char *prenom;
    int jour, mois, annee, heure, minutes, heure2, minutes2;
    char *objet;
    t_contact *contact;
    t_rendezvous *rdv;
    int choix;
    char c, t[60], t1[60];
    char date[10], time[5], chx[5];
    char aff=' ';
    int nbc, nbr;

    t[0]='\0'; t1[0]='\0';
    // Vérifier l'existance d'une sauvegarde. Si oui La charger ? si non afficher menu
    if (ExisteSauvegarde() == 0) {
        MenuEntete(1);
        MenuCorp("Une sauvegarde a ete trouvee", "Voulez-vous la charger ([O]ui/[N]on) ?", NULL);
        MenuPied();
        while (c = getchar()) {
            while (getchar() != '\n') { } // vider le buffer si saisie de plusieurs caracteres
            if (c == 'o' || c == 'O'){
                ImportContactRdv(agenda);
                break;
            }
            else if (c == 'n' || c == 'N') {
                break;
            }
            else {
                printf("/!\\ Saisie invalide /!\\. La saisie de O ou N est attendue : ");
            }
        }
    }
    // Affiche le menu tant que pas quitter
    strcpy(t, "Veuillez choisir une lettre entre C, A, S, F ou Q ?");


    //char str[4]; for (int j = 0; j < 50000; ++j) { for (int i = 0; i < 3; ++i) { str[i] = (char)(rand() % 26 + 'a'); } str[3] = '\0'; Recherche(agenda, str, "", 0); } //Génération aléatoire de 50000 chaines de 3 caractères pour remplir les logs pour avoir un graph cg TpsMoy.xls

    while (1 == 1) {
        MenuEntete(0);
        switch (aff) {
            case 'R': // affichage des rdv
                MenuCorpR(search.current, 1, "");
                aff=' ';
                break;
            default:
                if (t1[0]=='\0') {
                    MenuCorp(t, NULL, NULL);
                }
                else {
                    MenuCorp(t, t1, NULL);
                }
                break;
        }
        MenuPied();
        c = getchar();
        while (getchar() != '\n') { } // vider le buffer si saisie de plusieurs caracteres
        switch (c) {
            case 'c':
            case 'C':
                MenuEntete(1);
                MenuCorp("Saisir un nom (min 3 car.) :", NULL, NULL);
                MenuPied();
                nom = scanString("");
                MenuEntete(1);
                MenuCorp("Saisir un prenom (min 3 car.) :", NULL, NULL);
                MenuPied();
                prenom = scanString("");
                search = Recherche(agenda, nom, prenom, 0);
                strcpy(t1, "Veuillez choisir une lettre entre C, A, S, F ou Q ?");
                strcpy(t, prenom);
                strcat(t, " ");
                strcat(t, nom);
                if (search.niveau == -1) {
                    strcat(t, " existe deja");
                }
                else {
                    contact = creerContact(nom, prenom, search.niveau);
                    addContactTri(agenda, contact, search.prec, search.current);
                    strcat(t, " a ete ajoute");
                }
                break;
            case 'a':
            case 'A':
                MenuEntete(1);
                MenuCorp("Saisir les 3 premiers caractere d'un nom :", NULL, NULL);
                MenuPied();
                nom = scanString("");
                nom[3]='\0';
                search = Recherche(agenda, nom, "", 0);
                MenuEntete(1);
                nbc=MenuCorpC(search.current, 0, nom, "toto ?");
                MenuPied();
                if (nbc=='0') { // Pas de choix
                    sprintf(t, "Aucun nom ne correspond à \"%s\"", nom);
                    t1[0]='\0';
                    break;
                }
                else {
                    do {
                        fgets(chx, sizeof(chx), stdin);
                        if (sscanf(chx, "%d", &choix) == 1) {
                            if (choix == 0) { // Nouveau contact
                                MenuEntete(1);
                                MenuCorp("Saisir un nom (min 3 car.) :", NULL, NULL);
                                MenuPied();
                                nom = scanString("");
                                MenuEntete(1);
                                MenuCorp("Saisir un prenom (min 3 car.) :", NULL, NULL);
                                MenuPied();
                                prenom = scanString("");
                                break;
                            }
                            else if (choix > 0 && choix <= nbc) { // création rdv du contact sélectionné
                                for (int i = 0; i < choix - 1; i++) { search.current = search.current->next[0];}
                                nom = (char *)malloc(strlen(search.current->nom) + 1);
                                strcpy(nom, search.current->nom);
                                prenom = (char *)malloc(strlen(search.current->prenom) + 1);
                                strcpy(prenom, search.current->prenom);
                                break;
                            }
                            else if (choix == 999) { // Abandon de l'opération
                                strcpy(t, "Abandon de l'operation.");
                                t1[0]='\0';
                                break;
                            }
                        }
                        printf("/!\\ Saisie invalide /!\\. La saisie doit être un nombre entre 0 et %d ou 999 : ",nbc);
                    } while (1==1);
                }
                if (choix == 999) { // Abandon de l'opération
                    break;
                }
                MenuEntete(1);
                MenuCorp("Saisir la date du rendez-vous (jj/mm/aaaa) :", NULL, NULL);
                MenuPied();
                do {
                    fgets(date, sizeof(date), stdin);
                    if (sscanf(date, "%d/%d/%d", &jour, &mois, &annee) == 3) {
                        if (DateValide(jour, mois, annee) == 0) {
                            break;
                        }
                    }
                    printf("/!\\ Saisie invalide /!\\. La saisie doit être une date valide au format jj/mm/aaaa : ");
                } while (1==1);
                MenuEntete(1);
                MenuCorp("Saisir l'heure du rendez-vous (hh:mm) :", NULL, NULL);
                MenuPied();
                do {
                    fgets(time, sizeof(time), stdin);
                    if (sscanf(time, "%d:%d", &heure, &minutes) == 2) {
                        if (HeureValide(heure, minutes) == 0) {
                            break;
                        }
                    }
                    printf("/!\\ Saisie invalide /!\\. La saisie doit être une heure valide au format hh:mm : ");
                } while (1==1);
                MenuEntete(1);
                MenuCorp("Saisir la durée du rendez-vous (hh:mm) :", NULL, NULL);
                MenuPied();
                do {
                    fgets(time, sizeof(time), stdin);
                    if (sscanf(time, "%d:%d", &heure, &minutes) == 2) {
                        if (DureeValide(heure, minutes) == 0) {
                            break;
                        }
                    }
                    printf("/!\\ Saisie invalide /!\\. La saisie doit être une heure valide au format hh:mm : ");
                } while (1==1);
                MenuEntete(1);
                MenuCorp("Saisir l'objet du rendez-vous (min 3 car.) :", NULL, NULL);
                MenuPied();
                objet = scanString("");

                search = Recherche(agenda, nom, prenom, 0);
                strcpy(t, "Le rendez-vous a ete ajoute a ");
                strcpy(t1, "Veuillez choisir une lettre entre C, A, S, F ou Q ?");
                strcat(t, prenom);
                strcat(t, " ");
                strcat(t, nom);
                if (search.niveau != -1) {
                    contact = creerContact(nom, prenom, search.niveau);
                    addContactTri(agenda, contact, search.prec, search.current);
                    search.current=contact;
                }
                rdv = creerRendezVous(jour, mois, annee, heure, minutes, heure2, minutes2, objet);
                ajouterRendezVous(search.current, rdv);
                break;
            case 's':
            case 'S':
                MenuEntete(1);
                MenuCorp("Saisir les 3 premiers caractere d'un nom :", NULL, NULL);
                MenuPied();
                nom = scanString("");
                nom[3]='\0';
                search = Recherche(agenda, nom, "", 0);
                MenuEntete(1);
                nbc=MenuCorpC(search.current, 1, nom, "");
                MenuPied();
                if (nbc=='0') { // Pas de choix
                    sprintf(t, "Aucun nom ne correspond à \"%s\"", nom);
                    t1[0]='\0';
                    break;
                }
                else {
                    do {
                        fgets(chx, sizeof(chx), stdin);
                        if (sscanf(chx, "%d", &choix) == 1) {
                            if (choix > 0 && choix <= nbc) {
                                for (int i = 0; i < choix - 1; i++) { search.current = search.current->next[0];}
                                MenuEntete(1);
                                nbr=MenuCorpR(search.current, 0, "Titi ?");
                                MenuPied();
                                do {
                                    fgets(chx, sizeof(chx), stdin);
                                    if (sscanf(chx, "%d", &choix) == 1) {
                                        if (choix > 0 && choix <= nbr) {
                                            SupRendezVous(search.current, choix);
                                            t1[0]='\0';
                                            strcpy(t, "Le rendez-vous de ");
                                            strcat(t, search.current->prenom);
                                            strcat(t, " ");
                                            strcat(t, search.current->nom);
                                            strcat(t, " a ete supprime");
                                            break;
                                        }
                                        else if (choix == 999) { // Abandon de l'opération
                                            strcpy(t, "Abandon de l'operation.");
                                            t1[0]='\0';
                                            break;
                                        }
                                    }
                                    printf("/!\\ Saisie invalide /!\\. La saisie doit être un entier entre 1 et %d ou 999 : ", nbr);
                                } while (1==1);
                                break;
                            }
                            else if (choix == 999) {  // Abandon de l'opération
                                break;
                            }
                        }
                        printf("/!\\ Saisie invalide /!\\. La saisie doit être un entier entre 1 et %d ou 999 : ", nbc);
                    } while (1==1);
                }
                break;
            case 'f':
            case 'F':
                MenuEntete(1);
                MenuCorp("Saisir les 3 premiers caractere d'un nom :", NULL, NULL);
                MenuPied();
                nom = scanString("");
                nom[3]='\0';
                search = Recherche(agenda, nom, "", 0);
                MenuEntete(1);
                nbc=MenuCorpC(search.current, 1, nom, "toto ?");
                MenuPied();
                if (nbc=='0') { // Pas de choix
                    sprintf(t, "Aucun nom ne correspond à \"%s\"", nom);
                    t1[0]='\0';
                    break;
                }
                else {
                    do {
                        fgets(chx, sizeof(chx), stdin);
                        if (sscanf(chx, "%d", &choix) == 1) {
                            if (choix > 0 && choix <= nbc) {
                                for (int i = 0; i < choix - 1; i++) { search.current = search.current->next[0];}
                                t[0]='\0';
                                t1[0]='\0';
                                aff='R';
                                break;
                            }
                            else if (choix == 999) { // Abandon de l'opération
                                strcpy(t, "Abandon de l'operation.");
                                t1[0]='\0';
                                break;
                            }
                        }
                        printf("/!\\ Saisie invalide /!\\. La saisie doit être un nombre entre 1 et %d ou 999 : ",nbc);
                    } while (1==1);
                }
                break;
            case 'q':
            case 'Q':
                if (SauvegardePossible() == 0) {
                    MenuEntete(1);
                    MenuCorp("Voulez-vous sauvegarder l'agenda ([O]ui/[N]on) ?", NULL, NULL);
                    MenuPied();
                    while (c = getchar()) {
                        while (getchar() != '\n') { } // vider le buffer si saisie de plusieurs caracteres
                        if (c == 'o' || c == 'O'){
                            ExportContactRdv(agenda);
                            break;
                        }
                        else if (c == 'n' || c == 'N') {
                            break;
                        }
                        else {
                            printf("/!\\ Saisie invalide /!\\. La saisie de O ou N est attendue : ");
                        }
                    }
                }
                exit(0);
                break;
            default:
                strcpy(t,"Saisie invalide. C, A, S, F ou Q est attendue : ");
                break;
        }
    }


    free(agenda);// Libération de la mémoire


    //proposer une complétion après les 3 première lettres (vérifier si bien ca attendu)
    //fournir le temps de calcul d'insertion pas fait juste fait pour la recherche

    //
    return 0;
}

/*int main(void) {
  //main partie 2
  time_t t;
  time(&t);
  srand(t);
  int n = rand() % 12 + 1;
  int size = pow(2, n) - 1;
  int tab[size];
  for (int i = 0; i < size; i++) { // initialisation du tableau des niveau à 0
    tab[i] = 0;
  }
  int a = 1;
  for (int k = 0; k < size; k++) { // pour l'afficher le tableau
    // printf("%d", tab[k]);
  }
  // printf("\n");
  for (int i = 1; i < n; i++) { // parcours le tableau de niveau
    a = a * 2;                  // on double l'incrémentation du tableau

    for (int j = a - 1; j < size; j += a) { // pour chaque niveau on ajoute 1
      tab[j]++;
    }
    for (int k = 0; k < size; k++) { // pour l'affichage
      // printf("%d", tab[k]);
    }
    // printf("\n");
  }

  t_d_list *list = create_list(n); // on crée la liste vide
  t_d_cell *cell[size];
  for (int i = 0; i < size; i++) {
    cell[i] = create_cell(i + 1, tab[i] + 1); // on crée les cellules
    insert_cell(list, cell[i]);               // on les insère dans la liste
  }
  //  display_all_levels(list); // on affiche la liste

  clock_t debut, fin;
  double temps;

  FILE *log_file = fopen("log.txt", "a");
  char format[] = "%d\t%s\t%s\n";
  int level = n;
  char time_lvl0[15];
  char time_all_levels[15];

  printf("niveau\trecherche\ttps\titérations\n");
  for (int j = 2; j < 3; j++) {
    // startTimer();
    debut = clock(); // Enregistrez le temps de début
    for (int i = 0; i < pow(10, j + 3); i++) {
      classical_search(list, rand() % size + 1, 0);
    }
    // stopTimer();
    fin = clock(); // Enregistrez le temps de fin
    // displayTime();
    sprintf(time_lvl0,"%f",((double)(fin - debut)) / CLOCKS_PER_SEC * 1000);
    //time_lvl0 = ((char)(((double)(fin - debut)) / CLOCKS_PER_SEC * 1000)) +
'\0';

    // printf("%d\tstandard\t%f\t%.0f\n", n,
    //   ((double)(fin - debut)) / CLOCKS_PER_SEC * 1000, pow(10, j + 3));
    // time_lvl0 = getTimeAsString(); // fonction du module timer

    // startTimer();
    debut = clock(); // Enregistrez le temps de début
    for (int i = 0; i < pow(10, j + 3); i++) {
      expert_search(list, list->head[n - 1], NULL, rand() % size + 1, n - 1);
    }
    // stopTimer();
    fin = clock(); // Enregistrez le temps de fin
    // displayTime();
    // time_all_levels = getTimeAsString();
    sprintf(time_all_levels,"%f",((double)(fin - debut)) / CLOCKS_PER_SEC *
1000);
    //time_all_levels = ((char)(((double)(fin - debut)) / CLOCKS_PER_SEC *
1000)) + '\0';

    //  printf("%d\tavancée\t%f\t%.0f\n", n,
    //       ((double)(fin - debut)) / CLOCKS_PER_SEC * 1000, pow(10, j + 3));
   fprintf(log_file, format, level, time_lvl0, time_all_levels);
  }

  fclose(log_file);
  return 0;
}*/

/*
int main(void) {
//Partie 1 on teste les fonction du main
  t_d_list *list = create_list(5);
  display_all_levels(list);
  t_d_cell *cell1 = create_cell(56, 3);
  t_d_cell *cell2 = create_cell(31, 2);
  t_d_cell *cell3 = create_cell(32, 5);
  t_d_cell *cell4 = create_cell(18, 4);
  t_d_cell *cell5 = create_cell(25, 1);
  t_d_cell *cell6 = create_cell(59, 1);
  t_d_cell *cell7 = create_cell(58, 5);
  t_d_cell *cell8 = create_cell(91, 3);
  insert_cell(list, cell1);
  insert_cell(list, cell2);
  insert_cell(list, cell3);
  insert_cell(list, cell4);
  insert_cell(list, cell5);
  insert_cell(list, cell6);
  insert_cell(list, cell7);
  insert_cell(list, cell8);
  printf(".........................\n");
  display_all_levels(list);
  return 0;
}
*/
