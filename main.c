#include <stdio.h>
#include <stdlib.h>
#include "cell.h"

int main()
{
    // -------------------- TESTS --------------------

    // Tests : Cellule
    p_cell testCell = (p_cell) malloc(sizeof(t_cell));
    testCell->value = 19;
    testCell->next = NULL;

    printf("Valeur de la cellule : %d\n", testCell->value);

    // Empêcher le terminal de se fermer instantanément
    system("pause");
    return 0;
}
