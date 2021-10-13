#include <stdio.h>
#include "operations.h"

const int PARAMETERS_TO_READ = 6;

aircraft_node* read_aircraft_node() {
    aircraft_node* node = create_node();
    if (!node) {
        return NULL;
    }
    if (scanf("%zd %zd %zd %zd %zd %ms\n", &node->data.name, &node->data.model, &node->data.usage,
              &node->data.crew_size, &node->data.range_of_flight, &node->data.aircraft_name)
        != PARAMETERS_TO_READ || !node->data.name ||!node->data.model || !node->data.usage
        || !node->data.crew_size || !node->data.range_of_flight) {
        free_node(node);
        return NULL;
    }
    return node;
}

void print_list(const aircraft_node* head) {
    while (head) {
        if (head->data.aircraft_name) {
            printf("%zd %zd %zd %zd %zd %s\n", head->data.name, head->data.model, head->data.usage, 
            head->data.crew_size, head->data.range_of_flight, head->data.aircraft_name);
        } else {
            printf("%zd %zd %zd %zd %zd invalid_aircraft_name\n", head->data.name, head->data.model, 
            head->data.usage, head->data.crew_size, head->data.range_of_flight);
        }
        head = head->next;
    }
}

aircraft_node* get_ordered_list() {
    aircraft_node* head = NULL;
    aircraft_node* new = read_aircraft_node();
    while (new) {
        if (insert_node(&head, new) < 0) {
            free_list(head);
            free_node(new);
            head = NULL;
            break;
        }
        new = read_aircraft_node();
    }
    return head;
}
