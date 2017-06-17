#include <bits/stdc++.h> 
using namespace std;

#define MAXL (50000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
int P[50000], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 46340;
    for (i = 2; i <= n; i++) {
        if (!GET(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
long long mul(unsigned long long a, unsigned long long b, unsigned long long mod) { 
    long long ret = 0; 
    for (a %= mod, b %= mod; b != 0; b >>= 1, a <<= 1, a = a >= mod ? a - mod : a) {
        if (b&1) {
            ret += a;
            if (ret >= mod)	ret -= mod;
        }
    } 
    return ret; 
}
void exgcd(long long x, long long y, long long &g, long long &a, long long &b) {
    if (y == 0)
        g = x, a = 1, b = 0;
    else
        exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}
long long llgcd(long long x, long long y) {
    if (x < 0)    x = -x;
    if (y < 0)    y = -y;
    if (!x || !y)    return x + y;
    long long t;
    while (x%y)
        t = x, x = y, y = t%y;
    return y;
}
long long inverse(long long x, long long p) {
    long long g, b, r;
    exgcd(x, p, g, r, b);
    if (g < 0)	r = -r;
    return (r%p + p)%p;
}
long long mpow(long long x, long long y, long long mod) { // mod < 2^32 
    long long ret = 1;
    while (y) {
        if (y&1) 
            ret = (ret * x)%mod;
        y >>= 1, x = (x * x)%mod;
    }
    return ret % mod;
}
long long mpow2(long long x, long long y, long long mod) {
    long long ret = 1;
    while (y) {
        if (y&1) 
            ret = mul(ret, x, mod);
        y >>= 1, x = mul(x, x, mod);
    }
    return ret % mod;
}
int isPrime(long long p) { // implements by miller-babin
    if (p < 2 || !(p&1))	return 0;
    if (p == 2)				return 1;
    long long q = p-1, a, t;
    int k = 0, b = 0;
    while (!(q&1))	q >>= 1, k++;
    for (int it = 0; it < 2; it++) {
        a = rand()%(p-4) + 2;
        t = mpow2(a, q, p);
        b = (t == 1) || (t == p-1);
        for (int i = 1; i < k && !b; i++) {
            t = mul(t, t, p);
            if (t == p-1)
                b = 1;
        }
        if (b == 0)
            return 0;
    }
    return 1;
}
long long pollard_rho(long long n, long long c) {
    long long x = 2, y = 2, i = 1, k = 2, d;
    while (true) {
        x = (mul(x, x, n) + c);
        if (x >= n)	x -= n;
        d = llgcd(x - y, n);
        if (d > 1) return d;
        if (++i == k) y = x, k <<= 1;
    }
    return n;
}
void factorize(int n, vector<long long> &f) {
    for (int i = 0; i < Pt && P[i]*P[i] <= n; i++) {
    	if (n%P[i] == 0) {
    		while (n%P[i] == 0)
    			f.push_back(P[i]), n /= P[i];
    	}
    }
    if (n != 1)	f.push_back(n);
}
void llfactorize(long long n, vector<long long> &f) {
    if (n == 1)	
        return ;	
    if (n < 2e+9) {
        factorize(n, f);
        return ;
    }
    if (isPrime(n)) {
        f.push_back(n);
        return ;
    }

    long long d = n;
    for (int i = 2; d == n; i++)
        d = pollard_rho(n, i);
    llfactorize(d, f);
    llfactorize(n/d, f);
}
int main() {
    sieve();
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        long long n;
        scanf("%lld", &n);
        
        vector<long long> f;
        map<long long, int> r;
            
        llfactorize(n, f);
        for (auto &x : f)
            r[x]++;
            
        vector<long long> ret;
        for (auto it = r.begin(); it != r.end(); it++) {
        	for (int i = 0; i < it->second; i++)
        		ret.push_back(it->first);
        }
        
        for (int i = 0; i < ret.size(); i++)
        	printf("%lld%c", ret[i], " \n"[i == ret.size()-1]);        
    }
    return 0;
}
/*
3
2
91
40
*/
