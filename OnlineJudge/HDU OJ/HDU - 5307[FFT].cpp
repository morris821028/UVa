#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <complex>
using namespace std;

template<typename T> class TOOL_FFT {
public:
typedef unsigned int UINT32;
#define MAXN 262144
    complex<T> p[2][MAXN];
    int pre_n;
    T PI;
    TOOL_FFT() {
        pre_n = 0;
        PI = acos(-1);
    }
    int NumberOfBitsNeeded(int PowerOfTwo) {
        for (int i = 0; ; ++i) {
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
    
    void FFT(bool InverseTransform, vector<complex<T> >& In, vector<complex<T> >& Out) {
        // simultaneous data copy and bit-reversal ordering into outputs
        int NumSamples = In.size();
        int NumBits = NumberOfBitsNeeded(NumSamples);
        for (int i = 0; i < NumSamples; ++i) {
            Out[FastReverseBits(i, NumBits)] = In[i];
        }
        // the FFT process
        for (register int i = 1; i <= NumBits; i++) {
            int BlockSize = 1<<i, BlockEnd = BlockSize>>1, BlockCnt = NumSamples/BlockSize;
            for (register int j = 0; j < NumSamples; j += BlockSize) {
                complex<T> *t = p[InverseTransform];
                for (register int k = 0; k < BlockEnd; k++, t += BlockCnt) {
                    complex<T> a = (*t) * Out[k+j+BlockEnd];
                    Out[k+j+BlockEnd] = Out[k+j] - a;
                    Out[k+j] += a;
                }
            }
        }
        // normalize if inverse transform
        if (InverseTransform) {
            for (int i = 0; i < NumSamples; ++i) {
                Out[i] /= NumSamples;
            }
        }
    }
    void prework(int n) {
        if (pre_n == n)
            return ;
        pre_n = n;
        p[0][0] = complex<T>(1, 0);
        p[1][0] = complex<T>(1, 0);
        for (register int i = 1; i < n; i++) {
            p[0][i] = complex<T>(cos(2*i*PI / n ) , sin(2*i*PI / n ));
            p[1][i] = complex<T>(cos(2*i*PI / n ) , -sin(2*i*PI / n ));
        }
    }
    vector<T> convolution(complex<T> *a, complex<T> *b, int n) {
        prework(n);
        vector< complex<T> > s(a, a+n), d1(n), d2(n), y(n);
        vector<T> ret(n);
        FFT(false, s, d1);
        s[0] = b[0];
        for (int i = 1, j = n-1; i < n; ++i, --j)
            s[i] = b[j];
        FFT(false, s, d2);
        for (int i = 0; i < n; ++i) {
            y[i] = d1[i] * d2[i];
        }
        FFT(true, y, s);
        for (int i = 0; i < n; ++i) {
            ret[i] = s[i].real();
        }
        return ret;
    }
};
TOOL_FFT<double> tool;

complex<double> a[MAXN], b[MAXN];
vector<double> c;
int A[MAXN], sum[MAXN];
long long ret[MAXN], pr[262144];
int main() {
    pr[0] = 0;
    for (int i = 1; i < MAXN; i++)
        pr[i] = pr[i-1] + (long long)i*(i+1)/2;
    int testcase, n, m, s;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &A[i]);
        sum[0] = 0;
        for (int i = 1; i <= n; i++)
            sum[i] = sum[i-1] + A[i];
        
        s = sum[n];
        memset(ret, 0, sizeof(ret[0]) * (s+1));
        for (m = 1; m <= (s<<1); m <<= 1);
        
        memset(a, 0, sizeof(a[0])*m);
        memset(b, 0, sizeof(b[0])*m);
        for (int i = 1; i <= n; i++) {
            a[sum[i]] += complex<double>(i, 0);
            b[sum[i-1]] += complex<double>(1, 0);
        }
        
        c = tool.convolution(a, b, m);
        for (int i = 1; i < m; i++)
            ret[i] += round(c[i]);

        memset(a, 0, sizeof(a[0])*m);
        memset(b, 0, sizeof(b[0])*m);
        for (int i = 1; i <= n; i++) {
            a[sum[i]] += complex<double>(1, 0);
            b[sum[i-1]] += complex<double>(i-1, 0);
        }
        c = tool.convolution(a, b, m);
        for (int i = 1; i <= s; i++)
            ret[i] -= round(c[i]);
        for (int i = 1, z = 0; i <= n+1; i++) {
            if (i == n+1 || A[i] != 0)
                ret[0] += pr[z], z = 0;
            else
                z++;
        }        
        for (int i = 0; i <= s; i++) {
            printf("%lld\n", ret[i]);
        }
    }
    return 0;
}
