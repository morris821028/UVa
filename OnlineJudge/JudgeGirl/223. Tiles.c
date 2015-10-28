#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct {
	int x, y;
} Point;
int TYPE[4] = {1, 4, 2, 3};
int RT[4][2] = {{1, 2}, {0, 3}, {0, 3}, {1, 2}};
Point trans(Point b, int d1, int d2, int n) {
	n >>= 2;
	Point ret;
	if (d1 == 0) {
		if (d2 == 0)	return (Point) {b.x-n, b.y-n};
		if (d2 == 1)	return (Point) {b.x-n, b.y+n};
		if (d2 == 2)	return (Point) {b.x+n, b.y-n};
	}
	if (d1 == 1) {
		if (d2 == 1)	return (Point) {b.x-n, b.y+n};
		if (d2 == 0)	return (Point) {b.x-n, b.y-n};
		if (d2 == 3)	return (Point) {b.x+n, b.y+n};
	}
	if (d1 == 2) {
		if (d2 == 2)	return (Point) {b.x+n, b.y-n};
		if (d2 == 0)	return (Point) {b.x-n, b.y-n};
		if (d2 == 3)	return (Point) {b.x+n, b.y+n};
	}
	if (d1 == 3) {
		if (d2 == 3)	return (Point) {b.x+n, b.y+n};
		if (d2 == 1)	return (Point) {b.x-n, b.y+n};
		if (d2 == 2)	return (Point) {b.x+n, b.y-n};
	}
	assert(false);
}
Point trans2(Point b, int d1, int n) {
	n >>= 2;
	if (d1 == 0)	return (Point) {b.x+n, b.y+n};
	if (d1 == 1)	return (Point) {b.x+n, b.y-n};
	if (d1 == 2)	return (Point) {b.x-n, b.y+n};
	if (d1 == 3)	return (Point) {b.x-n, b.y-n};
	assert(false);
}
void dfs(Point co, int n, int m, int r) {
	if (n == m)	return ;
	if (n == 2) {
		printf("%d %d %d\n", TYPE[r], co.x, co.y);
		return ;
	}
	int a = n/2, b = n/4;
	dfs(co, a, b, r);
	dfs(trans(co, r, RT[r][0], n), a, b, RT[r][0]);
	dfs(trans(co, r, RT[r][1], n), a, b, RT[r][1]);
	dfs(trans(co, r, r, n), a, b, r);
	if (m < a) {
		dfs(trans2(co, r, n), a, m, r);
	}
}
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		Point co = {n/2, n/2};
		dfs(co, n, m, 0);
	}
	return 0;
}
