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
    static const int MAXN = 1<<17;
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
        for (int i = 0; i < n; i ++) {
            p[0][i] = complex(cos(2*i*PI / n), sin(2*i*PI / n));
            p[1][i] = complex(p[0][i].x, -p[0][i].y);
        }
        
        int NumBits = NumberOfBitsNeeded(n);
        for (int i = 0; i < n; i++)
        	reversePos[i] = FastReverseBits(i, NumBits);
    }
};

TOOL_FFT<double> tool;
struct BigInt {
	long long *v;
	int size;
	static const int DIGITS = 5;
	static const int MAXN = 1<<17;
	static int compare(const BigInt a, const BigInt b) {
		for (int i = MAXN-1; i >= 0; i--) {
			if (a.v[i] < b.v[i])
				return -1;
			if (a.v[i] > b.v[i])
				return 1;
		}
		return 0;
	}
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
			printf("%05lld", v[pos]);
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
        tool.convolution(na, nb, m, tmp);
        BigInt ret;
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
	BigInt divide(const BigInt &other, long long buf[]) const {
		{
			int cmp = compare(*this, other);
			BigInt ret;
			ret.size = MAXN-1, ret.v = buf;
			if (cmp == 0) {
				memset(buf, 0, sizeof(buf[0])*MAXN);
				buf[0] = 1;
				ret.reduce();
				return ret;
			} else if (cmp < 0) {
				memset(buf, 0, sizeof(buf[0])*MAXN);
				buf[0] = 0;
				ret.reduce();
				return ret;
			}
		}
		// A / B = A * (1/B)
		// x' = (2 - x * B) * x
		int m = MAXN;
		static double na[MAXN], nb[MAXN];
		static double invB[MAXN], netB[MAXN], tmpB[MAXN];
		static long long bufB[MAXN];
		int PRECISION = size+10;
		memset(nb+1, 0, sizeof(v[0])*(m-other.size));
        for (int i = 1, j = m-1; i < other.size; i++, j--)
            nb[j] = other.v[i];
        nb[0] = other.v[0];
        
		memset(invB, 0, sizeof(invB[0])*m);
		{
			long long t = 100000, a = other.v[other.size-1];
			if (other.size-2 >= 0)
				t = t*100000, a = a*100000+other.v[other.size-2];
			for (int i = PRECISION-other.size; i >= 0; i--) {
				invB[i] = t/a;
				t = (t%a)*100000;
			}
		}
		for (int it = 0; it < 100; it++) {
			// netB = xi * B
	        tool.convolution(invB, nb, m, netB);
	        long long carry = 0;
	        for (int i = 0; i <= PRECISION*2; i++) {
	        	bufB[i] = carry + (long long) (netB[i] + 1.5e-1);
	        	if (bufB[i] >= 100000)
	        		carry = bufB[i]/100000, bufB[i] %= 100000;
	        	else
	        		carry = 0;
				bufB[i] = -bufB[i];
	        }
	        // tmpB = 2 - xi * B
	        bufB[PRECISION] += 2;
	        memset(tmpB, 0, sizeof(tmpB[0])*m);
	        for (int i = 0; i <= PRECISION*2; i++) {
	        	if (bufB[i] < 0)
	        		bufB[i] += 100000, bufB[i+1]--;
	        	if (i != 0)
	        		tmpB[m-i] = bufB[i];
	        	else
	        		tmpB[i] = bufB[i];
			}
			// netB = tmpB * invB
			tool.convolution(invB, tmpB, m, netB);
			{
				long long carry = 0;
				memset(bufB, 0, sizeof(bufB[0])*m);
				for (int i = 0; i <= PRECISION*2; i++) {
					bufB[i] = carry + (long long) (netB[i] + 1.5e-1);
					if (bufB[i] >= 100000)
	        			carry = bufB[i]/100000, bufB[i] %= 100000;
	        		else
	        			carry = 0;
				}
			}
			
			{
				int same = 1;
				for (int i = PRECISION; same && i >= 5; i--)
					same &= ((long long) (invB[i]) == bufB[i+PRECISION]);
				if (same)
					break;
			}
			memset(invB, 0, sizeof(invB[0])*m);
	        for (int i = 0; i+PRECISION <= PRECISION*2; i++)
	        	invB[i] = bufB[i+PRECISION];
        }
        
        memset(na+1, 0, sizeof(v[0])*(m-size));
        for (int i = 1, j = m-1; i < size; i++, j--)
            na[j] = v[i];
        na[0] = v[0];
        tool.convolution(invB, na, m, netB);
		
        BigInt ret;
		ret.size = m-1;
        ret.v = buf;
        long long carry = 0;
		for (int i = 0; i < m; i++) {
        	buf[i] = carry + (long long) (netB[i] + 1.5e-1);
        	if (buf[i] >= 100000)
        		carry = buf[i]/100000, buf[i] %= 100000;
        	else
        		carry = 0;
		}
		for (int i = 0; i+PRECISION < m; i++)
			buf[i] = buf[i+PRECISION];
		memset(buf+PRECISION, 0, sizeof(buf[0])*(m-PRECISION));
        {
        	memset(na, 0, sizeof(na[0])*m);
        	for (int i = 1, j = m-1; i < m-1; i++, j--)
	            na[j] = buf[i];
	        na[0] = buf[0];
	        for (int i = 0; i < m; i++)
	        	nb[i] = other.v[i];
    		tool.convolution(nb, na, m, netB);
    		long long carry = 0;
    		for (int i = 0; i < m; i++) {
    			bufB[i] = (carry + (long long) (netB[i] + 1e-1));
	        	if (bufB[i] >= 100000)
	        		carry = bufB[i]/100000, bufB[i] %= 100000;
	        	else
	        		carry = 0;
			}
			carry = 0;
			for (int i = 0; i < m; i++) {
				bufB[i] = v[i] - bufB[i] + carry;
				if (bufB[i] < 0)
	        		bufB[i] += 100000, carry = -1;
	        	else
	        		carry = 0;
			}
			BigInt R;
			R.size = m-1, R.v = bufB;
			if (compare(other, R) <= 0) {
				buf[0]++;
				for (int i = 0; buf[i] >= 100000; i++)
					buf[i+1]++, buf[i] -= 100000;
			}
		}
        ret.reduce();
		return ret;
	}
};

int main() {
	static char sa[1<<20], sb[1<<20];
    while (scanf("%s %s", sa, sb) == 2) {
        static long long da[1<<19], db[1<<19], dc[1<<19];
        
        BigInt a, b, c;
        a.str2int(sa, da);
        b.str2int(sb, db);
        c = a.divide(b, dc);
        c.println();
    }
    return 0;
}

