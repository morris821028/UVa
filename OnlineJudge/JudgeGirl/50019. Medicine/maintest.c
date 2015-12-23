#include "medicine.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void test_all() {
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
	test_all();
	return 0;
}
