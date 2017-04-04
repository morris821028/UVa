#include <bits/stdc++.h>
using namespace std;

#define MAXL (50000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL], P[50000], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 46340;
    for (i = 2; i <= n; i++) {
        if (!GET(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}

int parent[262144], weight[262144];
void init(int n) {
	for (int i = 0; i <= n; i++)
		parent[i] = i, weight[i] = 1;
}
int findp(int x) {
	return parent[x] == x ? x : (parent[x] = findp(parent[x]));
}
int joint(int x, int y) {
	x = findp(x), y = findp(y);
	if (x == y)
		return 0;
	if (weight[x] >= weight[y]) {
		weight[x] += weight[y];
		parent[y] = x;
	} else {
		weight[y] += weight[x];
		parent[x] = y;
	}
	return 1;
}
int main() {
	sieve();
	int testcase, cases = 0, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		int label = Pt;
		init(Pt+2*n);
		int size = 0, edge = 0;
		map<int, int> R;
		for (int i = 0; i < Pt; i++)
			R[P[i]] = i;
		int has[65536] = {};
		for (int i = 0; i < n; i++) {
			int x, e = label++;
			scanf("%d", &x);
			size++;
			for (int j = 0; j < Pt && P[j] <= x; j++) {
				if (x%P[j] == 0) {
					if (has[j] == 0)
						has[j] = 1, size++;
					edge += joint(e, j);
					while (x%P[j] == 0)
						x /= P[j];
				}
			}
			if (x != 1) {
				int u;
				if (R.count(x))
					u = R[x];
				else
					u = label++, R[x] = u, size++;
				edge += joint(e, u);
			}
		}
		printf("Case %d: %d\n", ++cases, size - edge);
	}
	return 0;
}
/*
2
3
2  3  4
6
2  3  4  5  6  6
*/
