#include <bits/stdc++.h>
using namespace std;

struct Frac {
    long long x, y;
    Frac(long long a = 0, long long b = 1) {
        x = a, y = b;
        normal();
    }
    void normal() {
        if (y < 0)  x = -x, y = -y;
        long long g = llgcd(x, y);
        x /= g, y /= g;
        if (y < 0)  x = -x, y = -y;
    }
    long long llgcd(long long x, long long y) const {
        long long t;
        while (x%y)
            t = x, x = y, y = t % y;
        return y;
    }
    Frac operator-(const Frac &a) const {
        long long va = 0, vb = a.y / llgcd(y, a.y) * y;
        va = vb / y * x - vb / a.y * a.x;
        return Frac(va, vb);
    }
    Frac operator+(const Frac &a) const {
        long long va = 0, vb = a.y / llgcd(y, a.y) * y;
        va = vb / y * x + vb / a.y * a.x;
        return Frac(va, vb);
    }
    Frac operator*(const Frac a) const {
        long long g1 = llgcd(x, a.y), g2 = llgcd(a.x, y);
        long long va = 0, vb = 0;
        va = (x / g1) * (a.x / g2);
        vb = (y / g2) * (a.y / g1);
        return Frac(va, vb);
    }
    Frac operator/(const Frac a) const {
        long long g1 = llgcd(y, a.y), g2 = llgcd(x, a.x);
        long long va = 0, vb = 0;
        va = (a.y / g1) * (x / g2);
        vb = (y / g1) * (a.x / g2);
        return Frac(va, vb);
    }
    bool operator==(const Frac &a) const {
        return x - a.x == 0 && y - a.y == 0;
    }
    bool operator<(const Frac &a) const {
    	// WTF about this.
    	double f1, f2;
    	f1 = 1.0 * x / y, f2 = 1.0 * a.x / a.y;
    	if (fabs(f1 - f2) < 1e-9)	return false;
    	return f1 < f2;
        // return x * a.y < a.x * y;
    }
    void print() {
        printf("%lld/%lld", x, y);
    }
};


int N, K, M[32], cost[32][32];
Frac nofail[32][32], ret;
Frac dp[32][2048];
void dfs(int idx, int K, Frac succ) {
	if (K < 0 || succ < ret)	return ;
	if (idx == N) {
		ret = succ;
		return ;
	}
	for (int i = 0; i < M[idx]; i++) {
		dfs(idx+1, K - cost[idx][i], succ * nofail[idx][i]);
	}
}
int main() {
	int x, y, z;
	while (scanf("%d %d", &N, &K) == 2) {
		for (int i = 0; i < N; i++)
			scanf("%d", &M[i]);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M[i]; j++) {
				scanf("%d %d %d", &x, &y, &z);
				nofail[i][j] = Frac(y-x, y), cost[i][j] = z;
			}
		}
		
		for (int i = 0; i <= N; i++)
			for (int j = 0; j <= K; j++)
				dp[i][j] = Frac(0, 1);
		
		dp[0][0] = Frac(1, 1);
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j < M[i]; j++) {
				for (int k = K - cost[i][j]; k >= 0; k--) {
					Frac p = dp[i][k] * nofail[i][j];
					if (dp[i+1][k + cost[i][j]] < p)
						dp[i+1][k + cost[i][j]] = p;
				}
			}
		}
		
		ret = Frac(0, 1);
		for (int i = 0; i <= K; i++) {
			if (ret < dp[N][i])
				ret = dp[N][i];
		}
		ret = Frac(1, 1) - ret;
		ret.print();
		puts("");
	}
	return 0;
}
/*
1 50
1
0 1 100
1 100
1
0 1 100
2 300
2 3
2 3 10 1 10 100
9 10 100 1 2 200 1 5 250
2 100
2 2
2 3 10 1 10 10
19 20 0 1 2 0
*/

