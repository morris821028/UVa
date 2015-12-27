#include <stdio.h>

typedef struct {
	int x, y;
} Point;

Point A[131072];
int cmp(const void *x, const void *y) {
	Point *a = (Point *) x;
	Point *b = (Point *) y;
	long long da = (long long)a->x*a->x + (long long)a->y*a->y;
	long long db = (long long)b->x*b->x + (long long)b->y*b->y;
	if (da < db)		return -1;
	if (da > db)		return 1;
	if (a->x < b->x)	return -1;
	if (a->x > b->x)	return 1;
	if (a->y < b->y)	return -1;
	if (a->y > b->y)	return 1;
	return 0;
}
int main() {
	int n = 0;
	while (scanf("%d %d", &A[n+1].x, &A[n+1].y) == 2)
		n++;
	A[0].x = A[0].y = 0;
	qsort(A+1, n, sizeof(Point), cmp);
	long long ret = 0;
	for (int i = 1; i <= n; i++) {
		long long x = A[i].x - A[i-1].x;
		long long y = A[i].y - A[i-1].y;
		ret += x*x + y*y;
	}
	printf("%lld\n", ret);
	return 0;
}
