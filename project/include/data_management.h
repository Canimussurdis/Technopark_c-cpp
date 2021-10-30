#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
* Создать структуру для хранения информации о воздушных судах:
* марке (названии производителя), модели, назначении (грузовое, пассажирское и т.д.), численности экипажа и дальности полета.
* Составить с ее использованием программу вывода информации обо всех известных судах
* с группировкой по названию производителя и сортировкой по возрастанию дальности полета.
*/

typedef struct aircraft_node {
	struct {
		size_t name;
		size_t model;
		size_t usage;
		size_t crew_size;
		size_t range_of_flight;
		char *aircraft_name;
	} data;
	struct aircraft_node *next;
}  aircraft_node;

// Creates a new node.
aircraft_node* create_node();

// Frees up the memory allocated to the node.
void free_node(aircraft_node* node);

// Adds insertable to the linked list before the first node greater than or equal to insertable.
int insert_node(aircraft_node** head, aircraft_node* insertable);

// Frees up the memory allocated for the list nodes.
void free_list(aircraft_node* head);

/*
 * Implementation of the < comparison for double
 * @return 0, if lhs and rhs are almost equal or lhs > rhs. Otherwise, 1
 */
int is_less(const double lhs, const double rhs);




