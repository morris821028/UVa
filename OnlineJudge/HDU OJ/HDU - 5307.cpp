#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

typedef uint_fast32_t UINT32;
typedef long long INT64;
typedef uint_fast32_t INT32;
class TOOL_NTT {
public:
#define MAXN 262144
    //  INT64 P = 50000000001507329LL; // prime m = kn+1
    //  INT64 G = 3;
    INT32 P = 3, G = 2;
    INT32 wn[20];
    INT32 s[MAXN], d1[MAXN], d2[MAXN], c1[MAXN], c2[MAXN];
    const INT32 P1 = 998244353; // P1 = 2^23 * 7 * 17 + 1
    const INT32 G1 = 3;
    const INT32 P2 = 995622913; // P2 = 2^19 *3*3*211 + 1
    const INT32 G2 = 5;
    const INT64 M1 = 397550359381069386LL;
    const INT64 M2 = 596324591238590904LL;
    const INT64 MM = 993874950619660289LL; // MM = P1*P2
    TOOL_NTT() {
        for (int i = 0; i < 20; i++)
            wn[i] = mod_pow(G, (P-1) / (1<<i), P);
    }
    void reset(INT32 p, INT32 g) {
        P = p, G = g;
        for (int i = 0; i < 20; i++)
            wn[i] = mod_pow(G, (P-1) / (1<<i), P);
    }
    INT64 mod_mul(INT64 a, INT64 b, INT64 mod) {
        return (a*b - (long long)(a/(long double)mod*b+1e-3)*mod+mod)%mod;
        //      INT64 ret = 0;
        //      for (a = a >= mod ? a%mod : a, b = b >= mod ? b%mod : b; b != 0; b>>=1, a <<= 1, a = a >= mod ? a - mod : a) {
        //          if (b&1) {
        //              ret += a;
        //              if (ret >= mod)
        //                  ret -= mod;
        //          }
        //      }
        //      return ret;
    }
    INT64 mod_pow(INT64 n, INT64 e, INT64 m) {
        INT64 x = 1;
        for (n = n >= m ? n%m : n; e; e >>= 1) {
            if (e&1)
                x = mod_mul(x, n, m);
            n = mod_mul(n, n, m);
        }
        return x;
    }
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
    void NTT(int on, INT32 *In, INT32 *Out, int n) {
        int NumBits = NumberOfBitsNeeded(n);
        for (int i = 0; i < n; ++i)
            Out[FastReverseBits(i, NumBits)] = In[i];
        for (int h = 2, id = 1; h <= n; h <<= 1, id++) {
            for (int j = 0; j < n; j += h) {
                INT32 w = 1, u, t;
                int block = h/2, blockEnd = j + h/2;
                for (int k = j; k < blockEnd; k++) {
                    u = Out[k], t = (INT64)w*Out[k+block]%P;
                    Out[k] = (u + t)%P;
                    Out[k+block] = (u - t + P)%P;
                    w = (INT64)w * wn[id]%P;
                }
            }
        }
        if (on == 1) {
            for (int i = 1; i < n/2; i++)
                swap(Out[i], Out[n-i]);
            INT32 invn = mod_pow(n, P-2, P);
            for (int i = 0; i < n; i++)
                Out[i] = (INT64)Out[i]*invn%P;
        }
    }
    INT64 crt(INT32 a, INT32 b) {
        return (mod_mul(a, M1, MM) + mod_mul(b, M2, MM))%MM;
    }
    void convolution(INT32 *a, INT32 *b, int n, INT64 *c) {
        reset(P1, G1);
        NTT(0, a, d1, n);
        s[0] = b[0];    for (int i = 1; i < n; ++i) s[i] = b[n-i];
        NTT(0, s, d2, n);
        for (int i = 0; i < n; i++) s[i] = (INT64)d1[i] * d2[i]%P;
        NTT(1, s, c1, n);
        reset(P2, G2);
        NTT(0, a, d1, n);
        s[0] = b[0];    for (int i = 1; i < n; ++i) s[i] = b[n-i];
        NTT(0, s, d2, n);
        for (int i = 0; i < n; i++) s[i] = (INT64)d1[i] * d2[i]%P;
        NTT(1, s, c2, n);
        for (int i = 0; i < n; i++)
            c[i] = crt(c1[i], c2[i]);
    }
} tool;
INT32 a[262144], b[262144];
INT64 c[262144];
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
            a[sum[i]] += i;
            b[sum[i-1]] ++;
        }
        tool.convolution(a, b, m, c);
        for (int i = 1; i < m; i++)
            ret[i] += c[i];

        memset(a, 0, sizeof(a[0])*m);
        memset(b, 0, sizeof(b[0])*m);
        for (int i = 1; i <= n; i++) {
            a[sum[i]] ++;
            b[sum[i-1]] += i-1;
        }
        tool.convolution(a, b, m, c);
        for (int i = 1; i <= s; i++)
            ret[i] -= c[i];
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
