#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 2048;

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
char s1[MAXN], s2[MAXN];
int dp[MAXN][MAXN];
int main() {
	int N, M, K, val;
	while (scanf("%d %s %s", &K, s1+1, s2+1) == 3) {
		N = strlen(s1+1), M = strlen(s2+1), K++;
		int GLCS = 0;
		MonoQueue<int, cmp> mxC[MAXN];
				
		for (int i = 0; i < M; i++)
			mxC[i].setWindow(K);
		for (int i = 0; i <= N; i++)
			for (int j = 0; j <= M; j++)
				dp[i][j] = 0;
				
		for (int i = 0; i <= N; i++) {
			MonoQueue<int, cmp> mxR;
			mxR.setWindow(K);
			for (int j = 0; j <= M; j++) {
					
				val = dp[i][j];
				mxC[j].add(i, val);
				mxR.add(j, mxC[j].top().second);
				
				if (s1[i+1] == s2[j+1])
					dp[i+1][j+1] = mxR.top().second+1;
				GLCS = max(GLCS, val);
			}
		}

		printf("%d\n", GLCS);
	}
	return 0;
}

