#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 205;
char g[MAXN][MAXN];
int n, m, q;
const double pi = acos(-1);
const double p_area = pi/4;
const double q_area = 4-pi/2;
int f(int x, int y) {
	return x*(2*m+1) + y;
}
struct DisjointSet {
	int parent[MAXN*MAXN], weight[MAXN*MAXN];
	void init(int n) {
		for (int i = 0; i < n; i++)
			parent[i] = i, weight[i] = 1;
	}
	int findp(int x) {
		return x == parent[x] ? x : parent[x]=findp(parent[x]);
	}
	int joint(int x, int y) {
		x = findp(x), y = findp(y);
		if (weight[x] > weight[y]) 
			weight[x] += weight[y], parent[y] = x;
		else
			weight[y] += weight[x], parent[x] = y;
	}
} DS;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", g[i]);

		DS.init((2*n+1)*(2*m+1));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)  {
				int cx = 2*i+1, cy = 2*j+1;
				if (g[i][j] == '0') {
					DS.joint(f(cx, cy), f(cx-1, cy+1));
					DS.joint(f(cx, cy), f(cx+1, cy-1));
				} else {
					DS.joint(f(cx, cy), f(cx-1, cy-1));
					DS.joint(f(cx, cy), f(cx+1, cy+1));
				}
			}
		}
		static double ret[MAXN*MAXN];
		memset(ret, 0, sizeof(ret[0])*(2*n+1)*(2*m+1));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)  {
				int cx = 2*i+1, cy = 2*j+1;
				if (g[i][j] == '0') {
					ret[DS.findp(f(cx-1, cy-1))] += p_area;
					ret[DS.findp(f(cx+1, cy+1))] += p_area;
					ret[DS.findp(f(cx, cy))] += q_area;
				} else {
					ret[DS.findp(f(cx-1, cy+1))] += p_area;
					ret[DS.findp(f(cx+1, cy-1))] += p_area;
					ret[DS.findp(f(cx, cy))] += q_area;
				}
			}
		}
		scanf("%d", &q);
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < q; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			printf("%.4lf\n", ret[DS.findp(f(x, y))]);
		}
	}
	return 0;
}
/*
3
1 2
01
4
0 0
2 0
0 1
0 2
2 2
01
00
1
2 2
3 1
1
0
1
2
3 1
4 2
*/
