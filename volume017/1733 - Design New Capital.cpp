#include <bits/stdc++.h> 
using namespace std;

class TOOL_NTT {
public:
	static const int MAXN = (262144);
    const int64_t P = 7340033; // prime m = kn+1
    const int64_t G = 3;
    int64_t wn[22];
    int64_t s[MAXN], d1[MAXN], d2[MAXN], y[MAXN];
    TOOL_NTT() {
    	for (int i = 0; i < 22; i++)
            wn[i] = mod_pow(G, (P-1) / (1<<i), P);
    }
    int64_t mod_mul(int64_t a, int64_t b, int64_t mod) {
    	return a*b%mod;
//        return (a*b - (long long)(a/(long double)mod*b+1e-3)*mod+mod)%mod;
    }
    int64_t mod_pow(int64_t n, int64_t e, int64_t m) {
        int64_t x = 1;
        for (n = n >= m ? n%m : n; e; e >>= 1) {
            if (e&1)
                x = mod_mul(x, n, m);
            n = mod_mul(n, n, m);
        }
        return x;
    }
    int NumberOfBitsNeeded(int PowerOfTwo) {
        for (int i = 0;; ++i) {
            if (PowerOfTwo & (1 << i)) {
                return i;
            }
        }
    }
    inline uint32_t FastReverseBits(uint32_t a, int NumBits) {
        a = ( ( a & 0x55555555U ) << 1 ) | ( ( a & 0xAAAAAAAAU ) >> 1 ) ;
        a = ( ( a & 0x33333333U ) << 2 ) | ( ( a & 0xCCCCCCCCU ) >> 2 ) ;
        a = ( ( a & 0x0F0F0F0FU ) << 4 ) | ( ( a & 0xF0F0F0F0U ) >> 4 ) ;
        a = ( ( a & 0x00FF00FFU ) << 8 ) | ( ( a & 0xFF00FF00U ) >> 8 ) ;
        a = ( ( a & 0x0000FFFFU ) << 16 ) | ( ( a & 0xFFFF0000U ) >> 16 ) ;
        return a >> (32 - NumBits);
    }
    void NTT(int on, int64_t *In, int64_t *Out, int n) {
        int NumBits = NumberOfBitsNeeded(n);
        for (int i = 0; i < n; ++i)
            Out[FastReverseBits(i, NumBits)] = In[i];
        for(int h = 2, id = 1; h <= n; h <<= 1, id++) {
            for(int j = 0; j < n; j += h) {
                int64_t w = 1, u, t;
                int block = h/2, blockEnd = j + h/2;
                for(int k = j; k < blockEnd; k++) {
                    u = Out[k], t = mod_mul(w, Out[k+block], P);
                    Out[k] = u + t;
                    Out[k + block] = u - t + P;
                    if (Out[k] >= P)        Out[k] -= P;
                    if (Out[k+block] >= P)  Out[k+block] -= P;
                    w = mod_mul(w, wn[id], P);
                }
            }
        }
        if (on == 1) {
            for (int i = 1; i < n/2; i++)
                swap(Out[i], Out[n-i]);
            int64_t invn = mod_pow(n, P-2, P);
            for (int i = 0; i < n; i++)
                Out[i] = mod_mul(Out[i], invn, P);
        }
    }
    void convolution(int64_t *a, int64_t *b, int n, int64_t *c) {
        NTT(0, a, d1, n);
		NTT(0, b, d2, n);
        for (int i = 0; i < n; i++)
            s[i] = mod_mul(d1[i], d2[i], P);
        NTT(1, s, c, n);
    }
} tool;

const int MAXN = 100005;
const int MOD = 7340033; 
static int64_t f[MAXN], inv_f[MAXN];
inline int64_t pmod(int64_t a, int64_t b, int32_t m) {
	a = a * b;
	if (a >= m)
		return a%m;
	return a;
}
void init() {
	const int n = 100005; 
	static int64_t inv[MAXN];
	inv[1] = 1;
	for (int i = 2; i < n; i++)
		inv[i] = MOD - pmod(MOD/i, inv[MOD%i], MOD);
	f[0] = 1, inv_f[0] = 1;
	for (int i = 1; i < n; i++)
		f[i] = pmod(f[i-1], i, MOD);
	for (int i = 1; i < n; i++)
		inv_f[i] = pmod(inv_f[i-1], inv[i], MOD);
}

int64_t C(int n, int m) {
	return pmod(pmod(f[n], inv_f[m], MOD), inv_f[n-m], MOD);
}

int to_pow2(int n) {
	int m = 1;
	while (m < n)
		m <<= 1;
	return m;
}

int main() {
	init();
	
	int testcase, cases = 0;
	int n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		int quad[2][2] = {};
		for (int i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			quad[x > 0][y > 0]++;
		}
		
		int x = min(quad[0][0], quad[1][1]);
		int y = min(quad[0][1], quad[1][0]);
		int m = to_pow2(2*max(x+1, y+1));
		static int64_t a[262144], b[262144], c[262144] = {};
		memset(a, 0, sizeof(a[0])*m);
		memset(b, 0, sizeof(b[0])*m);
		for (int i = 0; i <= x; i++)
			a[i] = pmod(C(quad[0][0], i), C(quad[1][1], i), MOD);
		for (int i = 0; i <= y; i++)
			b[i] = pmod(C(quad[0][1], i), C(quad[1][0], i), MOD);


		tool.convolution(a, b, m, c);
	
//		for (int i = 0; i < m; i++)
//			printf("%lld %lld %lld a, b, c\n", a[i], b[i], c[i]);
			
		printf("Case %d:\n", ++cases);
		for (int i = 1; i <= n; i++) {
			int64_t v = (i&1) ? 0 : c[i>>1];
			printf("%lld%c", v, " \n"[i==n]);
		}
	}
	return 0;
}
/*
2
3
-1  -1
1  1
2  2
4
1  1
-1  1
1  -1
-1  -1
*/
