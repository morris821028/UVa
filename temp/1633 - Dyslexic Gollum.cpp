#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define MOD 1000000007
#define MAXN 1024
int dp[MAXN][MAXN]; // [length][prev]
int path[16], isValid[MAXN], isValid2[MAXN<<1];
void dfs(int idx, int K) {
    if (idx == K) {
        int ok = 0, num = 0;
        for (int i = 0, j = K-1; i < K; i++, j--) {
            ok |= path[i] != path[j];
            num = num * 2 + path[i];
        }
        if (ok) dp[K][num]++;
        isValid[num] = ok;
        
        path[K] = 0, ok = 0, num = 0;
        for (int i = 0, j = K; i <= K; i++, j--) {
            ok |= path[i] != path[j];
            num = num * 2 + path[i];
        }
        isValid2[num] = ok;
        path[K] = 1, ok = 0, num = 0;
        for (int i = 0, j = K; i <= K; i++, j--) {
            ok |= path[i] != path[j];
            num = num * 2 + path[i];
        }
        isValid2[num] = ok;
        return ;
    }
    path[idx] = 0;
    dfs(idx+1, K);
    path[idx] = 1;
    dfs(idx+1, K);
}
int main() {
    int testcase, N, K;
    scanf("%d", &testcase);;
    while (testcase--) {
        scanf("%d %d", &N, &K);
        
        for (int i = 0; i <= N; i++) {
            for (int j = 1<<K; j >= 0; j--) {
                dp[i][j] = 0;
            }
        }
        
        dfs(0, K);
        
        if (N < K) {
            printf("%d\n", 1<<N);
        } else {
            int ret = 0, mask = (1<<K)-1;
            for (int i = K; i < N; i++) {
                for (int j = (1<<K)-1; j >= 0; j--) {
                    if (dp[i][j] == 0 || !isValid[j])  continue;
                    int val = dp[i][j], x, y;
                    x = ((j<<1)&mask) | 0, y = (j<<1) | 0;
                    if (isValid[x] && isValid2[y])
                        dp[i+1][x] = (dp[i+1][x] + val)%MOD;
                    x = ((j<<1)&mask) | 1, y = (j<<1) | 1;
                    if (isValid[x] && isValid2[y])
                        dp[i+1][x] = (dp[i+1][x] + val)%MOD;
                }
            }
            for (int i = (1<<K)-1; i >= 0; i--)
                ret = (ret + dp[N][i])%MOD;
            printf("%d\n", ret);
        }
    }
    return 0;
}
/*
 3
 2 2
 3 3
 3 4
*/