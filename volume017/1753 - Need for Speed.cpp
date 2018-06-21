#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 1024;
int d[MAXN], s[MAXN];
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		double l = INT_MAX, r;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &d[i], &s[i]);
			l = min(l, (double) s[i]);
		}
		l = -l, r = 0x3f3f3f3f;
		for (int it = 0; it < 80; it++) {
			double c = (l+r)/2, t = 0;
			for (int i = 0; i < n && t < m; i++)
				t += d[i] / (c + s[i]);
			if (t > m)
				l = c;
			else
				r = c;
		}
		printf("%.9lf\n", l);
	}
	return 0;
}
/*
3  5
4  -1
4  0
10  3

4  10
5  3
2  2
3  6
3  1
*/
