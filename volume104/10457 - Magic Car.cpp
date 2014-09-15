#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <vector>
using namespace std;
struct E {
    int x, y, v;
    E(int a=0, int b=0, int c=0):
        x(a), y(b), v(c) {}
    bool operator<(const E &a) const {
        return  v < a.v;
    }
};
E D[10005];
int p[1005], rank[1005];
int findp(int x) {
    return p[x] == x ? x : (p[x] = findp(p[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if(x == y)
        return 0;
    if(rank[x] > rank[y])
        rank[x] += rank[y], p[y] = x;
    else
        rank[y] += rank[x], p[x] = y;
    return 1;
}
int kruscal(int n, int m, E D[], int st, int ed, int &max_edge) {
    for(int i = 0; i <= n; i++)
        p[i] = i, rank[i] = 1;
    for(int i = 0; i < m; i++) {
        if(joint(D[i].x, D[i].y)) {
        	if (findp(st) == findp(ed)) {
        		max_edge = D[i].v;
        		return 1;
        	}
        }
    }
    return 0;
}
int main() {
	int n, m, x, y, w;
	int a, b, q;
	while (scanf("%d %d", &n, &m) == 2 && n+m) {
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &w);
			D[i] = E(x, y, w);
		}
		sort(D, D+m);
		scanf("%d %d", &a, &b);
		scanf("%d", &q);
		while (q--) {
			scanf("%d %d", &x, &y);
			int ret = 0x3f3f3f3f, mxedge;
			for (int i = 0; i < m; i++) {
				if (kruscal(n, m-i, D+i, x, y, mxedge))
					ret = min(ret, mxedge - D[i].v);
				else
					break;
			}
			printf("%d\n", a + b + ret);
		}
	}
	return 0;
}
