#include <stdio.h> 
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
#define MAXN 3000005
long long dp[MAXN] = {};
int used[MAXN] = {}, ob[MAXN] = {}; // obstacle
int main() {
	memset(dp, 0, sizeof(dp));
	memset(ob, 0, sizeof(ob));
	memset(used, 0, sizeof(used));
	int n, m, dim[16], row[16], v[16];
	int testcase = 0, cases = 0;
	while (scanf("%d %d", &n, &m) == 2 && n+m) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &dim[i]);
			dim[i]++;
		}
		testcase++;
		row[n - 1] = 1;
		for (int i = n - 2; i >= 0; i--)
			row[i] = row[i+1] * dim[i+1];
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++)
				scanf("%d", &v[j]);
			int x = 0;
			for (int j = 0; j < n; j++)
				x += v[j] * row[j];
			ob[x] = testcase;
		}
		if(ob[0] == testcase){
            printf("Case %d: 0\n", ++cases);
            continue;
        }
		int ret = 0;
		for (int i = 0; i < n; i++)
			ret += (dim[i] - 1) * row[i];
		queue<int> Q;
		Q.push(0), used[0] = testcase;
		dp[0] = 1;
		while (!Q.empty()) {
			int x = Q.front();
			Q.pop();
			long long ways = dp[x];
			for (int i = 0; i < n; i++)
				v[i] = x / row[i], x %= row[i];
			for (int i = 0; i < n; i++) {
				v[i]++;
				if (v[i] < dim[i]) {
					x = 0;
					for (int j = 0; j < n; j++)
						x += v[j] * row[j];
					if (ob[x] != testcase) {
						if (used[x] != testcase)
							dp[x] = 0;
						dp[x] += ways;
						if (used[x] != testcase)
							Q.push(x), used[x] = testcase;
					}
				}
				v[i]--;
			}
		}
		if (used[ret] != testcase)	dp[ret] = 0;
		printf("Case %d: %lld\n", ++cases, dp[ret]);
	}
	return 0;
}
/*
3 0 
5 5 5
 
3 1 
9 8 7
1 1 1

3 2
9 8 7
1 1 1
5 6 6

3 2
9 8 7
2 3 4
9 8 7

3 2
9 8 7
2 3 4
9 8 7

0 0
*/
