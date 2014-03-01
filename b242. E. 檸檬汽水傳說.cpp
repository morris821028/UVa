#include <stdio.h>
const int N = 1000000;
int stk[N+1], cnt[N+1];
int main() {
    int cases, n, x;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        long long ans = 0, top = 0;
        stk[0] = -1u/2, cnt[0] = 1;
        while(n--) {
            scanf("%d", &x);
            while(stk[top] < x)
                ans += cnt[top], top--;
            if(stk[top] == x) {
                ans += cnt[top];
                cnt[top]++;
                if(top > 1) ans++;
            } else {
                if(top) ans++;
                stk[++top] = x, cnt[top] = 1;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
