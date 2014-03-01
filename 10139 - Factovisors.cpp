#include <stdio.h>
int p[5500], pt = 0;
void sieve() {
    int i, j, m[50000] = {};
    for(i = 2; i < 50000; i++)
        if(m[i] == 0) {
            p[pt++] = i;
            for(j = i+i; j < 50000; j += i)
                m[j] = 1;
        }
}
int solve(int n, int m) {
    int i;
    for(i = 0; i < pt && p[i]*p[i] <= m; i++) {
        if(m%p[i] == 0) {
            int cnt = 0;
            while(m%p[i] == 0)
                cnt++, m /= p[i];
            long long tmp = p[i], cnt2 = 0;
            while(tmp <= n) {
                cnt2 += n/tmp;
                tmp *= p[i];
            }
            if(cnt2 < cnt)  return 0;
        }
    }
    if(m != 1) {
        if(n < m)   return 0;
    }
    return 1;
}
int main() {
    sieve();
    int n, m;
    while(scanf("%d %d", &n, &m) == 2) {
        if(solve(n, m))
            printf("%d divides %d!\n", m, n);
        else
            printf("%d does not divide %d!\n", m, n);
    }
    return 0;
}
