#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <limits.h>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
#define MILLER_BABIN 10
typedef unsigned long long UINT64;
#define UNSTABLE_FAST
UINT64 mul(UINT64 a, UINT64 b, UINT64 mod) {
#ifdef UNSTABLE_FAST
    return (a*b - (long long)(a/(long double)mod*b+1e-3)*mod+mod)%mod;
#endif
    UINT64 ret = 0;
    for (a = a >= mod ? a%mod : a, b = b >= mod ? b%mod : b; b != 0; b>>=1, a <<= 1, a = a >= mod ? a - mod : a) {
        if (b&1) {
            ret += a;
            if (ret >= mod)
                ret -= mod;
        }
    }
    return ret;
}
struct Matrix {
    UINT64 v[2][2];
    int row, col; // row x col
    Matrix(int n, int m, int a = 0) {
        memset(v, 0, sizeof(v));
        row = n, col = m;
        for(int i = 0; i < row && i < col; i++)
            v[i][i] = a;
    }
    Matrix multiply(const Matrix& x, const long long mod) const {
        Matrix ret(row, x.col);
        for(int i = 0; i < row; i++) {
            for(int k = 0; k < col; k++) {
                if (!v[i][k])
                    continue;
                for(int j = 0; j < x.col; j++) {
                    ret.v[i][j] += mul(v[i][k], x.v[k][j], mod);
                    if (ret.v[i][j] >= mod)
                        ret.v[i][j] -= mod;
                }
            }
        }
        return ret;
    }
    Matrix pow(const long long& n, const long long mod) const {
        Matrix ret(row, col, 1), x = *this;
        long long y = n;
        while(y) {
            if(y&1)	ret = ret.multiply(x, mod);
            y = y>>1, x = x.multiply(x, mod);
        }
        return ret;
    }
} FibA(2, 2, 0);

#define MAXL (50000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL], P[50000], Pt = 0;
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

UINT64 mpow(UINT64 x, UINT64 y, UINT64 mod) { // mod < 2^32
    UINT64 ret = 1;
    while (y) {
        if (y&1)
            ret = (ret * x)%mod;
        y >>= 1, x = (x * x)%mod;
    }
    return ret % mod;
}
UINT64 mpow2(UINT64 x, UINT64 y, UINT64 mod) {
    UINT64 ret = 1;
    while (y) {
        if (y&1)
            ret = mul(ret, x, mod);
        y >>= 1, x = mul(x, x, mod);
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
int isPrime(long long p) { // implements by miller-babin
    if (p < 2 || !(p&1))	return 0;
    if (p == 2)				return 1;
    long long q = p-1, a, t;
    int k = 0, b = 0;
    while (!(q&1))	q >>= 1, k++;
    for (int it = 0; it < MILLER_BABIN; it++) {
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
    if (n < 1e+9) {
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
// above largest factor
// ---------------------- //
int legendre_symbol(UINT64 d, UINT64 p) {
    if (d%p == 0)	return 0;
    return mpow2(d, (p-1)>>1, p) == 1 ? 1 : -1;
}
void factor_gen(int idx, long long x, vector< pair<long long, int> > &f, vector<long long> &ret) {
    if (idx == f.size()) {
        ret.push_back(x);
        return ;
    }
    for (long long i = 0, a = 1; i <= f[idx].second; i++, a *= f[idx].first)
        factor_gen(idx+1, x*a, f, ret);
}
void factor_gen(long long n, vector<long long> &ret) {
    vector<long long> f;
    vector< pair<long long, int> > f2;
    llfactorize(n, f);
    sort(f.begin(), f.end());
    int cnt = 1;
    for (int i = 1; i <= f.size(); i++) {
        if (i == f.size() || f[i] != f[i-1])
            f2.push_back(make_pair(f[i-1], cnt)), cnt = 1;
        else
            cnt ++;
    }
    factor_gen(0, 1, f2, ret);
    sort(ret.begin(), ret.end());
}
UINT64 cycleInFib(UINT64 p) {
    if (p == 2)	return 3;
    if (p == 3)	return 8;
    if (p == 5)	return 20;
    vector<long long> f;
    if (legendre_symbol(5, p) == 1)
        factor_gen(p-1, f);
    else
        factor_gen(2*(p+1), f);
    long long f1, f2;
    for (int i = 0; i < f.size(); i++) {
        Matrix t = FibA.pow(f[i]-1, p);
        f1 = (t.v[0][0] + t.v[0][1])%p;
        f2 = (t.v[1][0] + t.v[1][1])%p;
        if (f1 == 1 && f2 == 0)
            return f[i];
    }
    return 0;
}
UINT64 cycleInFib(UINT64 p, int k) {
    UINT64 s = cycleInFib(p);
    for (int i = 1; i < k; i++)
        s = s * p;
    return s;
}
// inverse fibonacci function
int main() {
    sieve();
    FibA.v[0][0] = 1, FibA.v[0][1] = 1;
    FibA.v[1][0] = 1, FibA.v[1][1] = 0;
    
    int K, testcase;
    UINT64 C[20] = {1, 60, 300, 1500, 15000, 150000, 1500000, 15000000, 150000000, 1500000000, 15000000000, 150000000000, 1500000000000, 15000000000000, 150000000000000, 1500000000000000, 15000000000000000, 150000000000000000, 1500000000000000000};
    UINT64 M[20];
    scanf("%d %d", &K, &testcase);
    for (int i = 1; i <= K; i++) {
        long long m = mpow2(10, i, LONG_LONG_MAX);
        //        vector<long long> f;
        //        map<long long, int> r;
        //
        //        llfactorize(m, f);
        //        for (auto &x : f)
        //            r[x]++;
        //
        //        UINT64 cycle = 1;
        //        for (auto &x : r) {
        //            UINT64 t = cycleInFib(x.first, x.second);
        //            cycle = cycle / llgcd(t, cycle) * t;
        //        }
        //        C[i] = cycle;
        M[i] = m;
    }
    
    while (testcase--) {
        char s[32];
        scanf("%s", s);
        long long fib;
        vector<UINT64> pos;
        sscanf(s, "%lld", &fib);
        if (fib == 0) {
            puts("1");
            continue;
        }
        sscanf(s+K-1, "%lld", &fib);
        for (int i = 0; i < C[1]; i++) {
            Matrix t = FibA.pow(i, 10);
            long long fn = t.v[1][0];
            if (fn == fib)
                pos.push_back(i);
        }
        for (int i = 2; i <= K; i++) {
            sscanf(s+K-i, "%lld", &fib);
            vector<UINT64> next;
            for (auto &x : pos) {
                Matrix t = FibA.pow(x, M[i]), tp = FibA.pow(C[i-1], M[i]);
                for (UINT64 c = x; c <= C[i]; c += C[i-1]) {
                    long long fn = t.v[1][0];
                    if (fn == fib)
                        next.push_back(c);
                    t = t.multiply(tp, M[i]);
                }
            }
            sort(next.begin(), next.end());
            next.resize(unique(next.begin(), next.end()) - next.begin());
            pos = next;
        }
        if (pos.size() == 0)
            puts("You've slept foolish!");
        else
            printf("%llu\n", pos[0]+1);
    }
    return 0;
}
/*
 17 1
 00012779675210023
 16 1
 0012569221817747
 */
