#include <bits/stdc++.h> 
using namespace std;

template<typename WTYPE, bool FUNC(WTYPE, WTYPE)>
class MonoQueue {
public:
	deque< pair<int, WTYPE> > Q;
	int K;
	void setWindow(int K) {
		this->K = K;
	}
	inline void add(int idx, WTYPE val) {
		while (!Q.empty() && Q.front().first <= idx - K)
			Q.pop_front();
		while (!Q.empty() && FUNC(val, Q.back().second))
			Q.pop_back();
		Q.push_back({idx, val});
	}
	inline pair<int, WTYPE> top() {
		return Q.front();
	}
};
bool cmp(int a, int b) { return a >= b; }

const int MAXN = 1024;
int C[MAXN][MAXN], T[MAXN][MAXN], robot[MAXN];
int dp[MAXN][MAXN];
int main() {
	int N, M, P;
	scanf("%d %d %d", &N, &M, &P);
	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= M; j++)
			scanf("%d", &C[i][j]);
	}
	for (int i = 0; i < N; i++)
		scanf("%d", &robot[i]);
	
	// 
	for (int i = 0; i < N; i++)
		T[1][i] = C[i][1];
	for (int i = 2; i <= M; i++)
		for (int j = 0; j < N; j++)
			T[i][j] = T[i-1][(j-1+N)%N] + C[j][i];
	
	int dpm[MAXN] = {};
	MonoQueue<int, cmp> Q[MAXN];
	// dp[i][j] = max(dpm[i-k] + T[i][j] - T[i-k][j-k] - robot[j-k+1])
	// dp[i][j] = T[i][j] + max(dpm[i-k] - T[i-k][j-k] - robot[j-k+1])
	
	// let g[i][j] = dpm[i] - T[i][j] - robot[j+1]
	// then, dp[i][j] = T[i][j] + max(g[i-k][j-k])
	for (int i = 0; i <= M; i++)
		Q[i].setWindow(P);
	for (int i = 1; i <= M; i++) {
		dpm[i] = INT_MIN;
		for (int j = 0; j < N; j++) {
			dp[i][j] = INT_MIN;
//			for (int k = 1; k <= P && i-k >= 0; k++) {
//				int val = dpm[i-k] + T[i][j] - T[i-k][((j-k)%N+N)%N] - robot[((j-k)%N+1+N)%N];
//				dp[i][j] = max(dp[i][j], val);
//			}
			int k = ((i-j)%N+N)%N, val;
			Q[k].add(i, dpm[i-1] - T[i-1][(j-1+N)%N] - robot[j]);
			val = T[i][j] + Q[k].top().second;
			dp[i][j] = val;
			dpm[i] = max(dpm[i], dp[i][j]);
		}
	}
	printf("%d\n", dpm[M]);
	return 0;
}
