#include <cstdio>
#include <cstring>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <assert.h>
#define MAXN 512
#define INF 0x3f3f3f3f
#define eps 1e-6
using namespace std;

int g[MAXN][MAXN], A, B, N, M;
long long getHeight(int w, int h, int v) {
    if (v == 0) return 0;
    v = -v;
    int base = v * w * h;
    int ret = base / (N*M - w*h) - (base % (N*M - w*h) == 0);
    return ret + v;
}
int main() {
    while (scanf("%d %d %d %d", &A, &B, &N, &M) == 4) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf("%d", &g[i][j]);
                g[i][j] = -g[i][j];
            }
        }
        if (A > B)  swap(A, B);
        int mx[MAXN];
        long long ret = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) mx[j] = -INF;
            for (int j = i; j < N; j++) {
                if (j-i+1 > B)  break;
                for (int k = 0; k < M; k++) {
                    int prev = -INF;
                    for (int l = k; l < M; l++) {
                        if (l-k+1 > B)  break;
                        mx[l] = max(mx[l], g[j][l]);
                        prev = max(prev, mx[l]);
                        int w = j - i + 1, h = l - k + 1;
                        if (w > h)  swap(w, h);
                        if (w <= A && h <= B) {
                            long long V = getHeight(w, h, prev) * w * h;
                            ret = max(ret, V);
//                            printf("[%d %d] [%d %d]\n", i, k, j, l);
//                            printf("%d %d %d H %lld %lld\n", w, h, prev, getHeight(w, h, prev), V);
                        }
                    }
                }
            }
        }
        printf("%lld\n", ret);
    }
    return 0;
}