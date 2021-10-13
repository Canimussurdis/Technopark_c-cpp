#pragma once
#include "data_management.h"

/**
 * Creates a node and reads the aircrafts parameters to it from stdin
 * @return created node or NULL
 */
aircraft_node* read_aircraft_node();

/**
 * Outputs the aircraft parameters to stdout. If the country name is represented by an empty pointer,
 * "error_aircraft_name" will be printed instead.
 * @param head - pointer to the first item in the list. If it is null, then the function does nothing.
 */
void print_list(const aircraft_node* head);

/**
 * Generates an ordered list of aircrafts based on data from stdin
 * @return pointer to the first item in the list or NULL
 */
aircraft_node* get_ordered_list();