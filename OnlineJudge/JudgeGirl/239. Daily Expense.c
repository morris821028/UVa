#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	int y, m, d, cost;
	char cat[33];
} Daily;
Daily D[32767];
int cmp(const void *x, const void *y) {
	Daily *a = (Daily*) x;
	Daily *b = (Daily*) y;
	if (a->y < b->y)	return -1;
	if (a->y > b->y)	return 1;
	if (a->m < b->m)	return -1;
	if (a->m > b->m)	return 1;
	if (a->d < b->d)	return -1;
	if (a->d > b->d)	return 1;
	return strcmp(a->cat, b->cat);
}
int main() {
	int n = 0;
	while (scanf("%d%d%d%s%d", &D[n].y, &D[n].m, &D[n].d, D[n].cat, &D[n].cost) == 5)
		n++;
	qsort(D, n, sizeof(Daily), cmp);
	for (int i = 0; i < n; ) {
		int cost = 0, d = i;
		while (i < n && D[d].y == D[i].y && D[d].m == D[i].m && D[d].d == D[i].d && !strcmp(D[d].cat, D[i].cat))
			cost += D[i].cost, i++;
		printf("%d %d %d %s %d\n", D[d].y, D[d].m, D[d].d, D[d].cat, cost);
	}
	return 0;
}
