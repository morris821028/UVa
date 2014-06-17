#include <stdio.h>
int p[5500], pt = 0;
void sieve() {
    char mark[32767] = {};
    int i, j;
    for(i = 2; i < 32767; i++)
        if(!mark[i]) {
            p[pt++] = i;
            for(j = i+i; j < 32767; j += i)
                mark[j] = 1;
        }
}
int sol(int n) {
    static int a, b, i, cnt, t;
    a = 1, b = n, cnt = 1;
    for(i = 0; i < pt && p[i]*p[i] <= n; i++) {
        if(n%p[i] == 0) {
            a *= p[i]-1;
            b /= p[i];
            n /= p[i];
            t = 1;
            while(n%p[i] == 0)
                n /= p[i], t++;
            cnt *= t+1;
        }
    }
    if(n != 1)
        a *= n-1, b /= n, cnt *= 2;
    return a*b+cnt;
}
int main() {
    int n;
    sieve();
    while(scanf("%d", &n) == 1) {
        printf("%d\n", n-sol(n)+1);
    }
    return 0;
}
