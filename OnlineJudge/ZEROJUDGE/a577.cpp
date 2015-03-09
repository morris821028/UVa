#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <math.h>
#include <iostream>
#include <map>
#include <complex>
#include <cmath>
using namespace std;

#define for if (0); else for
using namespace std;

const int MaxFastBits = 16;
int **gFFTBitTable = 0;

int NumberOfBitsNeeded(int PowerOfTwo) {
	for (int i = 0;; ++i) {
		if (PowerOfTwo & (1 << i)) {
			return i;
		}
	}
}

int ReverseBits(int index, int NumBits) {
	int ret = 0;
	for (int i = 0; i < NumBits; ++i, index >>= 1) {
		ret = (ret << 1) | (index & 1);
	}
	return ret;
}

void InitFFT() {
    gFFTBitTable = new int *[MaxFastBits];
    for (int i = 1, length = 2; i <= MaxFastBits; ++i, length <<= 1) {
        gFFTBitTable[i - 1] = new int[length];
        for (int j = 0; j < length; ++j) {
            gFFTBitTable[i - 1][j] = ReverseBits(j, i);
		}
    }
}
inline int FastReverseBits(int i, int NumBits) {
    return NumBits <= MaxFastBits ? gFFTBitTable[NumBits - 1][i] : ReverseBits(i, NumBits);
}

void FFT(bool InverseTransform, vector<complex<double> >& In, vector<complex<double> >& Out) {
    if (!gFFTBitTable) { InitFFT(); }
    // simultaneous data copy and bit-reversal ordering into outputs
	int NumSamples = In.size();
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
			complex<double> a1(cos1, sin1), a2(cos2, sin2);
            for (int j = i, n = 0; n < BlockEnd; ++j, ++n) {
				complex<double> a0(2 * cos1 * a1.real() - a2.real(), 2 * cos1 * a1.imag() - a2.imag());
				a2 = a1;
				a1 = a0;
				complex<double> a = a0 * Out[j + BlockEnd];
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

vector<double> convolution(vector<double> a, vector<double> b) {
	int n = a.size();
	vector<complex<double> > s(n), d1(n), d2(n), y(n);
    for (int i = 0; i < n; ++i) {
        s[i] = complex<double>(a[i], 0);
	}
    FFT(false, s, d1);
    s[0] = complex<double>(b[0], 0);
    for (int i = 1; i < n; ++i) {
		s[i] = complex<double>(b[n - i], 0);
	}
    FFT(false, s, d2);
    for (int i = 0; i < n; ++i) {
		y[i] = d1[i] * d2[i];
    }
    FFT(true, y, s);
	vector<double> ret(n);
	for (int i = 0; i < n; ++i) {
		ret[i] = s[i].real();
	}
	return ret;
}

struct Polynomial {
    vector<double> v;
    Polynomial operator*(const Polynomial &other) const {
        int n = (int) max(v.size(), other.v.size()) * 2, m;
        for (m = 2; m < n; m <<= 1);
        vector<double> na, nb;
        na.resize(m, 0), nb.resize(m, 0);
        for (int i = 0; i < v.size(); i++)
            na[i] = v[i];
        for (int i = 0, j = m - 1; i < other.v.size(); i++, j--)
            nb[j] = other.v[i];
        Polynomial ret;
        ret.v = convolution(na, nb);
        for (int i = 1; i < ret.v.size(); i++)
            ret.v[i - 1] = ret.v[i];
        ret.v[ret.v.size() - 1] = 0;
        return ret;
    }
};

char sa[1<<18], sb[1<<18];
long long ret[1<<19];
int main() {
    while (scanf("%s %s", sa, sb) == 2) {
        Polynomial a, b, c;
        for (int i = (int)strlen(sa) - 1; i >= 0; i--)
            a.v.push_back(sa[i] - '0');
        
        for (int i = (int)strlen(sb) - 1; i >= 0; i--)
            b.v.push_back(sb[i] - '0');
        c = a * b;
        
        memset(ret, 0, sizeof(ret));
        int f = 0;
        double eps = 1.5e-1;
        for (int i = 0; i < c.v.size(); i++)
            ret[i] = (long long) (c.v[i] + eps);
        int n = (int)c.v.size();
        for (int i = 0; i < n; i++) {
            if (ret[i] >= 10) {
                ret[i + 1] += ret[i]/10;
                ret[i] %= 10;
            }
        }
        for (int i = n; i >= 0; i--) {
            if (ret[i])
                f = 1;
            if (f)
                printf("%lld", ret[i]);
        }
        if (!f)
            printf("0");
        puts("");
    }
    return 0;
}
/*
 0
 5
 
 11
 12
 */
