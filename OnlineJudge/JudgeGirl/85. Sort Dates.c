#include <stdio.h>
#incldue <stdlib.h>

typedef struct {
	int y, m, d;
} Date;

Date D[1000000];
int cmp(const void *x, const void *y) {
	Date *a = (Date*) x;
	Date *b = (Date*) y;
	if (a->y < b->y)	return -1;
	if (a->y > b->y)	return 1;
	if (a->m < b->m)	return -1;
	if (a->m > b->m)	return 1;
	if (a->d < b->d)	return -1;
	if (a->d > b->d)	return 1;
	return 0;
}
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%d %d %d", &D[i].y, &D[i].m, &D[i].d);
		qsort(D, n, sizeof(Date), cmp);
		for (int i = 0; i < n; i++)
			printf("%d %d %d\n", D[i].y, D[i].m, D[i].d);
	}
	return 0;
}

