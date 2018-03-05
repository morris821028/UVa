#include <bits/stdc++.h> 
using namespace std;

struct E {
	int l, r, s;
	E() {l = r = s = 0;}
	bool operator<(const E &e) const {
		return s > e.s;
	}
};
const int MAXS = 105;
E stat[MAXS];
int main() {
	int n, s;
	while (scanf("%d %d", &n, &s) == 2 && n) {
		for (int i = 0; i < s; i++)
			stat[i].s = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0, x; j < s; j++)
				scanf("%d", &x), stat[j].s += x;
		}
		
		int ret = 0, p = 100;
		for (int i = 0; i < s; i++) {
			scanf("%d %d", &stat[i].l, &stat[i].r);
			ret += stat[i].l * stat[i].s;
			p -= stat[i].l;
			stat[i].r -= stat[i].l;
			// stat[i].l = 0
		}
		sort(stat, stat+s);
		for (int i = 0; i < s && p; i++) {
			int t = min(p, stat[i].r);
			ret += stat[i].s * t;
			p -= t;
		}
		printf("%.2lf\n", (double) ret/n/100 + 1e-8);
	}
	return 0;
}
/*
1 1
0
0 100
2 2
50 90
70 50
0 100
0 100
2 2
50 90
70 50
30 70
30 70
2 2
50 90
70 50
50 50
50 50
2 2
73 52
92 81
20 50
60 80
0 0
*/
