#include "medicine.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/*
void init(Medicine *medicine);
int addActive(Medicine *medicine, char *name, int weight);
int addInactive(Medicine *medicine, char *name, int weight);
void print(Medicine *medicine);
int totalWeight(Medicine *medicine);
char *maxIngredient(Medicine *medicine);
*/
void test_spec0() {
	int n, m;
	scanf("%d %d", &n, &m);
	Medicine *medi = (Medicine *) malloc(sizeof(Medicine) * n);
	int cmd, mid, weight;
	char name[128];
	for (int i = 0; i < n; i++)
		init(&medi[i]);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &cmd, &mid);
		if (cmd == 1) { 		// addActive
			scanf("%s %d", name, &weight);
			int af = addActive(&medi[mid], name, weight);
			printf("af %d\n", af);
		} else if (cmd == 2) {	// addInactive
			assert(false);
		} else if (cmd == 3) {	// print
			assert(false);
		} else if (cmd == 4) {	// totalWeight
			printf("weight = %d\n", totalWeight(&medi[mid]));
		} else if (cmd == 5) {	// maxIngredient
			assert(false);
		}
	}
}
void test_spec1() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	Medicine *medi = (Medicine *) malloc(sizeof(Medicine) * n);
	int cmd, mid, weight;
	char name[128];
	for (int i = 0; i < n; i++)
		init(&medi[i]);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &cmd, &mid);
		if (cmd == 1) { 		// addActive
			scanf("%s %d", name, &weight);
			int af = addActive(&medi[mid], name, weight);
			printf("af %d\n", af);
		} else if (cmd == 2) {	// addInactive
			assert(false);
		} else if (cmd == 3) {	// print
			assert(false);
		} else if (cmd == 4) {	// totalWeight
			printf("weight = %d\n", totalWeight(&medi[mid]));
		} else if (cmd == 5) {	// maxIngredient
			char *ret = maxIngredient(&medi[mid]);
			printf("main ingredient = %s\n", ret == NULL ? "NOT FOUND" : ret);
		}
	}
}
void test_spec2() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	Medicine *medi = (Medicine *) malloc(sizeof(Medicine) * n);
	int cmd, mid, weight;
	char name[128];
	for (int i = 0; i < n; i++)
		init(&medi[i]);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &cmd, &mid);
		if (cmd == 1) { 		// addActive
			scanf("%s %d", name, &weight);
			int af = addActive(&medi[mid], name, weight);
			printf("af %d\n", af);
		} else if (cmd == 2) {	// addInactive
			scanf("%s %d", name, &weight);
			int bf = addInactive(&medi[mid], name, weight);
			printf("bf %d\n", bf);
		} else if (cmd == 3) {	// print
			assert(false);
		} else if (cmd == 4) {	// totalWeight
			printf("weight = %d\n", totalWeight(&medi[mid]));
		} else if (cmd == 5) {	// maxIngredient
			char *ret = maxIngredient(&medi[mid]);
			printf("main ingredient = %s\n", ret == NULL ? "NOT FOUND" : ret);
		}
	}
}
void test_spec4() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	Medicine *medi = (Medicine *) malloc(sizeof(Medicine) * n);
	int cmd, mid, weight;
	char name[128];
	for (int i = 0; i < n; i++)
		init(&medi[i]);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &cmd, &mid);
		if (cmd == 1) { 		// addActive
			scanf("%s %d", name, &weight);
			int af = addActive(&medi[mid], name, weight);
			printf("af %d\n", af);
		} else if (cmd == 2) {	// addInactive
			scanf("%s %d", name, &weight);
			int bf = addInactive(&medi[mid], name, weight);
			printf("bf %d\n", bf);
		} else if (cmd == 3) {	// print
			print(&medi[mid]);
		} else if (cmd == 4) {	// totalWeight
			printf("weight = %d\n", totalWeight(&medi[mid]));
		} else if (cmd == 5) {	// maxIngredient
			char *ret = maxIngredient(&medi[mid]);
			printf("main ingredient = %s\n", ret == NULL ? "NOT FOUND" : ret);
		}
	}
}
int main() {
	int spec;
	while (scanf("%d", &spec) == 1) {
		if (spec == 0) {
			test_spec0();
		} else if (spec == 1) {
			test_spec1();
		} else if (spec == 2) {
			test_spec2();
		} else if (spec == 3) {
			test_spec2();
		} else if (spec == 4) {
			test_spec4();
		}
	}
	return 0;
}
/*
[10%] Implement init, addActive, and totalWeight. It is guaranteed that we will not add more than 2 active ingredients.
[15%] Implement init, addActive, totalWeight, and maxIngredient. It is guaranteed that we will not add more than 2 active ingredients.
[15%] Implement init, addActive, addInactive, totalWeight, and maxIngredient. It is guaranteed that we will not add more than 2 active ingredients or 5 inactive ingredients.
[30%] Implement init, addActive, addInactive, and totalWeight. We may add more than 2 active ingredients or 5 inactive ingredients.
[30%] Implement all fucntions including print.
*/
