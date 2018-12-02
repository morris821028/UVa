#include <bits/stdc++.h>
using namespace std;

struct Complex {
    float x, y;
    Complex(double x = 0, double y = 0): x(x), y(y) {}
    Complex operator-(const Complex &v) const {
        return Complex(x-v.x,y-v.y);
    }
    Complex operator+(const Complex &v) const {
        return Complex(x+v.x,y+v.y);
    }
    Complex operator*(const Complex &v) const {
        return Complex(x*v.x-y*v.y,x*v.y+y*v.x);
    }
    Complex operator/(const int &v) const {
        return Complex(x/v,y/v);
    }
    double real() {
        return x;
    }
};
template<typename T> class TOOL_FFT {
public:
typedef unsigned int UINT32;
#define MAXN (1048576<<1)
    Complex p[2][MAXN];
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
    
    void FFT(bool InverseTransform, vector<Complex>& In, vector<Complex>& Out) {
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
                Complex *t = p[InverseTransform];
                for (register int k = 0; k < BlockEnd; k++, t += BlockCnt) {
                    Complex a = (*t) * Out[k+j+BlockEnd];
                    Out[k+j+BlockEnd] = Out[k+j] - a;
                    Out[k+j] = Out[k+j] + a;
                }
            }
        }
        // normalize if inverse transform
        if (InverseTransform) {
            for (int i = 0; i < NumSamples; ++i) {
                Out[i] = Out[i] / NumSamples;
            }
        }
    }
    void prework(int n) {
        if (pre_n == n)
            return ;
        pre_n = n;
        p[0][0] = Complex(1, 0);
        p[1][0] = Complex(1, 0);
        for (register int i = 1; i < n; i++) {
            p[0][i] = Complex(cos(2*i*PI / n ) , sin(2*i*PI / n ));
            p[1][i] = Complex(cos(2*i*PI / n ) , -sin(2*i*PI / n ));
        }
    }
    vector<T> convolution(Complex *a, Complex *b, int n) {
        prework(n);
        vector<Complex> s(a, a+n), d1(n), d2(n), y(n);
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

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m, o;
		scanf("%d %d %d", &n, &m, &o);

		static int row[50005] = {}, col[50005] = {}, dia[262144] = {};
		memset(dia, 0, sizeof(dia));
		memset(row, 0, sizeof(row));
		memset(col, 0, sizeof(col));
		int s = 1;
		while (s < n+m)
			s <<= 1;
		s <<= 1;
		for (int i = 0; i < o; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			x--, y--;
			row[x] = 1, col[y] = 1;
			if (x >= y) {
				dia[x-y] = 1;
			} else {
				dia[s-(y-x)] = 1;
			}
		}
		
		static Complex a[262144], b[262144];
	
		memset(a, 0, sizeof(a[0])*s);
		memset(b, 0, sizeof(b[0])*s);
		for (int i = 0; i < n; i++)
			a[i] = Complex(1-row[i], 0);
		for (int i = 0; i < m; i++)
			b[i] = Complex(1-col[i], 0);
		
		
		
		vector<double> c = tool.convolution(a, b, s);
//		for (int i = 0; i < n; i++)
//			printf("%.0lf ", a[i].x); puts("");
//		for (int i = 0; i < m; i++)
//			printf("%.0lf ", b[i].x); puts("");
		int64_t ret = 0;
		for (int i = 0; i < s; i++) {
			if (!dia[i]) {
				ret += round(c[i]);
			}
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
2
6 6 1
5 3
6 6 3
3 4
5 3
5 6

1
8 5 3
1 1
3 1
7 5
*/
