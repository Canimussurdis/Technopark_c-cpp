#include <stdio.h>
#include "operations.h"

int main() {
    aircraft_node* head = get_ordered_list();
    if (!head) {
        printf("Cannot get a list");
        return 1;
    }
    print_list(head);
    free_list(head);
    return 0;
}