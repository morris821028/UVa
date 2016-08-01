// Kirchhoff's theorem, Matrix Tree Theorem, determinant value
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;

// const long long PRIME_MOD = 1000000007LL;
const long long PRIME_MOD = 1000000000000037LL; // > 1e+15
const int MAXN = 64;

long long Q[MAXN][MAXN] = {}, L[MAXN][MAXN] = {};
int cg[MAXN][MAXN];

long long mul(long long a, long long b, long long mod) {
    if (b < 0)
        return -mul(a, -b, mod);
    long long ret = 0;
    for ( ; b != 0; b>>=1, (a<<=1)%=mod)
        if (b&1) (ret += a) %= mod;
    return ret;
}
// ax + by = g
void exgcd(long long x, long long y, long long &g, long long &a, long long &b) {
    if (y == 0)
        g = x, a = 1, b = 0;
    else
        exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}
long long llabs(long long x) {
    return x < 0 ? -x : x;
}
long long det(long long A[][MAXN], int n) {
    long long sum = 1;
    long long g, a, b;
    for (int i = 0; i < n; i++) {
        exgcd(A[i][i], PRIME_MOD, g, a, b);
        long long inv = a;
        if (g < 0)  inv = -inv;
        for (int j = i+1; j < n; j++) {
            for (int k = n - 1; k >= i; k--) {
                A[j][k] = A[j][k] - mul(mul(A[i][k], A[j][i], PRIME_MOD), inv, PRIME_MOD);
                A[j][k] = (A[j][k]%PRIME_MOD + PRIME_MOD) %PRIME_MOD;
            }
        }
        sum = mul(sum, A[i][i], PRIME_MOD);
        if (sum == 0)
            return 0;
    }
    if (sum < 0)    sum = (sum % PRIME_MOD + PRIME_MOD) %PRIME_MOD;
    return llabs(sum);
}
int main() {
//    long long g, a, b, llx = 70, lly = 11;
//    exgcd(llx, lly, g, a, b);
//    printf("%lld %lld + %lld %lld = %lld\n", llx, a, lly, b, g);
    int N, n;
    int x, y, testcase;
    scanf("%d", &testcase);
    while (testcase--) {
    	scanf("%d", &n), N = n*n;
        memset(cg, 0, sizeof(cg));
        memset(Q, 0, sizeof(Q));
        memset(L, 0, sizeof(L));
        
        const int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
        const int dy[] = {1, -1, 1, -1, 0, 1, -1, 0};
        for (int i = 0; i < n; i++) {
        	for (int j = 0; j < n; j++) {
        		int u, v, tx, ty;
        		u = i * n + j;
        		for (int k = 0; k < 8; k++) {
        			tx = i + dx[k], ty = j + dy[k];
        			if (tx < 0 || ty < 0 || tx >= n || ty >= n)
        				continue;
        			v = tx * n + ty;
        			cg[u][v] = cg[v][u] = 1;
        		}
        	}
        }
        
        // construct the Laplacian matrix Q
        for (int i = 0; i < N; i++) {
            int deg = 0;
            for (int j = 0; j < N; j++) {
                if (i != j && cg[i][j] == 1)  // has edge
                    Q[i][j] = -1, deg++;
            }
            Q[i][i] = deg;
        }
                
        // deleting row 1 and column 1 yields
        for (int i = 1; i < N; i++)
            for (int j = 1; j < N; j++)
                L[i-1][j-1] = Q[i][j];
        
        printf("%lld\n", det(L, N-1));
    }
    return 0;
}
/*

 
 */
