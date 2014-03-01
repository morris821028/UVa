#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct {
	double x, y;
}Point;
Point P[100000], CH[100000];
int cmp(const void *i, const void *j) {
	Point *a, *b;
	a = (Point *)i, b = (Point *)j;
	if(a->x != b->x)
		return a->x - b->x > 0 ? 1 : -1;
	return a->y - b->y > 0 ? 1 : -1;
}
double cross(Point o, Point a, Point b) {
	return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}
int montoneChain(int n) {
	qsort(P, n, sizeof(Point), cmp);
	int i, j, m = 0;
	for(i = 0; i < n; i++) {
		while(m >= 2 && cross(CH[m-2], CH[m-1], P[i]) >= 0)
			m--;
		CH[m++] = P[i];
	}
	for(i = n-1, j = m+1; i >= 0; i--) {
		while(m >= j && cross(CH[m-2], CH[m-1], P[i]) >= 0)
			m--;
		CH[m++] = P[i];
	}
	double length = 0;
	for(i = 0; i < m; i++) {
		if(i) {
			printf("-");
			length += sqrt((CH[i].x-CH[i-1].x)*(CH[i].x-CH[i-1].x) +
					(CH[i].y-CH[i-1].y)*(CH[i].y-CH[i-1].y));
		} 
		printf("(%.1lf,%.1lf)", CH[i].x, CH[i].y);
	}
	puts("");
	printf("Perimeter length = %.2lf\n", length);
}
int main() {
	int n, i, Case = 0;
	while(scanf("%d", &n) == 1 && n) {
		for(i = 0; i < n; i++)
			scanf("%lf %lf", &P[i].x, &P[i].y);
		if(Case)	puts("");
		printf("Region #%d:\n", ++Case);
		montoneChain(n);
	}
    return 0;
}
/*
3
1 2
4 10
5 12.3
6
0 0
1 1
3.1 1.3
3 4.5
6 2.1
2 -3.2
*/
