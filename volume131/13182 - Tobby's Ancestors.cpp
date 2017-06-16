#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <omp.h>
#include <algorithm>
using namespace std;
// FFT header
#define MAXN 524288
typedef struct {
	float x, y;
} complex;
typedef unsigned int UINT32;

typedef struct {
	int (* const NumberOfBitsNeeded) (int);
	UINT32 (* const FastReverseBits) (UINT32, int);
	void (* const FFT) (bool, complex[], complex[], int);
	void (* const convolution) (float *, float *, int , float *);
} FFT_namespace;

static inline complex init_complex(float a, float b) {
	complex t = {a, b};
	return t;
}
static inline complex add_complex(complex *a, complex *b) {
	return init_complex(a->x + b->x, a->y + b->y);
}
static inline complex sub_complex(complex *a, complex *b) {
	return init_complex(a->x - b->x, a->y - b->y);
}
static inline complex mul_complex(complex *a, complex *b) {
	return init_complex(a->x * b->x - a->y * b->y, a->x * b->y+ a->y * b->x);
}
static complex pre_theta[2][MAXN];
void prework(int n) {
	static int pre_n = 0;
	static const double PI = acos(-1);
    if (pre_n == n)
        return ;
    pre_n = n;
    pre_theta[0][0] = init_complex(1, 0);
    pre_theta[1][0] = init_complex(1, 0);
    for (register int i = 1; i < n; i++) {
        pre_theta[0][i] = init_complex(cosf(2*i*PI / n ) , sinf(2*i*PI / n ));
        pre_theta[1][i] = init_complex(cosf(2*i*PI / n ) , -sinf(2*i*PI / n ));
    }
}
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
    for (int i = 0; i < NumSamples; ++i)
        Out[FastReverseBits(i, NumBits)] = In[i];
    // the FFT process
    for (int i = 1; i <= NumBits; i++) {
        int BlockSize = 1<<i, BlockEnd = BlockSize>>1, BlockCnt = NumSamples/BlockSize;
        for (int j = 0; j < NumSamples; j += BlockSize) {
            complex *t = pre_theta[InverseTransform];
            for (int k = 0; k < BlockEnd; k++, t += BlockCnt) {
                complex a = mul_complex(&(*t), &Out[k+j+BlockEnd]);
                Out[k+j+BlockEnd] = sub_complex(&Out[k+j], &a);
                Out[k+j] = add_complex(&Out[k+j], &a);
            }
        }
    }
    
    // normalize if inverse transform
    if (InverseTransform) {
        for (int i = 0; i < NumSamples; ++i) {
            Out[i].x = Out[i].x / NumSamples;
        }
    }
}
void convolution(float *a, float *b, int n, float *c) {
    static complex s[MAXN], d1[MAXN], d2[MAXN], y[MAXN];
    prework(n);
    for (int i = 0; i < n; ++i)
        s[i] = init_complex(a[i], 0);
    _FFT(false, s, d1, n);
    s[0] = init_complex(b[0], 0);
    for (int i = 1; i < n; ++i)
        s[i] = init_complex(b[n - i], 0);
    _FFT(false, s, d2, n);
    for (int i = 0; i < n; ++i)
        y[i] = mul_complex(&d1[i], &d2[i]);
    _FFT(true, y, s, n);
    for (int i = 0; i < n; ++i)
        c[i] = s[i].x;
}
FFT_namespace const FFT = {NumberOfBitsNeeded, FastReverseBits, _FFT, convolution};
// FFT end


int main() {
	static char sa[MAXN], sb[MAXN];
	static int cc[MAXN];
	static float a[MAXN], b[MAXN], tmp[MAXN];
	while (scanf("%s", sb) == 1) {
		scanf("%s", sa);
		
		const int na = strlen(sa), nb = strlen(sb);
		const char charset[6] = "ATCG";
		
		int m = 1;
		for (m = 1; m < na+nb; m <<= 1);
		
		memset(cc, 0, sizeof(cc[0])*m);
		memset(a, 0, sizeof(a[0])*m);
		memset(b, 0, sizeof(b[0])*m);
		for (int i = 0; i < 4; i++) {
			char c = charset[i];
			for (int j = 0; j < na; j++)
				a[j+nb] = sa[j] == c;
			for (int j = 0; j < nb; j++)
				b[j] = sb[j] == c;
			
			FFT.convolution(a, b, m, tmp);
			for (int j = 0; j < m; j++)
				cc[j] += (int) (tmp[j] + 0.5f);
		}
		
		int best = 0, best_pos = 0;
		for (int i = 0; i < m; i++) {
			if (cc[i] > best)
				best = cc[i], best_pos = i;
		}
		printf("%d\n", best);
		if (best == 0) {
			puts("No matches");
		} else {
			for (int i = 0; i < m; i++) {
				char ca = -1, cb = -1;
				if (i >= nb && i < na+nb)
					ca = sa[i-nb];
				if (i >= best_pos && i-best_pos < nb)
					cb = sb[i-best_pos];
				if (ca != -1 || cb != -1) {
					if (ca == -1)	
						putchar(cb);
					else if(cb == -1)
						putchar(ca);
					else
						putchar(ca == cb ? ca : 'X');
				}
			}
			
			puts("");
		}
		puts("");
	}
	return 0;
}
/*
GATTACCA
TACAACAG

TACAACAG
GATTACCA

ATTG
GCCA

GCCA
ATTG

GCCA
TGCC

GATTACCA
TACAACAG
AAAA
GGGG
ATTG
GCCA
*/

