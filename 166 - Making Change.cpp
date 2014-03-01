#include <stdio.h>

int main() {
    int get_dp[2001] = {};
    int i, j, k, coin[6] = {5,10,20,50,100,200};
    get_dp[0] = 0;
    for(i = 1; i <= 2000; i++) {
        int mi = 0xffff;
        for(j = 0; j < 6; j++) {
            for(k = 1; ; k++) {
                if(i-coin[j]*k < 0)   break;
                if(get_dp[i-coin[j]*k]+k < mi)
                    mi = get_dp[i-coin[j]*k]+k;
            }
        }
        get_dp[i] = mi;
    }
    while(1) {
        int A[6], sum = 0, a, b;
        for(i = 0; i < 6; i++)
            scanf("%d", A+i), sum += A[i]*coin[i];
        if(!sum)    break;
        scanf("%d.%d", &a, &b);
        a = 100*a + b;
        int pay_dp[sum+1];
        for(i = 0; i <= sum; i++)
            pay_dp[i] = 0xffff;
        pay_dp[0] = 0;
        for(i = 0; i < 6; i++) {
            for(k = sum; k >= 0; k--) {
                for(j = 1; j <= A[i]; j++) {
                    if(k-coin[i]*j < 0) break;
                    if(pay_dp[k] > pay_dp[k-coin[i]*j]+j)
                        pay_dp[k] = pay_dp[k-coin[i]*j]+j;
                }
            }
        }
        int ans = 0xffff;
        for(i = a; i <= sum; i++) {
            if(ans <= pay_dp[i])    continue;
            if(ans > pay_dp[i]+get_dp[i-a])
                ans = pay_dp[i]+get_dp[i-a];
        }
        printf("%3d\n", ans);
    }
    return 0;
}
