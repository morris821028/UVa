#include <stdio.h> 
#include <algorithm>
using namespace std;

struct E {
    int x, y, v;
    E(int a = 0, int b = 0, int c = 0):
        x(a), y(b), v(c) {}
    bool operator<(const E &a) const {
        return  v > a.v;
    }
};
E D[65536];
int p[256], rank[256];
int findp(int x) {
    return p[x] == x ? x : (p[x]=findp(p[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if(x == y)	return 0;
    if(rank[x] > rank[y])
        rank[x] += rank[y], p[y] = x;
    else
        rank[y] += rank[x], p[x] = y;
    return 1;
}
int main() {
	int testcase, cases = 0, n, g[256][256];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				scanf("%d", &g[i][j]);
		printf("Case #%d: ", ++cases);
		int eflag = 0;
		for(int i = 0; i < n; i++)
			for(int j = i+1; j < n; j++)
				for(int k = j+1; k < n; k++)
					if(min(g[i][j], g[j][k]) > g[i][k] ||
						min(g[i][k], g[j][k]) > g[i][j] ||
						min(g[i][j], g[i][k]) > g[j][k])
						eflag = 1, i = j = k = n;
		if(eflag)  {
			puts("Impossible");
			continue;
		}
		printf("%d\n", n - 1);
		int m = 0;
		for(int i = 0; i < n; i++)
			p[i] = i, rank[i] = 1;
		for(int i = 0; i < n; i++)
			for(int j = i+1; j < n; j++)
				D[m++] = E(i, j, g[i][j]);
		sort(D, D+m);
		for(int i = 0; i < m; i++) {
			if(joint(D[i].x, D[i].y)) {
				printf("%d %d %d\n", D[i].x, D[i].y, D[i].v);
			}
		}
	}
	return 0;
}
