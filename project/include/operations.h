#pragma once
#include "data_management.h"

/*
 * Creates a node and reads the aircrafts parameters to it from stdin
 */
aircraft_node* read_aircraft_node();

/*
 * Outputs the aircraft parameters to stdout. If the country name is represented by an empty pointer,
 */
void print_list(const aircraft_node* head);

/*
 * Generates an ordered list of aircrafts based on data from stdin
 */
aircraft_node* get_ordered_list();
