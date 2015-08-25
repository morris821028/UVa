#include <bits/stdc++.h>
using namespace std;


typedef uint_fast32_t UINT32;
typedef long long INT64;
typedef int_fast32_t INT32;
class TOOL_NTT {
public:
#define MAXN 32767
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

const double pi = acos(-1);
void make(const char *s, double A[], int R, int N) {
	int a = 0, b = 0, c = 0;
	double F;	
	for (int i = 0; s[i]; i++) {
		if (isupper(s[i]))		a = s[i];
		else if (isdigit(s[i]))	b = s[i] - '0';
		else if (s[i] == '#')	c = 1;
		else if (s[i] == 'b')	c = -1;
	} 
	double w[] = {0, 2, 3, 5, 7, 8, 10};
	int ww = w[a - 'A'];
	if (a == 'A' || a == 'B')	b++;
	ww += c;
	F = exp(log(220) + (log(440) - log(220)) * ww / 12) * pow(2, b - 4);
	double d = F * 2 * pi / R;
	int ret = 1;
	for (int i = 0; i < N; i++) {
		double f = sin(i * d);
		A[i] = 32767 * f;
	}
}
double test(double A[], double B[], int N) {
	int M = 1;
	INT32 mA[8192], mB[8192];
	INT64 mC[8192];
	for (M = 1; M < N; M <<= 1);
	assert(M <= 8192);
	double sqA = 0, sqB = 0;
	for (int i = 0; i < M; i++) {
		mA[i] = round(A[i%N]);
		mB[i] = round(B[i%N]);
		sqA += mA[i] * mA[i];
		sqB += mB[i] * mB[i];
	}
	tool.convolution(mA, mB, M, mC);
	
	double test = sqA + sqB;
	for (int i = 0; i < M; i++)
		test = min(test, sqA - 2.0 * mC[i] + sqB);
	return test;
}
int main() {
	char s[1024];
	int R = 8000, N = 8000;
	double A[65536] = {}, B[65536] = {};
	scanf("%d %d", &R, &N);
	for (int i = 0; i < N; i++)
		scanf("%lf", &B[i]);
	
	double mn = -1;
	string best = "";
	for (int i = 'A'; i <= 'G'; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = '1'; k <= '9'; k++) {
				string s;
				s += string(1, i);
				if (j == 1)		s += '#';
				if (j == -1)	s += 'b';
				s += string(1, k);
				make(s.c_str(), A, R, N);
				double f = test(A, B, N);
				if (mn < 0 || f < mn)
					mn = f, best = s;
				printf("%s %lf\n", s.c_str(), f);
//				if (s == "C#4")
//					return 0;
			}
		}
	}
	printf("%s\n", best.c_str());
	return 0;
}
/*
8000 8
0 7077 13820 19911 25062 29029 31627 32731
*/
