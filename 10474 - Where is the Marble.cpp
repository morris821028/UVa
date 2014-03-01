#include <stdio.h>
int main() {
    int n, m, t = 0, x;
    while(scanf("%d %d", &n, &m) == 2) {
        if(!n && !m)
            break;
        int cnt[10001] = {}, sum[10001], l = 0, i;
        while(n--) {
            scanf("%d", &x);
            cnt[x]++;
            if(x > l)
                l = x;
        }
        sum[0] = 0;
        for(i = 1; i <= l; i++)
            sum[i] = sum[i-1]+cnt[i-1];
        printf("CASE# %d:\n", ++t);
        while(m--) {
            scanf("%d", &x);
            if(!cnt[x])
                printf("%d not found\n", x);
            else {
                printf("%d found at %d\n", x, sum[x]+1);
            }
        }
    }
    return 0;
}
