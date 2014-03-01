#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int x, y;
} Point;

int cmp(const void *i, const void *j) {
	Point *x, *y;
	x = (Point *)i, y = (Point *)j;
	if(x->x != y->x)
		return x->x - y->x;
	return x->y - y->y;
}
int gcd(int x, int y) {
	if(y == 0)	return x;
	x = abs(x);
	y = abs(y);
	int tmp;
	while(x%y) {
		tmp = x, x = y, y = tmp%y;
	}
	return y;
}
int main() {
	Point D[105];
	int t, cases = 0;
	scanf("%d", &t);
	while(t--) {
	    int n, a, b;
	    int i, j;
	    int ans = 0, g;
	    scanf("%d", &n);
	    for(i = 0; i < n; i++) {
	        scanf("%d.%d", &a, &b);
	        D[i].x = 100*a+b;
	        scanf("%d.%d", &a, &b);
	        D[i].y = 100*a+b;
		}
		printf("Data set #%d contains ", ++cases);
		qsort(D, n, sizeof(Point), cmp);
		for(i = 1, j = 1; i < n; i++) {
		    if(D[i].x != D[i-1].x || D[i].y != D[i-1].y)
                D[j++] = D[i];
		}
		n = j;
		if(n == 1) {
		    puts("a single gnu.");
		    continue;
		}
		Point slope[105];
		for(i = 0; i < n; i++) {
			int m = 0, tmp;
			for(j = i+1; j < n; j++) {
				slope[m].x = D[i].x - D[j].x;
				slope[m].y = D[i].y - D[j].y;
				g = gcd(slope[m].x, slope[m].y);
				slope[m].x /= g;
				slope[m].y /= g;
				m++;
			}
			qsort(slope, m, sizeof(Point), cmp);
			Point last = slope[0];
			tmp = 1;
			for(j = 1; j < m; j++) {
				if(last.x == slope[j].x && last.y == slope[j].y) {
					tmp++;
				} else {
					if(tmp > ans)
						ans = tmp;
					last = slope[j], tmp = 1;
				}
			}
			if(tmp > ans)
				ans = tmp;
		}
		printf("%d gnus, out of which a maximum of %d are aligned.\n", n, ans+1);
	}
    return 0;
}
