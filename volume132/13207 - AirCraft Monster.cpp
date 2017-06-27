#include <bits/stdc++.h>
using namespace std;

struct E {
	int a, b, c;
	E(int a=0, int b=0, int c=0):
		a(a), b(b), c(c) {}
	bool operator<(const E &other) const {
		if (a != other.a)
			return a < other.a;
		if (b != other.b)
			return b < other.b;
		return c < other.c;
	}
};
static inline int log2int(int x) {
    return 31 - __builtin_clz(x);
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int X, A, D, m;
		int XP[32], AP[32], DP[32];
		scanf("%d %d %d %d", &X, &A, &D, &m);
		
		for (int i = 0; i < m; i++)
			scanf("%*s %d %d %d", &XP[i], &AP[i], &DP[i]);
			
		int M = m/2, M2 = m-m/2;
		static int dp[1<<16][3] = {};
		set<E> R;
		R.insert(E(0, 0, 0));
		for (int i = 1; i < (1<<M); i++) {
			int k = i&(-i);
			int j = i^k;
			int pos = log2int(k);
			dp[i][0] = dp[j][0] + XP[pos];
			dp[i][1] = dp[j][1] + AP[pos];
			dp[i][2] = dp[j][2] + DP[pos];
		}
		for (int i = 0; i < (1<<M); i++) {
			if (dp[i][0] > X)	continue;
			if (dp[i][1] > A)	continue;
			if (dp[i][2] > D)	continue;
			R.insert(E(dp[i][0], dp[i][1], dp[i][2]));
		}
		
		int ret = R.count(E(X, A, D));
		for (int i = 1; i < (1<<M2) && !ret; i++) {
			int k = i&(-i);
			int j = i^k;
			int pos = log2int(k);
			dp[i][0] = dp[j][0] + XP[pos+M];
			dp[i][1] = dp[j][1] + AP[pos+M];
			dp[i][2] = dp[j][2] + DP[pos+M];
			if (dp[i][0] <= X && dp[i][1] <= A && dp[i][2] <= D)
			if (R.count(E(X-dp[i][0], A-dp[i][1], D-dp[i][2])))
				ret = 1;
		}
		puts(ret ? "POSSIBLE" : "IMPOSSIBLE");
	}
	return 0;
}
/*
100
100 100 100 5
MISSION1 30 10 40
MISSION2 40 70 30
MISSION3 40 10 20
MISSION4 20 20 50
MISSION5 10 50 90
100 100 100 3
a 10 30 10
b 10 10 40
c 10 60 50
100 100 100 2
a 0 0 0
b 100 100 100
100 100 100 2
b 100 100 100
a 0 0 0
*/

