#include <stdio.h>
#include "list.h"

int main() {
    t_d_list *list = create_list(5);
    fill_list(list);
    display_all(*list);
    return 0;
}
