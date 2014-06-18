#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int A[200050], dp[200050];
int main() {
    int n;
    int i, j, k;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++) {
            scanf("%d", &A[i]);
        }
        memset(dp, 63, sizeof(dp));
        for(i = 0; i < 5; i++)
            dp[i] = 1;
        for(i = 0; i < n; i++) {
            for(j = 1; j <= A[i]; j++)
                dp[i+j] = min(dp[i+j], dp[i]+1);
        }
        printf("%d\n", dp[n]-1);
    }
    return 0;
}
/*
4
4 4 4 4
5
5 4 3 2 1
6
1 1 1 1 1 1
8
4 4 4 4 1 1 1 1
10
10 8 6 4 2 5 4 3 2 1
20
5 5 5 2 2 5 5 5 2 2 5 5 5 2 2 3 3 3 1 1
*/
