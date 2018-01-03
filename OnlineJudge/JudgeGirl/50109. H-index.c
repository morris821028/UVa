#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	char name[16];
	int count;
} Record;
static Record r[32768];
int cmp(const void *x, const void *y) {
	Record *a = (Record *) x, *b = (Record *) y;
	int t = strcmp(a->name, b->name);
	if (t != 0)	return t;
	return b->count - a->count;
}
int main() {
	int n = 0;
	while (scanf("%s %d", &r[n].name, &r[n].count) == 2)
		n++;
	qsort(r, n, sizeof(r[0]), cmp);
	for (int i = 0; i < n; ) {
		int pos = i, h = 1;
		while (i < n && strcmp(r[i].name, r[pos].name) == 0) {
			if (r[i].count >= h)
				h++;
			i++;
		}
		printf("%s %d\n", r[pos].name, h-1);
	}
	return 0;
}
