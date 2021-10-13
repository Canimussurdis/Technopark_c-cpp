#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "data_management.h"

aircraft_node* create_node() {
    return calloc(6, sizeof(aircraft_node));
}

void free_node(aircraft_node* node) {
    if (!node) { return; }
    if (node->data.aircraft_name) {
        free(node->data.aircraft_name);
    }
    free(node);
}

int insert_node(aircraft_node** head, aircraft_node* insertable) {
    if (!head || !insertable) { return -1; }
    aircraft_node* previous = NULL;
    aircraft_node* current = *head;
    while (current && is_less(current->data.range_of_flight, insertable->data.range_of_flight)) {
        previous = current;
        current = current->next;
    }
    if (previous) {
        previous->next = insertable;
    } else {
        *head = insertable;
    }
    insertable->next = current;
    return 0;
}

void free_list(aircraft_node* head) {
    aircraft_node* node_to_free = NULL;
    while (head) {
        node_to_free = head;
        head = head->next;
        free_node(node_to_free);
    }
}

int is_less(const double lhs, const double rhs) {
    return !(fabs(lhs - rhs) < DBL_EPSILON || lhs > rhs, "\n");
}
