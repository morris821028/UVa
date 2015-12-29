#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"

void init_storage(Employee **storage, int n) {
	(*storage) = (Employee *)malloc(sizeof(Employee) * n);
}
void free_storage(Employee **storage) {
	free(*storage);
	*storage = 0;
}
Employee* find_employee_by_id(Employee *set, int n, int id) {
	for (int i = 0; i < n; i++) {
		if (set[i].id == id)
			return &(set[i]);
	}
	return NULL;
}
Employee* find_employee_by_name(Employee *set, int n, const char *first_name, const char *last_name) {
	for (int i = 0; i < n; i++) {
		if (!strcmp(set[i].first_name, first_name) &&
			!strcmp(set[i].last_name, last_name))
			return &(set[i]);
	}
	return NULL;
}
Employee* find_root_boss(Employee *set, int n, Employee *e) {
	while (e->boss_id != e->id) {
		for (int i = 0; i < n; i++)
			if (e->boss_id == set[i].id)
				e = &(set[i]);
	}
	return e;
}
int check_relationship(Employee *set, int n, Employee *A, Employee *B) {
	Employee *x, *y;
	Employee *bA, *bB;
	bA = find_root_boss(set, n, A);
	bB = find_root_boss(set, n, B);
	if (bA != bB)	return 4;
	x = A, y = B;
	do {
		x = find_employee_by_id(set, n, x->boss_id);
		if (x == B)	return 1;
	} while (x != bA);
	do {
		y = find_employee_by_id(set, n, y->boss_id);
		if (y == A)	return 2;
	} while (y != bB);
	return 3;
}


