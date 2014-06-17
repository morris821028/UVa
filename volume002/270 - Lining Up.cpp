#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int x, y;
}Point;

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
	Point D[700];
	int t;
	char str[100];
	scanf("%d", &t);
	getchar();
	getchar();
	while(t--) {
		int n = 0;
		while(gets(str)) {
			if(str[0] == '\0')
				break;
			sscanf(str, "%d %d", &D[n].x, &D[n].y);
			n++;
		}
		qsort(D, n, sizeof(Point), cmp);
		int i, j;
		int ans = 1, g;
		Point slope[700];
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
		printf("%d\n", ans+1);
		if(t)	puts("");
	}
    return 0;
}
