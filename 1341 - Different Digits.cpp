#include <stdio.h>

int main() {
    long long n, m, t;
    while(scanf("%lld", &n) == 1 && n) {
        printf("%lld:\n", n);
        char mark[10][65536] = {}, ud[10];
        int flag = 1, cnt = 0, i, j;
        long long t1[10];
        for(i = 1; i < 10; i++)
            t1[i] = i%n, ud[i] = 0;
        for(i = 0; flag && cnt < 9; i++) {
            for(j = 1; j < 10; j++) {
                if(t1[j] == 0) {
                    flag = 0;
                    for(; i >= 0; i--)
                        printf("%d", j);
                    puts("");
                    break;
                }
                t1[j] = (t1[j]*10+j)%n;
                if(mark[j][t1[j]] && ud[j] == 0)
                    ud[j] = 1, cnt++;
                mark[j][t1[j]] = 1;
            }
        }
        if(!flag)   continue;
        //puts("--");
        long long dig[5] = {};
        for(i = 0, m = n; ; i++, m += n) {
            char ap[10] = {}, cnt = 0;
            t = m;
            while(t && cnt <= 2) {
                if(ap[t%10] == 0)   cnt++;
                ap[t%10] = 1;
                t /= 10;
            }
            if(dig[cnt] == 0)
                dig[cnt] = m;
            if(cnt == 2)
                break;
        }
        printf("%lld\n", dig[2]);
    }
    return 0;
}
