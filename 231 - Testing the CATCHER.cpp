#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j, test = 0, A[1000];
    while(scanf("%d", &A[0]) == 1) {
        if(A[0] < 0)    break;
        n = 1;
        while(scanf("%d", &A[n]) == 1) {
            if(A[n] < 0)    break;
            else
                n++;
        }
        int DP[1000] = {};
        for(i = 0; i < n; i++) {
            for(j = i+1; j < n; j++) {
                if(A[j] < A[i] && DP[j] < DP[i]+1)
                    DP[j] = DP[i]+1;
            }
        }
        int ans = 0;
        for(i = 0; i < n; i++)
            ans = ans > DP[i] ? ans : DP[i];
        ans++;
        if(test)
            puts("");
        printf("Test #%d:\n", ++test);
        printf("  maximum possible interceptions: %d\n", ans);

    }
    return 0;
}
