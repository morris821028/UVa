#include <bits/stdc++.h> 
#include <stdint.h>
using namespace std;

static const int MAXN = 4096; 
static int V[MAXN], T[MAXN];
static int64_t C[MAXN];
int main() {
	int testcase;
	int vol, tmp, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &vol, &tmp);
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d %d", &V[i], &T[i]);
		for (int i = 1; i <= n; i++) {
			C[i] = C[i-1] + V[i]*T[i];
			V[i] = V[i-1] + V[i];
		}
		
		int hvol = (vol+1)/2;
		float mndiff = 1e+30;
		int ret_l = -1, ret_r = -1;
		for (int i = 1, l = 0; i <= n; i++) {
			l = max(l, i);
			while (l <= n && V[l]-V[i-1] < hvol)
				l++;
			for (int r = l; r <= n && V[r]-V[i-1] <= vol; r++) {
				float t = (float) (C[r]-C[i-1])/(V[r]-V[i-1]);
				if (fabs(t-tmp) < mndiff) {
					mndiff = fabs(t-tmp);
					ret_l = i, ret_r = r;
				}
			}
		}
		if (ret_l < 0 || mndiff > 5)
			puts("Not possible");
		else
			printf("%d %d\n", ret_l-1, ret_r-1);
	}
	return 0;
}
/*
2
615 11
15
24 18
25 5
74 4
80 5
75 3
96 2
53 6
25 24
74 20
97 20
76 3
14 16
8 3
21 14
82 18
100 20
3
10 20
66 40
5 100

75 3
96 2
53 6
25 24
74 20
97 20


*/
