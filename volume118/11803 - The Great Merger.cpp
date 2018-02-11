#include <bits/stdc++.h>
using namespace std;
const int MAXN = 205;
struct KM {
    int W[MAXN][MAXN], N;
    int mx[MAXN], my[MAXN]; // match arr
    int lx[MAXN], ly[MAXN]; // label arr
    int x[MAXN], y[MAXN]; // used arr
    int hungary(int nd) {
        x[nd] = 1;
        for (int i = 0; i < N; i++) {
            if (y[i] == 0 && W[nd][i] == lx[nd]+ly[i]) {
                y[i] = 1;
                if (my[i] == -1 || hungary(my[i])) {
                    my[i] = nd;
                    return 1;
                }
            }
        }
        return 0;
    }
    int reset(int n) {
    	N = n;
    	for (int i = 0; i < n; i++)
    		memset(W[i], 0, sizeof(W[0][0])*n);
	}
    int run() {
        memset(mx, -1, sizeof(mx));
        memset(my, -1, sizeof(my));
        for (int i = 0; i < N; i++)
        	lx[i] = -0x3f3f3f3f, ly[i] = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                lx[i] = lx[i] > W[i][j] ? lx[i] : W[i][j];
        for (int i = 0; i < N; i++) {
            while (1) {
                memset(x, 0, sizeof(x));
                memset(y, 0, sizeof(y));
                if (hungary(i))  break;
                int d = 0x3f3f3f3f;
                for (int j = 0; j < N; j++) {
                    if (x[j]) {
                        for (int k = 0; k < N; k++)
                            if (!y[k])
                            d = d < lx[j]+ly[k]-W[j][k] ?
                                d : lx[j]+ly[k]-W[j][k];
                    }
                }
                if (d == 0x3f3f3f3f)  break;
                for (int j = 0; j < N; j++) {
                    if (x[j])    lx[j] -= d;
                    if (y[j])    ly[j] += d;
                }
            }
        }
        int res = 0;
        for (int i = 0; i < N; i++) {
            if (my[i] != -1)
                res += W[my[i]][i];
        }
        return res;
    }
} km;

vector<int> g[2][MAXN];
int dp[MAXN][MAXN];
int match(int p, int q) {
	int &ret = dp[p][q];
	if (ret != -1)
		return ret;
	if (g[0][p].size() == 0 || g[1][q].size() == 0)
		return ret = 1;
	// ensure sub-problems are solved.
	for (auto u : g[0][p]) {
		for (auto v : g[1][q])
			match(u, v);
	}
	// running KM algorithm to find maximum matching
	int n = max(g[0][p].size(), g[1][q].size());
	km.reset(n);
	for (int i = 0; i < g[0][p].size(); i++)
		for (int j = 0; j < g[1][q].size(); j++)
			km.W[i][j] = match(g[0][p][i], g[1][q][j]);
	ret = km.run() + 1;
	return ret;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n[2], p;
		for (int i = 0; i < 2; i++) {
			scanf("%d", &n[i]);
			for (int j = 0; j <= n[i]; j++)
				g[i][j].clear();
			for (int j = 1; j <= n[i]; j++) {
				scanf("%d", &p);
				g[i][p].push_back(j);
			}
		}
		memset(dp, -1, sizeof(dp));
		int mx = match(0, 0);
		printf("Case %d: %d\n", ++cases, (n[0]+n[1]+2)-2*mx);
	}
	return 0;
}
/*
2
4  0  0  1  1
4  0  1  2  2

4  0  0  1  1
4  0  0  2  2
*/
