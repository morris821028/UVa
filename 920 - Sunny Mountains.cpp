#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct {
	int x, y;
}Point;
int cmp(const void *i, const void *j) {
	Point *x, *y;
	x = (Point *)i, y = (Point *)j;
	return y->x - x->x;
}
int main() {
	Point D[100];
	int C, n, i;
	scanf("%d", &C);
	while(C--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d %d", &D[i].x, &D[i].y);
		qsort(D, n, sizeof(Point), cmp);
		int maxH = 0;
		double sum = 0;
		for(i = 1; i < n; i++) {
			if(D[i].y > maxH) {
				double x, y;
				x = D[i].x-(double)(D[i].x-D[i-1].x)*(D[i].y-maxH)/(D[i].y-D[i-1].y);
				y = maxH;
				sum += sqrt((x-D[i].x)*(x-D[i].x) + (y-D[i].y)*(y-D[i].y));
				maxH = D[i].y;
			}
		}
		printf("%.2lf\n", sum);
	}
    return 0;
}
