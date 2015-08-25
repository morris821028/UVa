#include <bits/stdc++.h>
using namespace std;

template<typename T> class M_FFT {
public:
	 struct complex {
        T x, y;
        complex(T x = 0, T y = 0):
            x(x), y(y) {}
        complex operator+(const complex &A) {
            return complex(x+A.x,y+A.y);
        }
        complex operator-(const complex &A) {
            return complex(x-A.x,y-A.y);
        }
        complex operator*(const complex &A) {
            return complex(x*A.x-y*A.y,x*A.y+y*A.x);
        }
    };
typedef unsigned int UINT32;
	static const int MAXN = 8192;
    complex p[2][MAXN];
    int pre_n;
    T PI;
    M_FFT() {
        pre_n = 0;
        PI = acos(-1);
    }
    int NumberOfBitsNeeded(int PowerOfTwo) {
        for (int i = 0; ; ++i) {
            if (PowerOfTwo & (1 << i))
                return i;
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
    
    void FFT(bool InverseTransform, vector<complex>& In, vector<complex>& Out) {
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
                complex *t = p[InverseTransform];
                for (register int k = 0; k < BlockEnd; k++, t += BlockCnt) {
                    complex a = (*t) * Out[k+j+BlockEnd];
                    Out[k+j+BlockEnd] = Out[k+j] - a;
                    Out[k+j] = Out[k+j] + a;
                }
            }
        }
        // normalize if inverse transform
        if (InverseTransform) {
            for (int i = 0; i < NumSamples; ++i) {
                Out[i].x /= NumSamples;
            }
        }
    }
    void prework(int n) {
        if (pre_n == n)	return ;
        pre_n = n;
        p[0][0] = complex(1, 0);
        p[1][0] = complex(1, 0);
        for (register int i = 1; i < n; i++) {
            p[0][i] = complex(cos(2*i*PI / n ) , sin(2*i*PI / n ));
            p[1][i] = complex(cos(2*i*PI / n ) , -sin(2*i*PI / n ));
        }
    }
    vector<T> convolution(complex *a, complex *b, int n) {
        prework(n);
        vector<complex> s(a, a+n), d1(n), d2(n), y(n);
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
        for (int i = 0; i < n; ++i)
            ret[i] = s[i].x;
        return ret;
    }
};
M_FFT<double> tool;

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
		A[i] = round(32767 * f);
	}
}
double test(double A[], double B[], int N) {
	int M = 1;
	M_FFT<double>::complex mA[8192], mB[8192];
	for (M = 1; M < N; M <<= 1);
	int match = N/2;
	double sqA[8192] = {}, sqB = 0;
	for (int i = 0; i < M; i++) {
		mA[i] = M_FFT<double>::complex(A[i%N], 0);
		if (i < match)
			mB[i] = M_FFT<double>::complex(B[i%N], 0);
		else
			mB[i] = M_FFT<double>::complex(0, 0);
		sqA[i] = sqA[i-1] + mA[i%N].x * mA[i%N].x;
		sqB += mB[i%N].x * mB[i%N].x;
	}
	vector<double> v = tool.convolution(mA, mB, M);
	
	double test = sqA[M-1] + sqB;
	for (int i = 0; i < N - match; i++) {
		double sum = sqA[i + match - 1] - (i ? sqA[i-1] : 0);
		test = min(test, sum - 2 * v[i] + sqB);
	}
	return test;
}
int main() {
	char s[1024];
	int R = 8000, N = 8000;
	double A[65536] = {}, B[65536] = {}, C[65536];
	scanf("%d %d", &R, &N);
	for (int i = 0; i < N; i++)
		scanf("%lf", &B[i]);
	N = min(N, 4096);
	double mn = -1;
	string best = "";
	for (int k = '9'; k >= '1'; k--) {
		for (int i = 'A'; i <= 'G'; i++) {
			for (int j = -1; j <= 1; j++) {
				string s;
				s += string(1, i);
				if (j == 1)		s += '#';
				if (j == -1)	s += 'b';
				s += string(1, k);
				make(s.c_str(), A, R, N);
				double f = test(A, B, N);
				if (mn < 0 || f <= mn)
					mn = f, best = s;
			}
		}
	}
	printf("%s\n", best.c_str());
	return 0;
}
/*
8000 8
0 7077 13820 19911 25062 29029 31627 32731
62455006276.999878
62455006276.999878
*/

