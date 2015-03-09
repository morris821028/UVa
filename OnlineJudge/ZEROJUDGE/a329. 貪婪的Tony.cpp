#include <stdio.h>
int main() {
    int n, m, i, x;
    while(scanf("%d", &n) == 1) {
        int ans[100001] = {0,1};
        for(i = 1; i <= n; i++) {
            scanf("%d", &m);
            while(m--) {
                scanf("%d", &x);
                ans[x] += ans[i];
                if(ans[x] >= 1234567)
                    ans[x] -= 1234567;
            }
        }
        printf("%d\n", ans[n]);
    }
    return 0;
}
