#include <cstdio>
#include <cstring>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <assert.h>
#define MAXR 128
#define MAXN 128
#define eps 1e-6
#define MAXMN 65536
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
    int NumSamples = (int) In.size();
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
    int n = (int) a.size();
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
double a[MAXMN + 10], b[MAXMN + 10];
double grid_a[MAXN][MAXN];
int binaryResize(int n) {
    int v = 2;
    while(v < n)
        v <<= 1;
    return v;
}
double getArea(int lx, int ly, int rx, int ry) {
    double ret = 0;
    ret += grid_a[rx][ry];
    if(lx - 1 >= 0)
        ret -= grid_a[lx - 1][ry];
    if(ly - 1 >= 0)
        ret -= grid_a[rx][ly - 1];
    if(lx - 1 >= 0 && ly - 1 >= 0)
        ret += grid_a[lx - 1][ly - 1];
    return ret;
}

char circlePattern[MAXR][MAXN][MAXN], T[MAXN][MAXN];
int circleW[MAXR], circleH[MAXR], circlePixel[MAXR];
void printCircle(int r) {
    const double dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
    const double dy[] = {1, -1, 0, 1, -1, 0, 1, -1};
    double x, y;
    double cx = r, cy = r;
    circleW[r] = circleH[r] = 2 * r + 1, circlePixel[r] = 0;
    for (int i = 0; i <= 2 * r; i++) {
        for (int j = 0; j <= 2 * r; j++) {
            int in = 0, out = 0;
            for (int k = 0; k < 8; k++) {
                x = i + dx[k]/2, y = j + dy[k]/2;
                if (pow(x - cx, 2) + pow(y - cy, 2) < r*r - eps) {
                    in = 1;
                }
                if (pow(x - cx, 2) + pow(y - cy, 2) > r*r - eps) {
                    out = 1;
                }
            }
            circlePixel[r] += in&out;
            circlePattern[r][i][j] = (in&out) ? '1' : '0';
        }
        circlePattern[r][i][2 * r + 1] = '\0';
    }
}

struct Pos {
    int x, y, r;
    Pos(int a = 0, int b = 0, int c = 0):
    x(a), y(b), r(c) {}
    bool operator<(const Pos &a) const {
        if (r != a.r)   return r < a.r;
        if (y != a.y)   return y < a.y;
        return x < a.x;
    }
};
int main() {
    for (int i = 5; i < MAXR; i++)
        printCircle(i);
    int testcase, cases = 0;
    int m, n, p, q;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i++)
            scanf("%s", T[i]);
        vector<Pos> ret;
        
        int rrr = min(n, m);
        for (int ir = 5; ir <= rrr; ir++) {
            p = circleH[ir], q = circleW[ir];
            memset(a, 0, sizeof(a));
            memset(b, 0, sizeof(b));
            memset(grid_a, 0, sizeof(grid_a));
            int N;
            N = binaryResize(m);
            N = max(N, binaryResize(n));
            N = max(N, binaryResize(p));
            N = max(N, binaryResize(q));
            
//            for (int i = 0; i < p; i++)
//                printf("%s\n", circlePattern[ir][i]);

            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                    a[i * N + j] = T[i][j] == '1';
            
            for (int i = 0; i < p; i++) {
                for (int j = 0; j < q; j++) {
                    b[i * N + j] = circlePattern[ir][i][j] == '1';
                }
            }
            
            double column_sum[512] = {};
            for(int i = 0; i < N; i++) {
                for(int j = 0; j < N; j++) {
                    column_sum[j] += a[i*N + j]*a[i*N + j];
                    grid_a[i][j] += column_sum[j];
                    if(j)
                        grid_a[i][j] += grid_a[i][j-1];
                }
            }
            vector<double> r = convolution(vector<double>(a, a + N*N), vector<double>(b, b + N*N));
            int qx = m - p;
            int qy = n - q;
            for(int i = 0; i <= qx; i++)    {
                for(int j = 0; j <= qy; j++) {
                    double c = r[i*N + j];
                    if (c >= circlePixel[ir] * 0.98) {
                        ret.push_back(Pos(i + ir, j + ir, ir));
                    }
                }
            }
        }
        assert(ret.size() > 0);
        printf("Case %d: %d", ++cases, (int) ret.size());
        sort(ret.begin(), ret.end());
        for (int i = 0; i < ret.size(); i++)
            printf(" (%d,%d,%d)", ret[i].r, ret[i].y, ret[i].x);
        puts("");
    }
    return 0;
}

/*
999
30 30
000000000000000000000000000000
000000000000011111110000000000
000000000000110000011000000000
000000000001100000001100000000
000000000011000000000110000000
000000000110000000000011000000
000000011111110000000001000000
000001110100011100000001000000
000011000100000110000000000000
000110000100000011000001000000
001100000100000001100001000000
001000000110000000100011000000
011000000011000000110110000000
010000000001100000011100000000
010000000000110000011000000000
010000000000011111110000000000
010000000000000000010000000000
010000000000000000010000000000
011000000000000000110000000000
001000000000000000100000000000
001000000000000001100000000000
000110000000000011000000000000
000011000000000110000000000000
000001110000011100000000000000
000000011111110000000000000000
000000000000000000000000000000
000000000000000000000000000000
000000000000000000000000000000
000000000000000000000000000000
000000000000000000000000000000
*/