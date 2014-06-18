#include <stdio.h>

int main() {
    int n;
    char s[10005];
    while(scanf("%d", &n) == 1) {
        scanf("%s", s);
        int W[10] = {}, Wtot = 0;
        long long ret = 0;
        int i, j;
        for(i = 0; i < 10; i++) {
            int tot = n*(n-1)/2 + n, cnt = 0;
            tot -= Wtot;
            for(j = 0; j <= n; j++) {
                if(s[j] > i+'0')
                    cnt++;
                else {
                    tot -= cnt*(cnt-1)/2 + cnt;
                    cnt = 0;
                }
            }
            ret += i * (tot%1000000007);
            ret %= 1000000007;
            W[i] = tot;
            Wtot += tot;
        }
        printf("%d\n", ret%1000000007);
    }
    return 0;
}
