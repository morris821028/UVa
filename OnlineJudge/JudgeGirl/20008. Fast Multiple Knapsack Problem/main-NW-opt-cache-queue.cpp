#include <bits/stdc++.h>
using namespace std;

namespace {

	static const int MAXW = 1000005;
	static const int MAXN = 1005;
	static const int MAXC = 1<<12;

	struct BB {
		int w, v, c;
		BB(int w = 0, int v = 0, int c = 0):
			w(w), v(v), c(c) {}
		bool operator<(const BB &x) const {
			return w * c  < x.w * x.c;
		}
	};
	static bool cmpByWeight(BB x, BB y) {
		return x.w < y.w;
	}
	static int run(BB A[], int dp[], int W, int N) {
		static int MQ[MAXC][2];
		
		for (int i = 0, sum = 0; i < N; i++) {
			int w = A[i].w, v = A[i].v, c = A[i].c;
			assert(c < MAXC);
			sum = min(sum + w*c, W);
			if (c != 1) {
				for (int j = 0; j < w; j++) {
					int l = 0, r = 0;
					MQ[r][0] = 0, MQ[r][1] = dp[j];
					int cache_max = MQ[r][1], cache_idx = MQ[r][0];
					int k_bound;
					r = (r+1)&(MAXC-1);
					k_bound = min((sum-j)/w, c);
					for (int k = 1, tw = w+j, tv = v; k <= k_bound; k++, tw += w, tv += v) {
						// tw = k*w+j, tv = k*v;
						int dpv = dp[tw] - tv;
						while (l != r && MQ[r-1][1] <= dpv)
							r = (r-1+MAXC)&(MAXC-1);
						MQ[r][0] = k, MQ[r][1] = dpv;
						if (l == r)	cache_max = dpv, cache_idx = k;
						r = (r+1)&(MAXC-1);
						dp[tw] = max(dp[tw], cache_max + tv);
					}
					k_bound = (sum-j)/w;
					for (int k = c+1, tw = (c+1)*w+j, tv = (c+1)*v; k <= k_bound; k++, tw += w, tv += v) {
						int dpv = dp[tw] - tv;
						while (l != r && MQ[r-1][1] <= dpv)
							r--;
						MQ[r][0] = k, MQ[r][1] = dpv;
						if (l == r)	cache_max = dpv, cache_idx = k;
						else if (k - cache_idx > c)	
							l = (l+1)&(MAXC-1), cache_idx = MQ[l][0], cache_max = MQ[l][1];
						r = (r+1)&(MAXC-1);
						dp[tw] = max(dp[tw], cache_max + tv);
					}
				}
			} else if (c == 1) {
				for (int j = sum; j >= w; j--)
					dp[j] = max(dp[j], dp[j-w]+v);
			}
		}
	}	
	static int greedy(int C[][3], int N, int W) {
		struct GB {
			int w, v, c;
			GB(int w = 0, int v = 0, int c = 0):
				w(w), v(v), c(c) {}
			bool operator<(const GB &x) const {
				if (v * x.w != x.v * w)
					return v * x.w > x.v * w;
				return c > x.c;
			}
		};
		vector<GB> A;
		for (int i = 0; i < N; i++) {
			int w = C[i][0], v = C[i][1], c = C[i][2];
			A.push_back(GB(w, v, c));
		}
		sort(A.begin(), A.end());
		int ret = 0;
		for (int i = 0; i < N; i++) {
			int t = min(A[i].c, W/A[i].w);
			if (t == 0)
				return -1;
			W -= t*A[i].w;
			ret += t*A[i].v;
			if (W == 0)
				return ret;
		}
		return ret;
	}
	static int knapsack(int C[][3], int N, int W) {
		// filter
		{
			int filter = greedy(C, N, W);
			if (filter != -1)
				return filter;
		}
		vector<BB> A;
		for (int i = 0; i < N; i++) {
			int w = C[i][0], v = C[i][1], c = C[i][2];
			A.push_back(BB(w, v, c));
		}
		// reduce
		{
			sort(A.begin(), A.end(), cmpByWeight);
			map<pair<int, int>, int> R;
			for (int i = 0; i < N; i++)
				R[make_pair(A[i].w, A[i].v)] = i;
			for (int i = 0; i < N; i++) {
				int c = A[i].c;
				map<pair<int, int>, int>::iterator it;
				for (int k = 1; k <= c; k <<= 1) {
					int w = A[i].w * k, v = A[i].v * k;
					it = R.find(make_pair(w, v));
					if (it != R.end() && i != it->second) {
						int j = it->second;
						A[j].c ++;
						A[i].c -= k;
					}
					c -= k;
				}
				if (c > 0) {
					int w = A[i].w * c, v = A[i].v * c;
					it = R.find(make_pair(w, v));
					if (it != R.end() && i != it->second) {
						int j = it->second;
						A[j].c ++;
						A[i].c -= c;
					}
				}
			}
		}
		static int dp1[MAXW+1], dp2[MAXW+1];
		BB Ar[2][MAXN];
		int ArN[2] = {};
		memset(dp1, 0, sizeof(dp1[0])*(W+1));
		memset(dp2, 0, sizeof(dp2[0])*(W+1));
		sort(A.begin(), A.end());
		int sum[2] = {};
		for (int i = 0; i < N; i++) {
			int ch = sum[1] < sum[0];
			Ar[ch][ArN[ch]] = A[i];
			ArN[ch]++;
			sum[ch] = min(sum[ch] + A[i].w*A[i].c, W);
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
//	freopen("6.in", "r", stdin);
	int W, N;
	assert(scanf("%d %d", &W, &N) == 2);
	int C[MAXN][3];
	for (int i = 0; i < N; i++)
		assert(scanf("%d %d %d", &C[i][1], &C[i][0], &C[i][2]) == 3);
	printf("%d\n", knapsack(C, N, W));
	return 0;
}




