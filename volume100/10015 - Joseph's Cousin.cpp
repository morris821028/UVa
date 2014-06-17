#include <stdio.h>

int Pt = 1, P[5500];
int sieve() {
    char mark[50000] = {};
    int i, j;
    for(i = 2; i < 50000; i++) {
        if(!mark[i]) {
            P[Pt++] = i;
            for(j = 2*i; j < 50000; j += i)
                mark[j] = 1;
        }
    }
}
int main() {
    sieve();
    int n, i, j, st[8193];
    while(scanf("%d", &n) == 1 && n) {
        int M;
        for(M = 1; M < n+1; M <<= 1);
        for(i = 2*M-1; i > 0; i--) {
            if(i >= M)
                st[i] = 1;
            else
                st[i] = st[i<<1]+st[i<<1|1];
        }
        int m, last, prev = 0, s;
        for(i = 1; i <= n; i++) {
            m = (P[i]+prev)%(n-i+1);
            if(m == 0)
                m = n-i+1;
            prev = m-1;
            for(s = 1; s < M;) {
                if(st[s<<1] < m)
                    m -= st[s<<1], s = s<<1|1;
                else
                    s = s<<1;
            }
            last = s-M+1;
            while(s) {
                st[s] --;
                s >>= 1;
            }
        }
        printf("%d\n", last);
    }
    return 0;
}
