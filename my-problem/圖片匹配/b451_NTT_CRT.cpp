#include <bits/stdc++.h>
using namespace std;

typedef uint_fast32_t UINT32;
typedef long long INT64;
typedef uint_fast32_t INT32;
class TOOL_NTT {
public:
#define MAXN 262144
//	INT64 P = 50000000001507329LL; // prime m = kn+1
//	INT64 G = 3;
	INT32 P = 3, G = 2;
	INT32 wn[20];
	INT32 s[MAXN], d1[MAXN], d2[MAXN], c1[MAXN], c2[MAXN];
	const INT32 P1 = 998244353;	// P1 = 2^23 * 7 * 17 + 1
	const INT32 G1 = 3;
	const INT32 P2 = 995622913; // P2 = 2^19 *3*3*211 + 1
	const INT32 G2 = 5;
	const INT64 M1 = 397550359381069386LL;
	const INT64 M2 = 596324591238590904LL;
	const INT64 MM = 993874950619660289LL; // MM = P1*P2
	TOOL_NTT() {
		for (int i = 0; i < 20; i++)
			wn[i] = mod_pow(G, (P-1) / (1<<i), P);
	}
	void reset(INT32 p, INT32 g) {
		P = p, G = g;
		for (int i = 0; i < 20; i++)
			wn[i] = mod_pow(G, (P-1) / (1<<i), P);
	}
	INT64 mod_mul(INT64 a, INT64 b, INT64 mod) { 
	    long long y = (long long)((double)a*b/mod+0.5); // fast for P < 2^58
    	long long r = (a*b-y*mod)%mod;
    	return r < 0 ? r + mod : r;
//	  	INT64 ret = 0; 
//		for (a = a >= mod ? a%mod : a, b = b >= mod ? b%mod : b; b != 0; b>>=1, a <<= 1, a = a >= mod ? a - mod : a) { 
//			if (b&1) {
//				ret += a;
//				if (ret >= mod) 
//					ret -= mod;
//			} 
//		} 
//		return ret; 
	}
	INT64 mod_pow(INT64 n, INT64 e, INT64 m) {
    	INT64 x = 1;
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
	inline UINT32 FastReverseBits(UINT32 a, int NumBits) {
		a = ( ( a & 0x55555555U ) << 1 ) | ( ( a & 0xAAAAAAAAU ) >> 1 ) ;
		a = ( ( a & 0x33333333U ) << 2 ) | ( ( a & 0xCCCCCCCCU ) >> 2 ) ;
		a = ( ( a & 0x0F0F0F0FU ) << 4 ) | ( ( a & 0xF0F0F0F0U ) >> 4 ) ;
		a = ( ( a & 0x00FF00FFU ) << 8 ) | ( ( a & 0xFF00FF00U ) >> 8 ) ;
		a = ( ( a & 0x0000FFFFU ) << 16 ) | ( ( a & 0xFFFF0000U ) >> 16 ) ;
	    return a >> (32 - NumBits);
	}
	void NTT(int on, INT32 *In, INT32 *Out, int n) {
		int NumBits = NumberOfBitsNeeded(n);
		for (int i = 0; i < n; ++i)
	        Out[FastReverseBits(i, NumBits)] = In[i];
    	for (int h = 2, id = 1; h <= n; h <<= 1, id++) {
        	for (int j = 0; j < n; j += h) {
				INT32 w = 1, u, t;
				int block = h/2, blockEnd = j + h/2;
            	for (int k = j; k < blockEnd; k++) {
                	u = Out[k], t = (INT64)w*Out[k+block]%P;
                	Out[k] = (u + t)%P;
                	Out[k+block] = (u - t + P)%P;
                	w = (INT64)w * wn[id]%P;
            	}
        	}
    	}
		if (on == 1) {
			for (int i = 1; i < n/2; i++)
				swap(Out[i], Out[n-i]);
			INT32 invn = mod_pow(n, P-2, P);
			for (int i = 0; i < n; i++)
				Out[i] = (INT64)Out[i]*invn%P;
		}
	}
	INT64 crt(INT32 a, INT32 b) {
		return (mod_mul(a, M1, MM) + mod_mul(b, M2, MM))%MM;
	}
	void convolution(INT32 *a, INT32 *b, int n, INT64 *c) {
		reset(P1, G1);
		NTT(0, a, d1, n);
	    s[0] = b[0];	for (int i = 1; i < n; ++i) s[i] = b[n-i];
		NTT(0, s, d2, n);
		for (int i = 0; i < n; i++)	s[i] = (INT64)d1[i] * d2[i]%P;
		NTT(1, s, c1, n);
		reset(P2, G2);
		NTT(0, a, d1, n);
	    s[0] = b[0];	for (int i = 1; i < n; ++i) s[i] = b[n-i];
		NTT(0, s, d2, n);
		for (int i = 0; i < n; i++)	s[i] = (INT64)d1[i] * d2[i]%P;
		NTT(1, s, c2, n);
		for (int i = 0; i < n; i++)
			c[i] = crt(c1[i], c2[i]);
	}
} tool;
INT32 a[262144], b[262144];
INT64 c[262144];
long long sum[512][512];
inline long long getArea(int lx, int ly, int rx, int ry) {
    long long ret = sum[rx][ry];
    if(lx)	ret -= sum[lx-1][ry];
    if(ly)	ret -= sum[rx][ly-1];
    if(lx && ly)	ret += sum[lx-1][ly-1];
    return ret;
}
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
	int m, n, p, q, x, N, M, S;
    while (ReadInt(&m)) {
    	ReadInt(&n), ReadInt(&p), ReadInt(&q);
    	N = max(m, p), M = max(n, q);
        S = 1;
        for (; S < N*M; S <<= 1);
        memset(a, 0, sizeof(a[0]) * S);
        memset(b, 0, sizeof(b[0]) * S);
        for (int i = 0; i < m; i++) {
        	long long s = 0;
            for (int j = 0; j < n; j++) {
        		ReadInt(&x);
            	a[i*M+j] = x;
        		s += x*x;
        		sum[i][j] = (i > 0 ? sum[i-1][j] : 0) + s;          
            }
        }
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < q; j++) {
            	ReadInt(&x);
            	b[i*M+j] = x;
            }
        }        
        tool.convolution(a, b, S, c);
        int qx = m - p, qy = n - q, bX = 0, bY = 0;
        long long diff = LONG_MAX;
        for (int i = 0; i <= qx; i++) {
            for (int j = 0; j <= qy; j++) {
                long long v = getArea(i, j, i+p-1, j+q-1) - 2*c[i*M + j];
                if (v < diff)
                    diff = v, bX = i, bY = j;
            }
        }
        fprintf(stderr, "diff = %lld\n", diff);
        printf("%d %d\n", bX+1, bY+1);
    }
    return 0;
}

