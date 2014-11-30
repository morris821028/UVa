#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <algorithm>
using namespace std;

#define MAXN 131072
int x[MAXN], y[MAXN], w[MAXN];
int cost[MAXN], dist[MAXN];
int dp[MAXN];

int f(int j) {
	return dp[j-1] - cost[j] + dist[j];
}
int main() {
	int testcase, C, N;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &C, &N);
		w[0] = 0, cost[0] = 0;
		for (int i = 1; i <= N; i++) {
			scanf("%d %d %d", &x[i], &y[i], &w[i]);
			cost[i] = cost[i-1] + abs(x[i] - x[i-1]) + abs(y[i] - y[i-1]);
			dist[i] = abs(x[i]) + abs(y[i]);
			w[i] += w[i-1];
		}
		// dp[i] = dp[j-1] + cost[j, i] + dist[j] + dist[i]
		// dp[i] = dp[j-1] + cost[i] - cost[j] + dist[j] + dist[i]
		// dp[i] = (dp[j-1] - cost[j] + dist[j]) + cost[i] + dist[i]
		deque<int> Q;
		Q.push_back(0);
		for (int i = 1; i <= N; i++) {
			while (!Q.empty() && w[i] - w[Q.front()] > C)
				Q.pop_front();
			dp[i] = f(Q.front() + 1) + cost[i] + dist[i];
			while (!Q.empty() && f(Q.back() + 1) >= f(i + 1))
				Q.pop_back();
			Q.push_back(i);
		}
		printf("%d\n", dp[N]);
		if (testcase)	puts("");
	}
	return 0;
}
