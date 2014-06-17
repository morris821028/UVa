#include <stdio.h>

int main() {
    int N, D, i, j, n;
    while(scanf("%d %d", &N, &D) == 2) {
        if(N == 0 && D == 0)    break;
        int cnt[105] = {};
        long long res;
        for(i = 2; i <= N; i++) {
            n = i;
            for(j = 2; j <= n; j++)
                while(n%j == 0) {
                    n /= j, cnt[j]++;
                }
        }
        int zero = 0;
        for(i = 2; i < 100 && !zero; i++) {
            while(D%i == 0) {
                if(cnt[i] == 0) {
                    zero = 1;
                    break;
                }
                cnt[i]--;
                D /= i;
            }
        }
        if(D != 1 && (D > 100 || cnt[D] == 0))
            zero = 1;
        else if(D != 1)
            cnt[D]--;
        if(zero) {
            puts("0");
            continue;
        }
        res = 1;
        for(i = 0; i <= N; i++) {
            res *= cnt[i]+1;
        }
        printf("%lld\n", res);
    }
    return 0;
}
