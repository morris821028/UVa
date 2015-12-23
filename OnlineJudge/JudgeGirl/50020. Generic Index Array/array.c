#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUTOFBOUND -2147483648
#define HAVENOTSET -2147483647
#define SETSUCCESS 1
static int outOfBound(int x, int l, int r) {
	return x < l || x > r;
}
static int cmp(const void *x, const void *y) {
	ELE *a = (ELE*) x, *b = (ELE*) y;
	if (a->has != b->has)	return a->has - b->has;
	return a->val - b->val;
}
void init(ARRAY *a,  int l, int r) {
	a->l = l, a->r = r;
	memset(a->dat, 0, sizeof(a->dat));
}
int set(ARRAY *a, int index, int value) {
	if (outOfBound(index, a->l, a->r))
		return OUTOFBOUND;
	a->dat[index - a->l].has = 1;
	a->dat[index - a->l].val = value;
	return SETSUCCESS;
}
int get(ARRAY *a, int index) {
	if (outOfBound(index, a->l, a->r))
		return OUTOFBOUND;
	if (!a->dat[index - a->l].has)
		return HAVENOTSET;
	return a->dat[index - a->l].val;
}
void print(ARRAY *a) {
	for (int i = a->l, j = 0; i <= a->r; i++, j++) {
		if (a->dat[j].has)	printf("%d\n", a->dat[j].val);
		else				printf("No value\n");
	}
}
void sort(ARRAY *a) {
	qsort(a->dat, a->r - a->l + 1, sizeof(ELE), cmp);
}
