#include <bits/stdc++.h>
using namespace std;
static const int MAXW = 5000000+5;
static const int MAXN = 1005;

void run(int A[][2], int dp[], int W, int N) {
	for (int i = 0, sum = 0; i < N; i++) {
		int w = A[i][0], v = A[i][1];
		for (int j = min(W, sum + w); j >= w; j--)
			dp[j] = max(dp[j], dp[j-w]+v);
		sum += w;
	}
}

int find_pivot(int sum[], int N, long long W) {
	long long best = 1LL<<60;
	int LT = 0, RT = 0, pos = 0;
	static long long sum2[MAXN];
	long long s = 0;
	sum[N] = sum[N-1];
	for (int i = 0; i <= N; i++)	{
		s += sum[i];
		sum2[i] = s;
	}
	for (int i = 0; i < N; i++) {
		while (LT < i && sum[LT] <= W)	
			LT++;
		RT = max(RT, i-1);
		while (RT < N && sum[RT] - (i ? sum[i-1] : 0) <= W)
			RT++;
		long long cc = (sum2[LT] + (i-LT)*W) + (sum2[RT] - (i ? sum2[i-1] : 0) - (i ? sum[i-1] : 0)*(RT-i) + (N-RT)*W);
		if (cc < best)
			best = cc, pos = i;
	}
	return pos;
}
int main() {
	int W, N;
	while (scanf("%d %d", &W, &N) == 2) {
		vector< pair<int, int> > A;
		for (int i = 0; i < N; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			A.push_back(make_pair(y, x));
		}
		static int dp1[MAXW], dp2[MAXW];
		static int Ar[MAXN][2];
		memset(dp1, 0, sizeof(dp1[0])*(W+1));
		memset(dp2, 0, sizeof(dp2[0])*(W+1));
		sort(A.begin(), A.end());
		for (int i = 0; i < N; i++)
			Ar[i][0] = A[i].first, Ar[i][1] = A[i].second;

		int sum[MAXN] = {};
		for (int i = 0, s = 0; i < N; i++) {
			s += Ar[i][0];
			sum[i] = s;
		}

		int pivot = find_pivot(sum, N, W);
		fprintf(stderr, "test %d %d\n", N/2, pivot);
		run(Ar, dp1, W, pivot);
		run(Ar+pivot, dp2, W, N-pivot);

		int ret = 0;
		for (int i = 0, j = W, mx = 0; i <= W; i++, j--) {
			mx = max(mx, dp2[i]);
			ret = max(ret, dp1[j] + mx);
		}
		printf("%d\n", ret);
	}
	return 0;
}
