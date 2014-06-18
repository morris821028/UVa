#include <stdio.h>
#include <string.h>
int main() {
    int testcase;
    int n, p, x;
    int i, j;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &n, &p);
        n = n/10;
        int dp[1000] = {};
        dp[0] = 1;
        for(i = 0; i < p; i++) {
            scanf("%d", &x), x /= 10;
            for(j = 999-x; j >= 0; j--) {
                if(dp[j])
                    dp[j+x] = 1;
            }
        }
        int ret = n;
        while(ret < 1000 && dp[ret] == 0)
            ret++;
        if(ret == 1000)
            puts("NO SOLUTION");
        else
            printf("%d\n", ret*10);
    }
    return 0;
}
