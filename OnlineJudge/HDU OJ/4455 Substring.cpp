#include <stdio.h>
int mark[1000005] = {}, A[1000000] = {};
int main() {
    int n, i;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        int q, w;
        scanf("%d", &q);
        while(q--) {
            scanf("%d", &w);
            int cnt = 0;
            long long ans = 0;
            for(i = 0; i < w; i++) {
                if(mark[A[i]] == 0)
                    cnt++;
                mark[A[i]]++;
            }
            ans += cnt;
            w--;
            for(i = 1; i+w < n; i++) {
                mark[A[i-1]]--;
                if(mark[A[i-1]] == 0)
                    cnt--;
                if(mark[A[i+w]] == 0)
                    cnt++;
                mark[A[i+w]]++;
                ans += cnt;
            }
            for(i--; i < n; i++)
                mark[A[i]]--;
            printf("%lld\n", ans);
        }
    }
    return 0;
}
