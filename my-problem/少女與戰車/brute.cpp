#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
#include <assert.h>
using namespace std;

#define eps 1e-8
#define MAXN 32767
int main() {
	int n;
	freopen("in.txt", "r+t", stdin);
	freopen("bruteout.txt", "w+t", stdout);
	double X[MAXN], V[MAXN];
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &X[i], &V[i]);
		int st = 0, leading[MAXN] = {};
		for (int i = 1; i < n; i++) {
			if (X[i] > X[st] || (X[i] == X[st] && V[i] > V[st]))
				st = i;
		}
		leading[st] = 1;
		for (int i = 0; i < n; i++) {
			int next = st;
			double t = -1, tmp;
			for (int j = 0; j < n; j++) {
				if (V[j] <= V[st])
					continue;
				tmp = (X[st] - X[j]) / (V[j] - V[st]);
				assert(tmp >= 0);
				if (t < 0 || tmp < t || (fabs(tmp - t) < eps && V[j] > V[next]))
					t = tmp, next = j;
			}
			if (next == st)
				break;			
			st = next;
			leading[st] = 1;
		}
		for (int i = 0; i < n; i++) {
			if (i)	putchar(' ');
			printf("%d", leading[i]);
		}
		puts("");
	}
	return 0;
}
/*
3
5 -1
1 2
3 -3

6
16 0.125
14 0.2727
18 -0.125
4  0.8333
12 0.3
6  0.5714

3
4 1
4 0.5
0 2.25

4
3 0
5 -1
0 0.75
1 0.5

3
3 -1
2 -0.25
1 -0.5

4
0 1
1 0.75
2 0.5
3 0.25 
*/
