#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <locale.h>



#include "cell.h"
#include "list.h"
#include "timer.h"
#include "agenda.h"
#include "menu.h"

int main(){
    t_agenda *agenda = create_agenda();
    int choix = 1;
    while(choix != 0){
        printf("Que voulez-vous faire?\n\n"
               "1. ajouter un contact\n"
               "2. afficher un niveau de l'agenda\n"
               "3. afficher tout l'agenda\n"
               "0. quitter\n");
        scanf("%d", &choix);
        switch (choix) {
            case 1 :
                add_contact(agenda);
            case 2:
                affiche_level(agenda);
            case 3:
                display_agenda(*agenda);
            break;
        }
    }
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
