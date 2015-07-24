#include <bits/stdc++.h>
using namespace std;

template<typename T> class TOOL_FFT {
public:
typedef unsigned int UINT32;	
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
	
	void FFT(bool InverseTransform, vector<complex<T> >& In, vector<complex<T> >& Out) {
	    // simultaneous data copy and bit-reversal ordering into outputs
	    int NumSamples = In.size();
	    int NumBits = NumberOfBitsNeeded(NumSamples);
	    for (int i = 0; i < NumSamples; ++i) {
	        Out[FastReverseBits(i, NumBits)] = In[i];
	    }
	    // the FFT process
	    T angle_numerator = acos(-1.) * (InverseTransform ? -2 : 2);
	    for (int BlockEnd = 1, BlockSize = 2; BlockSize <= NumSamples; BlockSize <<= 1) {
	        T delta_angle = angle_numerator / BlockSize;
	        T sin1 = sin(-delta_angle);
	        T cos1 = cos(-delta_angle);
	        T sin2 = sin(-delta_angle * 2);
	        T cos2 = cos(-delta_angle * 2);
	        for (int i = 0; i < NumSamples; i += BlockSize) {
	            complex<T> a1(cos1, sin1), a2(cos2, sin2), a0;
	            for (int j = i, n = 0; n < BlockEnd; ++j, ++n) {
	                a0 = complex<T>(2 * cos1 * a1.real() - a2.real(), 2 * cos1 * a1.imag() - a2.imag());
	                a2 = a1;
	                a1 = a0;
	                complex<T> a = a0 * Out[j + BlockEnd];
	                Out[j + BlockEnd] = Out[j] - a;
	                Out[j] += a;
	            }
	        }
	        BlockEnd = BlockSize;
	    }
	    // normalize if inverse transform
	    if (InverseTransform) {
	        for (int i = 0; i < NumSamples; ++i) {
	            Out[i] /= NumSamples;
	        }
	    }
	}
	
	vector<T> convolution(T *a, T *b, int n) {
	    vector<std::complex<T>> s(n), d1(n), d2(n), y(n);
	    vector<T> ret(n);
	    for (int i = 0; i < n; ++i) {
	        s[i] = complex<T>(a[i], 0);
	    }
	    FFT(false, s, d1);
	    s[0] = complex<T>(b[0], 0);
	    for (int i = 1; i < n; ++i) {
	        s[i] = complex<T>(b[n - i], 0);
	    }
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

double a[262144], b[262144];
long long sum[512][512];
long long getArea(int lx, int ly, int rx, int ry) {
    long long ret = sum[rx][ry];
    if(lx-1 >= 0)
        ret -= sum[lx-1][ry];
    if(ly-1 >= 0)
		ret -= sum[rx][ly-1];
    if(lx-1 >= 0 && ly-1 >= 0)	
		ret += sum[lx-1][ly-1];
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
            for (int j = 0; j < n; j++) {
            	ReadInt(&x);
            	a[i*M+j] = x;                
            }
        }
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < q; j++) {
            	ReadInt(&x);
            	b[i*M+j] = x;
            }
        }
        
        for (int i = 0; i < m; i++) {
        	long long s = 0;
        	for (int j = 0; j < n; j++) {
        		x = a[i*M+j];
        		s += x*x;
        		sum[i][j] = (i > 0 ? sum[i-1][j] : 0) + s;
        	}
        }
        vector<double> r = tool.convolution(a, b, S);
        int qx = m - p, qy = n - q, bX = 0, bY = 0;
        long long diff = LONG_MAX;
        for (int i = 0; i <= qx; i++)    {
            for (int j = 0; j <= qy; j++) {
                long long v = round(getArea(i, j, i+p-1, j+q-1) - 2*r[i*M + j]);
                if (v < diff) {
                    diff = v, bX = i, bY = j;
                }
            }
        }
        printf("%d %d\n", bX+1, bY+1);
    }
    return 0;
}

