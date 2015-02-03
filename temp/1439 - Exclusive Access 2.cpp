#include <cstdio>
#include <cstring>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <set>
#include <map>
#include <queue>
using namespace std;
#define MAXN 128
#define MAXM 15
#define INF 0x3f3f3f3f
// minimum vertex coloring, O(3^n)
int main() {
    int N, M;
    char R1[MAXN][8], R2[MAXN][8];
    while (scanf("%d", &N) == 1 && N) {
        map<char, int> R;
        for (int i = 0; i < N; i++) {
            scanf("%s %s", R1[i], R2[i]);
            R[R1[i][0]] = R[R2[i][0]] = 1;
        }
        M = 0;
        for (map<char, int>::iterator it = R.begin(); it != R.end(); it++)
            it->second = M++;
        int maskg[MAXM] = {}, selfEdge[1<<MAXM];
        for (int i = 0; i < N; i++) {
            int x = R[R1[i][0]], y = R[R2[i][0]];
            maskg[x] |= 1<<y, maskg[y] |= 1<<x;
        }
        for (int i = 0; i < (1<<M); i++) {
            int ok = 1;
            for (int j = 0; j < M; j++) {
                if ((i>>j)&1) {
                    ok &= (i&maskg[j]) == 0;
                }
            }
            selfEdge[i] = ok;
        }
        int dp[1<<MAXM] = {}, from[1<<MAXM];
        dp[0] = 0;
        for (int i = 1; i < (1<<M); i++) {
            dp[i] = INF;
            for (int j = i; j; j = (j-1)&i) {
                if (selfEdge[j]) {
                    if (dp[i-j]+1 < dp[i]) {
                        dp[i] = dp[i-j]+1;
                        from[i] = i-j;
                    }
                }
            }
        }
        
        int color[MAXM] = {};
        for (int c = 1, i = (1<<M)-1; i; c++, i = from[i]) {
            int level = i^(from[i]);
//            printf("%d\n", level);
            for (int j = 0; j < M; j++) {
                if ((level>>j)&1)
                    color[j] = c;
            }
        }
        printf("%d\n", dp[(1<<M)-1] - 2);
        for (int i = 0; i < N; i++) {
            int x = color[R[R1[i][0]]], y = color[R[R2[i][0]]];
//            printf("%d %d\n", x, y);
            if (x > y) {
                printf("%s %s\n", R1[i], R2[i]);
            } else {
                printf("%s %s\n", R2[i], R1[i]);
            }
        }
    }
    return 0;
}
/*
*/