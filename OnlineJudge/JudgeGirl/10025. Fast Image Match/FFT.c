#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
// FFT header
#define MAXN 262144
typedef struct {
	double x, y;
} complex;
typedef unsigned int UINT32;
typedef struct {
	int (* const NumberOfBitsNeeded) (int);
	UINT32 (* const FastReverseBits) (UINT32, int);
	void (* const FFT) (bool, complex[], complex[], int);
	void (* const convolution) (double *, double *, int , double *);
} FFT_namespace;
typedef struct {
	complex (* const init) (double, double);
	complex (* const add) (complex *a, complex *b);
	complex (* const sub) (complex *a, complex *b);
	complex (* const mul) (complex *a, complex *b);
} Complex_namespace;
complex init_complex(double a, double b) {
	complex t = {a, b};
	return t;
}
complex add_complex(complex *a, complex *b) {
	return init_complex(a->x + b->x, a->y + b->y);
}
complex substract_complex(complex *a, complex *b) {
	return init_complex(a->x - b->x, a->y - b->y);
}
complex multiply_complex(complex *a, complex *b) {
	return init_complex(a->x * b->x - a->y * b->y, a->x * b->y+ a->y * b->x);
}
Complex_namespace const Complex = {init_complex, add_complex, substract_complex, multiply_complex};
// FFT body
int NumberOfBitsNeeded(int PowerOfTwo) {
    for (int i = 0;; ++i) {
        if (PowerOfTwo & (1 << i)) {
            return i;
        }
    }
}
UINT32 FastReverseBits(UINT32 a, int NumBits) {
	a = ( ( a & 0x55555555U ) << 1 ) | ( ( a & 0xAAAAAAAAU ) >> 1 ) ;
	a = ( ( a & 0x33333333U ) << 2 ) | ( ( a & 0xCCCCCCCCU ) >> 2 ) ;
	a = ( ( a & 0x0F0F0F0FU ) << 4 ) | ( ( a & 0xF0F0F0F0U ) >> 4 ) ;
	a = ( ( a & 0x00FF00FFU ) << 8 ) | ( ( a & 0xFF00FF00U ) >> 8 ) ;
	a = ( ( a & 0x0000FFFFU ) << 16 ) | ( ( a & 0xFFFF0000U ) >> 16 ) ;
    return a >> (32 - NumBits);
}
void _FFT(bool InverseTransform, complex In[], complex Out[], int n) {
    // simultaneous data copy and bit-reversal ordering into outputs
    int NumSamples = n;
    int NumBits = NumberOfBitsNeeded(NumSamples);
    for (int i = 0; i < NumSamples; ++i) {
        Out[FastReverseBits(i, NumBits)] = In[i];
    }
    // the FFT process
    double angle_numerator = acos(-1.) * (InverseTransform ? -2 : 2);
    for (int BlockEnd = 1, BlockSize = 2; BlockSize <= NumSamples; BlockSize <<= 1) {
        double delta_angle = angle_numerator / BlockSize;
        double sin1 = sin(-delta_angle);
        double cos1 = cos(-delta_angle);
        double sin2 = sin(-delta_angle * 2);
        double cos2 = cos(-delta_angle * 2);
        for (int i = 0; i < NumSamples; i += BlockSize) {
            complex a1 = {cos1, sin1}, a2 = {cos2, sin2}, a0, a;
            int j, n;
            for (j = i, n = 0; n+8 < BlockEnd; ) {
#define UNLOOP {\
a0 = Complex.init(2 * cos1 * a1.x - a2.x, 2 * cos1 * a1.y - a2.y); \
a2 = a1, a1 = a0; \
a = Complex.mul(&a0, &Out[j + BlockEnd]); \
Out[j + BlockEnd] = Complex.sub(&Out[j], &a); \
Out[j] = Complex.add(&Out[j], &a); \
++j, ++n; }
#define UNLOOP8	{UNLOOP UNLOOP UNLOOP UNLOOP UNLOOP UNLOOP UNLOOP UNLOOP}
				UNLOOP8;
            }
            for (; n < BlockEnd; )
            	UNLOOP;
        }
        BlockEnd = BlockSize;
    }
    // normalize if inverse transform
    if (InverseTransform) {
        for (int i = 0; i < NumSamples; ++i) {
            Out[i].x = Out[i].x / NumSamples;
        }
    }
}
void convolution(double *a, double *b, int n, double *c) {
    static complex s[MAXN], d1[MAXN], d2[MAXN], y[MAXN];
    for (int i = 0; i < n; ++i)
        s[i] = Complex.init(a[i], 0);
    _FFT(false, s, d1, n);
    s[0] = Complex.init(b[0], 0);
    for (int i = 1; i < n; ++i)
        s[i] = Complex.init(b[n - i], 0);
    _FFT(false, s, d2, n);
    for (int i = 0; i < n; ++i)
        y[i] = Complex.mul(&d1[i], &d2[i]);
    _FFT(true, y, s, n);
    for (int i = 0; i < n; ++i)
        c[i] = s[i].x;
}
FFT_namespace const FFT = {NumberOfBitsNeeded, FastReverseBits, _FFT, convolution};
// FFT end
double a[MAXN], b[MAXN], c[MAXN];
long long sum[512][512];
long long getArea(int lx, int ly, int rx, int ry) {
    long long ret = sum[rx][ry];
    if (lx)	ret -= sum[lx-1][ry];
    if (ly)	ret -= sum[rx][ly-1];
    if (lx && ly)	ret += sum[lx-1][ly-1];
    return ret;
}
int main() {
	int m, n, p, q, x, N, M, S;
	while (scanf("%d %d %d %d", &m, &n, &p, &q) == 4) {
        N = m > p ? m : p, M = n > q ? n : q;
        S = 1;
        for (; S < N*M; S <<= 1);
        memset(a, 0, sizeof(a[0]) * S);
        memset(b, 0, sizeof(b[0]) * S);
        for (int i = 0; i < m; i++) {
        	long long s = 0;
            for (int j = 0; j < n; j++) {
				scanf("%d", &x);
            	a[i*M+j] = x;
        		s += x*x;
        		sum[i][j] = (i > 0 ? sum[i-1][j] : 0) + s;          
            }
        }
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < q; j++) {
				scanf("%d", &x);
            	b[i*M+j] = x;
            }
        }        
        FFT.convolution(a, b, S, c);
        int qx = m - p, qy = n - q, bX = 0, bY = 0;
        long long diff = LONG_MAX;
        for (int i = 0; i <= qx; i++)    {
            for (int j = 0; j <= qy; j++) {
                long long v = getArea(i, j, i+p-1, j+q-1) - 2*c[i*M + j] + 0.5;
                if (v < diff)
                    diff = v, bX = i, bY = j;
            }
        }
        printf("%d %d\n", bX+1, bY+1);
    }
    return 0;
}

