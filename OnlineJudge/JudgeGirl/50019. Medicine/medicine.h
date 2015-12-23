#ifndef MEDICINE_H
#define MEDICINE_H

typedef struct {
	char name[128];
	int w;
} Ingredient;
typedef struct {
	Ingredient a[2], b[5];
	int an, bn;
} Medicine;

void init(Medicine *medicine);
int addActive(Medicine *medicine, char *name, int weight);
int addInactive(Medicine *medicine, char *name, int weight);
void print(Medicine *medicine);
int totalWeight(Medicine *medicine);
char *maxIngredient(Medicine *medicine);

#endif
