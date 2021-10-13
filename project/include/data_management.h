#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
* ������� ��������� ��� �������� ���������� � ��������� �����:
* ����� (�������� �������������), ������, ���������� (��������, ������������ � �.�.), ����������� ������� � ��������� ������.
* ��������� � �� �������������� ��������� ������ ���������� ��� ���� ��������� �����
* � ������������ �� �������� ������������� � ����������� �� ����������� ��������� ������.
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

aircraft_node* create_node();

void free_node(aircraft_node* node);

int insert_node(aircraft_node** head, aircraft_node* insertable);

/**
 * Frees up the memory allocated for the list nodes.
 * @param head - pointer to the first item in the list. If it is null, then the function does nothing.
 */
void free_list(aircraft_node* head);

/**
 * Implementation of the < comparison for double
 * @param lhs
 * @param rhs
 * @return 0, if lhs and rhs are almost equal or lhs > rhs. Otherwise, 1
 */
int is_less(const double lhs, const double rhs);




