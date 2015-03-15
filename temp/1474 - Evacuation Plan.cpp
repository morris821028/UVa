#include <stdio.h> 
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
#define CLR(x) (mark[(x)>>5] &= ~(1<<((x)&31))) 
const int MAXN = 4010;
const int MAXL = ((MAXN*MAXN)>>5) + 1;
int mark[MAXL];
const long long INF = 1LL<<60;
long long dp[2][MAXN];
long long llabs(long long x) {
	return x > 0 ? x : -x;
}
int main() {
	int n, m, x;
	pair<int, int> S[MAXN], T[MAXN];
	int place[MAXN];
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			T[i] = pair<int, int>(x, i);
		}
		scanf("%d", &m);
		for (int i = 1; i <= m; i++) {
			scanf("%d", &x);
			S[i] = pair<int, int>(x, i);
		}
		
		sort(T+1, T+n+1);
		sort(S+1, S+m+1);
		
		memset(dp, 63, sizeof(dp));
		
		int p = 0, q = 1;
		dp[0][0] = 0;
		for (int i = 1; i <= m; i++) {
			memset(dp[q], 63, (n+1) * sizeof(long long));
			for (int j = i; j <= n; j++) {
//				dp[q][j] = min(dp[q][j-1], dp[p][j-1]) + llabs(S[i].first - T[j].first);
				if (dp[q][j-1] < dp[p][j-1]) { 
					// follow previous (j-1)th team enter shelter i, 
					dp[q][j] = dp[q][j-1] + abs(S[i].first - T[j].first);
					CLR(i * MAXN + j);
				} else { 
					// beginner enter shelter i, 
					dp[q][j] = dp[p][j-1] + abs(S[i].first - T[j].first);
					SET(i * MAXN + j); // set 1, 
				}
			}
			p = !p, q = !q;
		}
		
		for (int i = n, j = m; i >= 1; i--) {
			place[T[i].second] = S[j].second;
			if (GET(j * MAXN + i))
				j--;
		} 
		
		printf("%lld\n", dp[p][n]);
		for (int i = 1; i <= n; i++)
			printf("%d%c", place[i], i == n ? '\n' : ' ');
	}
	return 0;
}
/*
3 
1 2 3 
2 
2 10

7
1 5 6 9 15 0 7
4
-1 5 6 13
*/
