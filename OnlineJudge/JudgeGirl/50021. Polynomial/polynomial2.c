#include "polynomial.h"
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
// FFT header
#define MAXN 8192
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
#define UNLOOP8    {UNLOOP UNLOOP UNLOOP UNLOOP UNLOOP UNLOOP UNLOOP UNLOOP}
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

#define HIGHESTX 4095
static void normalize(Polynomial *poly) {
	int n = HIGHESTX;
	while (n > 0 && poly->v[n] == 0)
		n--;
	poly->n = n;
}
void init(Polynomial *poly, int coef[], int n) {
	memset(poly->v, 0, sizeof(poly->v));
	memcpy(poly->v, coef, sizeof(int) * n);
	normalize(poly);
}
Polynomial add(Polynomial *poly1, Polynomial *poly2) {
	Polynomial ret = *poly1;
	for (int i = 0; i <= poly2->n; i++)
		ret.v[i] += poly2->v[i];
	normalize(&ret);
	return ret;
}
Polynomial multiply(Polynomial *poly1, Polynomial *poly2) {
	static int tmp[4096], N, S;
	static double a[MAXN], b[MAXN], c[MAXN];
	N = poly1->n > poly2->n ? poly1->n : poly2->n;
	N++, N <<= 1;
    S = 1;
    for (; S < N; S <<= 1);
	memset(a, 0, sizeof(a[0]) * S);
    memset(b, 0, sizeof(b[0]) * S);
    for (int i = 0; i <= poly1->n; i++)
    	a[i] = poly1->v[i];
    for (int i = 1; i <= poly2->n; i++)
    	b[S-i] = poly2->v[i];
    b[0] = poly2->v[0];
	FFT.convolution(a, b, S, c);
	for (int i = poly1->n + poly2->n; i >= 0; i--)
		tmp[i] = round(c[i]);
	Polynomial ret;
	init(&ret, tmp, poly1->n + poly2->n + 1);
	normalize(&ret);
	return ret;
}
void print(Polynomial *poly) {
	normalize(poly);
	printf("%+d", poly->v[poly->n]);
	if (poly->n)	printf("x");
	if (poly->n > 1)	printf("^%d", poly->n);
	for (int i = poly->n-1; i >= 0; i--) {
		if (poly->v[i] == 0)
			continue;
		printf("%+d", poly->v[i]);
		if (i)	printf("x");
		if (i > 1)	printf("^%d", i);
	}
	puts("");
}
