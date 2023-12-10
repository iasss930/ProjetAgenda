#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <locale.h>



#include "cell.h"
#include "list.h"
#include "timer.h"
#include "agenda.h

int main(){
    setlocale(LC_ALL, "fr_FR.UTF-8");
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
    return 0;
}


/*partie 1 et 2
int main() {
    t_d_list *list = create_list(5);
    fill_list(list);
    display_all(*list);
    display_level(*list, 7);
    printf("%d", dicho_search(*list, 9));
    return 0;
}
*/
