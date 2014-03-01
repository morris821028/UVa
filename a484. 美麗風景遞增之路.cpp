#include <stdio.h>
#include <map>
using namespace std;
int g[1005][1005];
int main() {
    int t, R, C, i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &R, &C);
        map<int, int> dp[2][C];
        int flag = 0, A[2][1001] = {};
        memset(A, -1, sizeof(A));
        dp[0][C][-1] = 1;
        for(i = 0; i < R; i++) {
            for(j = 0; j < C; j++) {
                scanf("%d", &A[flag][j]);

            }
            flag = 1-flag;
        }
    }
    return 0;
}
