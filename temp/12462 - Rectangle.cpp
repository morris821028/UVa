#include <stdio.h>
#include <string.h>
#include <stack>
#include <algorithm>
using namespace std;
#define MAXN 131072
#define MAXC 32
int h[MAXN], c[MAXN], sumc[MAXN][MAXC];
int L[MAXN], R[MAXN]; 
int main() {
	int N, C;
	while (scanf("%d %d", &N, &C) == 2 && N) {
		for (int i = 1; i <= N; i++)
			scanf("%d", &h[i]);
		for (int i = 1; i <= N; i++)
			scanf("%d", &c[i]);
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < C; j++)
				sumc[i][j] = sumc[i-1][j];
			sumc[i][c[i]]++;
		}
		for (int i = 0; i < C; i++)
			sumc[N+1][i] = sumc[N][i]; 
			
		h[0] = h[N+1] = 0;
		stack<int> stk;
		stk.push(0);
		for (int i = 1; i <= N; i++) {
			while (h[i] <= h[stk.top()])
				stk.pop();
			L[i] = stk.top() + 1, stk.push(i);
		}
		
		while (!stk.empty())	stk.pop();
		
		stk.push(N + 1);
		for (int i = N; i >= 1; i--) {
			while (h[i] <= h[stk.top()])
				stk.pop();
			R[i] = stk.top() - 1, stk.push(i);
		}
		
		long long ret = 0;
		for (int i = 1; i <= N; i++) {
			int ok = 1;
			for (int j = 0; j < C; j++)
				ok &= sumc[R[i]][j] - sumc[L[i] - 1][j] > 0;
			if (ok)
				ret = max(ret, (long long) h[i] * (R[i] - L[i] + 1));
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
6 3
2 3 1 7 3 5
2 0 1 0 1 2
3 1
2 2 2
0 0 0
5 2
3 2 1 2 3
1 0 1 0 1
6 4
1 2 3 4 5 6
0 1 2 3 1 0
7 2
1 2 3 4 3 2 1
0 1 0 1 0 1 0
10 2
2 1 2 1 1 2 1 2 2 1
1 0 0 0 1 0 0 1 1 0
3 2
1000000000 999999997 999999999
0 1 1
*/
