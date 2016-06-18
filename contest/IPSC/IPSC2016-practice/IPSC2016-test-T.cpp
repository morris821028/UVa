#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1024;
long long X[1024], Y[1024], R[1024];
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
        assert(x < 10000), assert(y < 10000);
    }
    long long llgcd(long long x, long long y) const {
    	if (x == 0)	return y;
    	if (y == 0)	return x;
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
        return x * a.y < a.x * y;
    }
    void print() {
        printf("%lld/%lld", x, y);
    }
};
Frac V[1024];
int inter(int x, int y) {
	long long v;
	v = (X[x] - X[y])*(X[x] - X[y]) + 
		(Y[x] - Y[y])*(Y[x] - Y[y]);
	return v <= (R[x] + R[y]) * (R[x] + R[y]);
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lld %lld %lld", &X[i], &Y[i], &R[i]);
		int suck[1024] = {};
		int used[1024] = {};
		int update = 0;
			memset(used, 0, sizeof(used));
			queue<int> Q;
			Q.push(0), V[0] = Frac(1, 1), used[0] = 1, suck[0] = 0;
			while (!Q.empty() && update == 0) {
				int u = Q.front();
				Q.pop();
				for (int i = 0; i < n && update == 0; i++) {
					if (suck[i] || i == u)
						continue;
					if (!inter(u, i))
						continue;
					Frac t = V[u] * Frac(R[u], R[i]);
					if (used[i] && !(t == V[i])) {
						suck[i] = 1;
						update = 1;
					}
					if (used[i] && (used[u]+1)%2 != used[i]%2) {
						suck[i] = 1;
						update = 1;
					}
					V[i] = t;
					if (used[i] == 0) {
						used[i] = used[u]+1;
						Q.push(i);
					}
				}
			}
		
		if (used[n-1] && update == 0) {
			V[n-1].print();
			if (used[n-1]%2)
				printf(" clockwise\n");
			else
				printf(" counterclockwise\n");
		} else {
			puts("does not rotate");
		}
	}
	return 0;
}

