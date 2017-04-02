#include <bits/stdc++.h>
using namespace std;

template<typename T> class TOOL_FFT {
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
    T PI;
    static const int MAXN = 1<<16;
    complex p[2][MAXN];
    int reversePos[MAXN];
    TOOL_FFT() {
        PI = acos(-1);
        preprocessing();
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
    
    void FFT(bool InverseTransform, complex In[], complex Out[], int n) {
        // simultaneous data copy and bit-reversal ordering into outputs
        int NumSamples = n;
        int NumBits = NumberOfBitsNeeded(NumSamples);
        for (int i = 0; i < NumSamples; ++i) 
            Out[reversePos[i]] = In[i];
            
        // the FFT process
        for (int i = 1; i <= NumBits; i++) {
            int BlockSize = 1<<i, BlockEnd = BlockSize>>1, BlockCnt = NumSamples/BlockSize;
            for (int j = 0; j < NumSamples; j += BlockSize) {
                complex *t = p[InverseTransform];
                int k = 0;
#define UNLOOP_SIZE 8
                for (; k+UNLOOP_SIZE < BlockEnd; ) {
#define UNLOOP { \
	complex a = (*t) * Out[k+j+BlockEnd]; \
    Out[k+j+BlockEnd] = Out[k+j] - a; \
    Out[k+j] = Out[k+j] + a;\
    k++, t += BlockCnt;\
}
#define UNLOOP4 {UNLOOP UNLOOP UNLOOP UNLOOP;}
#define UNLOOP8 {UNLOOP4 UNLOOP4;}
					UNLOOP8;
				}
				for (; k < BlockEnd;)
					UNLOOP;
            }
        }
        // normalize if inverse transform
        if (InverseTransform) {
            for (int i = 0; i < NumSamples; ++i) {
                Out[i] = Out[i].x / NumSamples;
            }
        }
    }
    void convolution(T *a, T *b, int n, T *c) {
        static complex s[MAXN], d1[MAXN], d2[MAXN], y[MAXN];
    	n = MAXN;
        for (int i = 0; i < n; ++i)
            s[i] = complex(a[i], 0);
        FFT(false, s, d1, n);
        s[0] = complex(b[0], 0);
        for (int i = 1; i < n; ++i)
            s[i] = complex(b[n - i], 0);
        FFT(false, s, d2, n);
        for (int i = 0; i < n; ++i)
            y[i] = d1[i] * d2[i];
        FFT(true, y, s, n);
        for (int i = 0; i < n; ++i)
            c[i] = s[i].x;
    }
    void preprocessing() {
        int n = MAXN;
        const int BLOCK = 32;
        const double cosT = cos(2*PI/n);
        const double sinT = sin(2*PI/n);
        for (int i = 0; i < n; i += BLOCK) {
            p[0][i] = complex(cos(2*i*PI / n), sin(2*i*PI / n));
            p[1][i] = complex(p[0][i].x, -p[0][i].y);
            double cT = p[0][i].x, sT = p[0][i].y;
            for (int j = 1; j < BLOCK; j++) {
            	double cnT, snT;
            	cnT = cosT*cT - sinT*sT;
            	snT = cosT*sT + sinT*cT;
            	p[0][i+j] = complex(cnT, snT);
            	p[1][i+j] = complex(cnT, -snT);
            	cT = cnT, sT = snT;
			}
        }
        
        int NumBits = NumberOfBitsNeeded(n);
        for (int i = 0; i < n; i++)
        	reversePos[i] = FastReverseBits(i, NumBits);
    }
};

struct PrintPaddingInt {
	char s[100000][6];
	PrintPaddingInt() {
		memset(s, 0, sizeof(s));
		const int D = 5;
		for (int i = 0; i < D; i++)
			s[0][i] = '0';
		for (int i = 1; i < 100000; i++) {
			memcpy(s[i], s[i/10]+1, sizeof(s[0][0])*(D-1));
			s[i][D-1] = '0' + i%10;
		}
	}
	void out(int x) {
		fputs(s[x], stdout);
	}
};
TOOL_FFT<double> tool;
PrintPaddingInt printer;
struct BigInt {
	long long *v;
	int size;
	static const int DIGITS = 5;
	static const int MAXN = 1<<16;
	void str2int(char *s, long long buf[]) {
		int n = strlen(s);
		size = (n+DIGITS-1) / DIGITS;
		int cnt = n%DIGITS == 0 ? DIGITS : n%DIGITS;
		int x = 0, pos = size-1;
		v = buf;
		for (int i = 0; i < n; i++) {
			x = x*10 + s[i] - '0';
			if (--cnt == 0) {
				cnt = DIGITS;
				v[pos--] = x, x = 0;
			}
		}
	}
	void println() {
		printf("%lld", v[size-1]);
		for (int pos = size-2; pos >= 0; pos--)
			printer.out(v[pos]);
		puts("");
	}
	BigInt multiply(const BigInt &other, long long buf[]) const {
		int m = MAXN;
		static double na[MAXN], nb[MAXN];
		static double tmp[MAXN];
		memset(na+size, 0, sizeof(v[0])*(m-size));
		for (int i = 0; i < size; i++)
			na[i] = v[i];
		memset(nb+1, 0, sizeof(v[0])*(m-other.size));
        for (int i = 1, j = m-1; i < other.size; i++, j--)
            nb[j] = other.v[i];
        nb[0] = other.v[0];
        BigInt ret;
        tool.convolution(na, nb, m, tmp);
        ret.size = m;
        ret.v = buf;
        for (int i = 0; i < m; i++)
        	buf[i] = (long long) (tmp[i] + 1.5e-1);
        for (int i = 0; i < m; i++) {
        	if (buf[i] >= 100000)
        		buf[i+1] += buf[i]/100000, buf[i] %= 100000;
		}
        ret.reduce();
        return ret;
	}
	void reduce() {
		while (size > 1 && fabs(v[size-1]) < 5e-1)
			size--;
	}
};

int main() {
	static char sa[1<<18], sb[1<<18];
    while (scanf("%s %s", sa, sb) == 2) {
        static long long da[1<<19], db[1<<19], dc[1<<19];
        
        BigInt a, b, c;
        a.str2int(sa, da);
        b.str2int(sb, db);
        c = a.multiply(b, dc);
        c.println();
    }
    return 0;
}

