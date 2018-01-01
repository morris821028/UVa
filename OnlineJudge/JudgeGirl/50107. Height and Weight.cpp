#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 64
#define MAXN 131072
typedef struct {
	char name[MAXC];
	int h, w;
	float bmi;
} E;
static E stu[MAXN];
static int cmp(const void *x, const void *y) {
	E *a = (E *) x, *b = (E *) y;
	if (a->bmi != b->bmi)
		return a->bmi < b->bmi ? -1 : 1;
	if (a->w != b->w)
		return a->w < b->w ? -1 : 1;
	if (a->h != b->h)
		return a->h < b->h ? -1 : 1;
	return strcmp(a->name, b->name);
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s %d %d", &stu[i].name, &stu[i].h, &stu[i].w);
		stu[i].bmi = (float) stu[i].w / stu[i].h / stu[i].h;
	}
	qsort(stu, n, sizeof(stu[0]), cmp);
	for (int i = 0; i < n; i++)
		printf("%s %d %d\n", stu[i].name, stu[i].h, stu[i].w);
	return 0;
}
