#include <bits/stdc++.h>
using namespace std;

namespace {

static const int MAXW = 5000005;
static const int MAXN = 1005*12;
 
static void run(int A[][2], int dp[], int W, int N) {
    for (int i = 0, sum = 0; i < N; i++) {
        int w = A[i][0], v = A[i][1];
        for (int j = min(W, sum + w); j >= w; j--)
            dp[j] = max(dp[j], dp[j-w]+v);
        sum += w;
    }
}
 
static int knapsack(int C[][3], int N, int W) {
	vector< pair<int, int> > A;
	for (int i = 0; i < N; i++) {
		int w = C[i][0], v = C[i][1], c = C[i][2];
		for (int k = 1; k <= c; k <<= 1) {
			A.push_back(make_pair(k*w, k*v));
			c -= k;
		}
		if (c > 0)
			A.push_back(make_pair(c*w, c*v));
	}
	N = A.size();
	assert(N < MAXN);
	static int dp1[MAXW+1], dp2[MAXW+1];
    int Ar[2][MAXN][2], ArN[2] = {};
    memset(dp1, 0, sizeof(dp1[0])*(W+1));
    memset(dp2, 0, sizeof(dp2[0])*(W+1));
    sort(A.begin(), A.end());
	int sum[2] = {};
    for (int i = 0; i < N; i++) {
		int ch = sum[1] < sum[0];
        Ar[ch][ArN[ch]][0] = A[i].first;
		Ar[ch][ArN[ch]][1] = A[i].second;
		ArN[ch]++;
		sum[ch] += A[i].first;
	}

    run(Ar[0], dp1, W, ArN[0]);
    run(Ar[1], dp2, W, ArN[1]);

    int ret = 0;
    for (int i = 0, j = W, mx = 0; i <= W; i++, j--) {
        mx = max(mx, dp2[i]);
        ret = max(ret, dp1[j] + mx);
    }
    return ret;
}
}

int main() {
	int W, N;
	assert(scanf("%d %d", &W, &N) == 2);
	int C[MAXN][3];
	for (int i = 0; i < N; i++)
		assert(scanf("%d %d %d", &C[i][1], &C[i][0], &C[i][2]) == 3);
	printf("%d\n", knapsack(C, N, W));
	return 0;
}

