#include <stdio.h> 
#include <vector>
#include <queue>
using namespace std;
#define MAXL (500000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
int P[55000], Pt = 0;
int Pf[524288];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 500000;
    int m = 0;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j), Pf[j] = i;
            P[Pt++] = i, Pf[i] = i;
        }
    }
}
long long mpow(long long x, long long y, long long mod) {
	long long ret = 1;
	while (y) {
		if (y&1)
			ret = (ret * x)%mod;
		y >>= 1, x = (x * x)%mod;
	}
	return ret;
}
// this problem
const int MAXN = 526244;
vector<int> g[MAXN];
int dp[MAXN];
void preprocess(int N) {
	vector<int> topo;
	queue<int> Q;
	int u, v;
	Q.push(1);
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		topo.push_back(u);
		for (int i = 0; i < g[u].size(); i++)
			Q.push(g[u][i]);
	}
	
	for (int i = topo.size() - 1; i >= 0; i--) {
		u = topo[i];
		dp[u] = 1;
		for (int j = 0; j < g[u].size(); j++)
			dp[u] += dp[g[u][j]];
	}
}
/*
	f(u) = f(s1) f(s2) * (size(u) - 1)! / (size(s1)! size(s2)!)
	=> unfold
  		f(root) = (size(root) - 1)! / (size(u1) size(u2) size(u3) ... size(un))
*/

int szCnt[524288], pCnt[524288];
int main() {
	sieve();
	int testcase, cases = 0;
	int N, p;
	long long M;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %lld", &N, &M);
		
		for (int i = 1; i <= N; i++)
			g[i].clear(), szCnt[i] = 0, pCnt[i] = 0;
		for (int i = 2; i <= N; i++) {
			scanf("%d", &p);
			g[p].push_back(i);
		}
		
		preprocess(N);
		
		for (int i = 2; i <= N; i++)
			szCnt[dp[i]]++;
		
		for (int i = 0; i < Pt && P[i] <= N-1; i++) { 	// factor (N-1)! = m!
			int m = N - 1;
			long long p = P[i];
			while (p <= m)
				pCnt[P[i]] += m / p, p = p * P[i];
		}
		
		for (int i = 2; i <= N; i++) { 					// factor size(u)
			if (szCnt[i] == 0)
				continue;
			int m = i;
			while (m != 1) {
				pCnt[Pf[m]] -= szCnt[i];
				m = m / Pf[m];
			}
		}
		
		long long ret = 1;
		for (int i = 2; i <= N; i++) {
			if (pCnt[i]) {
				ret = (ret * mpow(i, pCnt[i], M))%M;
			}
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
4 
3 1000000
1 
1 
4 1000000
1 
1 
1 
5 1000000
1 
2 
3 
4 
5 1000000
1 
1 
3 
3
*/
