#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <locale.h>



#include "cell.h"
#include "list.h"
#include "timer.h"
int main(void) {
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
    cell[i] = create_cell(i + 1, tab[i] + 1);// on crée les cellules
    for (intj = 0; j < n; j++) {
        insere_cell(list, cell[i], j);// on les insère dans la liste
    }
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
}
