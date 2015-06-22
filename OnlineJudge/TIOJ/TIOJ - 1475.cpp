#include <bits/stdc++.h> 
using namespace std;

class BigInteger {
public:
    vector<long long> v;
    long long MAXC;
    BigInteger(int x = 0) {
        v = vector<long long>(10, 0);
        v[0] = x;
        MAXC = 100000000;
        normal();
    }
    BigInteger operator+(const BigInteger &x) const {
        BigInteger r(0);
        r.v.resize(max(v.size(), x.v.size()) + 2, 0);
        for (int i = 0; i < v.size(); i++)
            r.v[i] += v[i];
        for (int i = 0; i < x.v.size(); i++)
            r.v[i] += x.v[i];
        r.normal();
        return r;
    }
    BigInteger operator*(const BigInteger &x) const {
        BigInteger r(0);
        r.v.resize(v.size() + x.v.size() + 2, 0);
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == 0)
                continue;
            for (int j = 0; j < x.v.size(); j++)
                r.v[i+j] += v[i] * x.v[j];
        }
        r.normal();
        return r;
    }
    void normal() {
        for (int i = 0; i < v.size(); i++) {
            if (v[i] >= MAXC) {
                v[i+1] += v[i] / MAXC;
                v[i] %= MAXC;
            }
        }
        int s = (int) v.size() - 1;
        while (s > 0 && v[s] == 0)
            s--;
        v.resize(s+1);
    }
    bool isZero() const {
        if (v.size() > 1)   return false;
        return v[0] == 0;
    }
    bool operator<(const BigInteger &x) const {
    	if (v.size() != x.v.size())
    		return v.size() < x.v.size();
    	for (int i = v.size()-1; i >= 0; i--) {
    		if (v[i] != x.v[i])
    			return v[i] < x.v[i];
    	}
    	return false;
	}
	bool operator==(const BigInteger &x)  const {
		if (v.size() != x.v.size())
			return false;
		for (int i = v.size()-1; i >= 0; i--)
			if (v[i] != x.v[i])
				return false;
		return true;
	}
    void print() {
        printf("%lld", v[v.size()-1]);
        for (int i = (int) v.size() - 2; i >= 0; i--)
            printf("%08lld", v[i]);
    }
};

int main() {
	int N, M, A[128];
	BigInteger f[128] = {};
	f[0] = BigInteger(1);
	for (int i = 1; i < 128; i++)
		f[i] = f[i-1] * BigInteger(i);
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++)
			scanf("%d", &A[i]);
		scanf("%d", &M);
		
		sort(A, A + N);
		int dp[10005] = {};
		BigInteger dp2[10005] = {};
		dp2[0] = BigInteger(1), dp[0] = 0;
		for (int i = 0; i < N; i++) {
			int x = A[i];
			for (int j = M; j >= x; j--) {
				if (dp[j] < dp[j-x] + 1 && !dp2[j-x].isZero())
					dp[j] = dp[j-x] + 1, dp2[j] = BigInteger(0);
				if (dp[j] == dp[j-x] + 1 && !dp2[j-x].isZero())
					dp2[j] = dp2[j] + dp2[j-x];
			}
		}
		int a = dp[M];
		BigInteger b = dp2[M] * f[a];
		
		printf("%d ", a);
		b.print();
		puts("");
	}
	return 0;
}
/*
5
10 50 30 70 60
20 
*/
