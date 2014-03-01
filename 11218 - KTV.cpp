#include <stdio.h>
int main() {
    int n, a, b, c, s;
    int i, j, cases = 0;
    while(scanf("%d", &n), n) {
        int C[512] = {}, stk[512], stkIdx = 0;
        while(n--) {
            scanf("%d %d %d %d", &a, &b, &c, &s);
            a--, b--, c--;
            i = 1<<a|1<<b|1<<c;
            if(C[i] < s) {
                if(!C[i])  stk[stkIdx++] = i;
                C[i] = s;
            }
        }
        int ans = -1, tmp;
        for(i = 0; i < stkIdx; i++) {
            for(j = i+1; j < stkIdx; j++) {
                if((stk[i]&stk[j]) == 0) {
                    if(!C[511-stk[i]-stk[j]])
                        continue;
                    tmp = C[stk[i]]+C[stk[j]]+C[511^stk[i]^stk[j]];
                    if(tmp > ans)   ans = tmp;
                }
            }
        }
        printf("Case %d: %d\n", ++cases, ans);
    }
    return 0;
}
