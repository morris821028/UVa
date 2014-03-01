#include <stdio.h>
int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
long long dp1[90005], dp2[90005] = {};
int p[90005], son[90005];
int main() {
    int n, i;
    while(scanf("%d", &n) == 1) {
        for(i = 1; i < n; i++) {
            ReadInt(&p[i]);
            dp1[i] = son[i] = 0;
        }
        dp1[0] = dp2[0] = son[0] = 0;
        for(i = n-1; i > 0; i--) {
            son[i]++;
            dp1[p[i]] += dp1[i] + son[i];
            son[p[i]] += son[i];
        }
        for(i = 1; i < n; i++) {
            dp2[i] = (dp2[p[i]]+n-son[i]) + (dp1[p[i]]-dp1[i]-son[i]);
        }
        long long ans = dp1[0]+dp2[0];
        int lab = 0;
        for(i = 1; i < n; i++) {
            if(dp1[i]+dp2[i] < ans)
                ans = dp1[i]+dp2[i], lab = i;
        }
        printf("%d\n", lab);
    }
    return 0;
}
