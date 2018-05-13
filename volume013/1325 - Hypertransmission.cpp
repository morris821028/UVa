#include <bits/stdc++.h>
using namespace std;

struct Planet {
	int x, y, z, p;
	Planet(int x=0, int y=0, int z=0, int p=0):
		x(x), y(y), z(z), p(p) {}
} pt[1024];

struct E {
	int i, j, dist;
	E(int i=0, int j=0, int dist=0):
		i(i), j(j), dist(dist) {}
	bool operator<(const E &e) {
		return dist < e.dist;
	}
} pp[1024*1024];

int distance(Planet &a, Planet &b) {
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z);
}

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		static int stat[1024][2] = {};
		for (int i = 0; i < n;  i++) {
			int x, y, z, p;
			scanf("%d %d %d %d", &x, &y, &z, &p);
			pt[i] = Planet(x, y, z, p);
			stat[i][0] = 1;
			stat[i][1] = 0;
		}

		int e = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				pp[e] = E(i, j, distance(pt[i], pt[j]));
				e++;
			}
		}

		sort(pp, pp+e);

		int ret = 0, ret_d = 0;
		int dest = 0;
		for (int i = 0; i < e;) {
			int d = pp[i].dist;
			while (i < e && pp[i].dist == d) {
				int a = pp[i].i, b = pp[i].j;
				if (pt[a].p == pt[b].p) {
					if (stat[a][1] == stat[a][0]+1)
						dest--;
					if (stat[b][1] == stat[b][0]+1)
						dest--;
					stat[a][0]++, stat[b][0]++;
				} else {
					if (stat[a][1] == stat[a][0])
						dest++;
					if (stat[b][1] == stat[b][0])
						dest++;
					stat[a][1]++, stat[b][1]++;
				}
				i++;
			}
			if (dest > ret)
				ret = dest, ret_d = d;
		}
		printf("%d\n", ret);
		printf("%.4lf\n", sqrt(ret_d));
	}
	return 0;
}
/*
4
0 0 0 1
0 1 0 0
1 0 0 0
1 1 0 1
4
0 0 0 1
1 0 0 0
0 1 0 0
0 0 1 1
*/
