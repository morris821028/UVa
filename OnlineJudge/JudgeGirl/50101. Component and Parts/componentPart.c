#include "componentPart.h"
#include <stdio.h>
typedef struct {
	ComponentPart *item;
	int price, dirty;
} C;
#define MAXN 128
static int dfs(C *u, C A[]) {
	if (!u->dirty)
		return u->price;
	if (u->item->numComponent == 0) {
		u->dirty = 0;
		return u->price = u->item->price;
	}
	for (int i = 0; i < u->item->numComponent; i++)
		u->price += dfs(&A[u->item->componentPartList[i]], A);
	u->dirty = 0;
	return u->price;
}
static int cmp(const void *a, const void *b) {
	C *x = (C *) a, *y = (C *) b;
	return strcmp(x->item->name, y->item->name);
}
void findPrice(int n, ComponentPart A[]) {
	C B[MAXN];
	for (int i = 0; i < n; i++)
		B[i].item = &A[i], B[i].price = 0, B[i].dirty = 1;
	for (int i = 0; i < n; i++)
		dfs(&B[i], B);
	qsort(B, n, sizeof(B[0]), cmp);
	for (int i = 0; i < n; i++)
		printf("%s %d\n", B[i].item->name, B[i].price);
}

