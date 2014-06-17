#include <stdio.h>

int main() {
    int n, i, j;
    int cases = 0;
    while(scanf("%d", &n) == 1) {
        int dp[1001] = {}, a[40];
        for(i = 0; i < n; i++)
            scanf("%d", a+i);
        dp[0] = 1;
        for(i = 0; i < n; i++) {
            for(j = 1000-a[i]; j >= 0; j--)
                if(dp[j])   dp[j+a[i]] += dp[j];
        }
        int flag = 0, l = 0;
        for(i = 0; i < n; i++) {
            if(a[i] < l)    flag = 1;
            l = a[i];
            if(dp[a[i]] != 1)   flag = 1;
        }
        printf("Case #%d:", ++cases);
        for(i = 0; i < n; i++)
            printf(" %d", a[i]);
        puts("");
        if(flag)
            puts("This is not an A-sequence.");
        else
            puts("This is an A-sequence.");
    }
    return 0;
}
