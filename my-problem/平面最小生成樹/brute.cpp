#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;

#define MAXV 32767 
struct Point {
	int x, y;
	Point(int a = 0, int b = 0):
		x(a), y(b) {}
	bool operator<(const Point &a) const {
		if (x != a.x)	return x < a.x;
		return y < a.y;
	}
};
struct edge {
    int x, y;
	long long v;
	bool operator<(const edge &a) const {
		return v < a.v;
	}
};
int p[MAXV], r[MAXV];
void init(int n) {
    for(int i= 0; i <= n; i++)
        p[i] = i, r[i] = 1;
}
int find(int x) {
    return x == p[x] ? x : (p[x]=find(p[x]));
}
int joint(int x, int y) {
    x = find(x), y = find(y);
    if(x != y) {
        if(r[x] > r[y])
            r[x] += r[y], p[y] = x;
        else
            r[y] += r[x], p[x] = y;
        return 1;
    }
    return 0;
}
int cmp(const void *i, const void *j) {
    static edge *a, *b;
    a = (edge *)i, b = (edge *)j;
    return a->v - b->v;
}
#define MAXE (1048576 * 2)
edge D[MAXE];
int main() {
    int n, m, i, j;
    Point A[MAXV];
    while(scanf("%d", &n) == 1) {
        init(n);
        for(i = 0; i < n; i++) {
        	int x, y;
            scanf("%d %d", &x, &y);
            A[i] = Point(x, y);
        }
        sort(A, A+n);
        int connect = 0;
        m = 0;
        for(i = 0; i < n; i++) {
            for(j = i+1; j < n && j < i + 10; j++) {
                D[m].x = i, D[m].y = j;
                D[m].v = (long long) (A[i].x-A[j].x)*(A[i].x-A[j].x)+
                    (long long) (A[i].y-A[j].y)*(A[i].y-A[j].y);
                if (m + 1 < MAXE)
                	m++;
            }
        }
        sort(D, D+m);
        double ans = 0;
        for(i = 0; i < m; i++) {
            if(joint(D[i].x, D[i].y)) {
                ans += sqrt(D[i].v);
                connect++;
                if(connect == n-1)
                    break;
            }
        }
        printf("%.0lf\n", ans);
    }
    return 0;
}
