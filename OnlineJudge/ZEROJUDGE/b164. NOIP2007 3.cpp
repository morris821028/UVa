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
BigInteger bin[128];
int main() {
	bin[0] = BigInteger(1);
	for (int i = 1; i < 100; i++)
		bin[i] = bin[i-1] * 2;
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		BigInteger ret(0);
		for (int it = 0; it < n; it++) {
			BigInteger A[128], dp[128][128];
			for (int i = 1, x; i <= m; i++)
				scanf("%d", &x), A[i] = BigInteger(x);
			for (int i = 0; i <= m; i++) {
				for (int j = 0; j+i <= m; j++) {
					int l = i, r = j;
					if (l > 0 && r > 0)
						dp[l][r] = max(dp[l-1][r]+A[l]*bin[l+r], dp[l][r-1]+A[m-r+1]*bin[l+r]); 
					else if (l > 0)
						dp[l][r] = dp[l-1][r]+A[l]*bin[l+r];
					else
						dp[l][r] = dp[l][r-1]+A[m-r+1]*bin[l+r];
				}
			}
			BigInteger v(0);
			for (int i = 0; i <= m; i++)
				v = max(v, dp[i][m-i]);
			ret = ret + v;
		}
		ret.print();
		puts("");
	}
	return 0;
}
