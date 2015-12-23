#include "medicine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void init(Medicine *medicine) {
	medicine->an = medicine->bn = 0;
}
int addActive(Medicine *medicine, char *name, int weight) {
	int an = medicine->an;
	for (int i = 0; i < an; i++) {
		if (!strcmp(medicine->a[i].name, name)) {
			medicine->a[i].w += weight;
			return medicine->a[i].w;
		}
	}
	if (an == 2)	return -1;
	medicine->a[an].w = weight;
	strcpy(medicine->a[an].name, name);
	medicine->an++;
	return weight;
}
int addInactive(Medicine *medicine, char *name, int weight) {
	int bn = medicine->bn;
	for (int i = 0; i < bn; i++) {
		if (!strcmp(medicine->b[i].name, name)) {
			medicine->b[i].w += weight;
			return medicine->b[i].w;
		}
	}
	if (bn == 5)	return -1;
	medicine->b[bn].w = weight;
	strcpy(medicine->b[bn].name, name);
	medicine->bn++;
	return weight;
}
static int ingcmp(const void *a, const void *b) {
	Ingredient *x = *(Ingredient **)a, *y = *(Ingredient **)b;
	if (x->w != y->w)	return y->w - x->w;
	return strcmp(x->name, y->name);
}
void print(Medicine *medicine) {
	int an = medicine->an,
		bn = medicine->bn;
	Ingredient *a[2], *b[5];
	for (int i = 0; i < an; i++)
		a[i] = &(medicine->a[i]);
	for (int i = 0; i < bn; i++)
		b[i] = &(medicine->b[i]);
	qsort(a, an, sizeof(Ingredient*), ingcmp);
	qsort(b, bn, sizeof(Ingredient*), ingcmp);
	puts("----- Active Ingredient begin   -----");
	for (int i = 0; i < an; i++)
		printf("%d %s\n", a[i]->w, a[i]->name);
	puts("----- end                       -----");
	puts("----- Inactive Ingredient begin -----");
	for (int i = 0; i < bn; i++)
		printf("%d %s\n", b[i]->w, b[i]->name);
	puts("----- end                       -----");
}
int totalWeight(Medicine *medicine) {
	int w = 0;
	for (int i = 0; i < medicine->an; i++)
		w += medicine->a[i].w;
	for (int i = 0; i < medicine->bn; i++)
		w += medicine->b[i].w;
	return w;
}
char *maxIngredient(Medicine *medicine) {
	Ingredient *c[10];
	int cn = 0;
	for (int i = 0; i < medicine->an; i++)
		c[cn++] = &(medicine->a[i]);
	for (int i = 0; i < medicine->bn; i++)
		c[cn++] = &(medicine->b[i]);
	if (cn == 0)	return NULL;
	qsort(c, cn, sizeof(Ingredient*), ingcmp);
	return c[0]->name;
}
