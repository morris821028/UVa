#include "employee.h"
#include <stdio.h>

int relation(Employee *x, Employee *y) {
	Employee *tx = x, *ty = y;
	while (tx != tx->boss) {
		if (tx == y)	return 1;
		tx = tx->boss;
	}
	if (tx == y)	return 1;
	while (ty != ty->boss) {
		if (ty == x)	return 2;
		ty = ty->boss;
	}
	if (ty == x)	return 2;
	if (tx == ty)
		return 3;
	return 4;
}
