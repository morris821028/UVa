#include <stdio.h>
#define maxL (1000000>>5)+1
int p[80000], pt = 0;
int mark[maxL];
int GET(int x) {
    return mark[x>>5]>>(x&31)&1;
}
void SET(int x) {
    mark[x>>5] |= 1<<(x&31);
}
void sieve() {
    int i, j, k;
    int n = 1000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            p[pt++] = i;
        }
    }
}
int main() {
    sieve();
    int n, i;
    while(scanf("%d", &n) == 1 && n) {
        printf("%d:\n", n);
        int hn = n/2, flag = 0;
        for(i = 0; i < pt; i++) {
            if(p[i] > hn)
                break;
            if(!GET(n-p[i])) {
                printf("%d+%d\n", p[i], n-p[i]);
                flag = 1;
                break;
            }
        }
        if(!flag)
            puts("NO WAY!");
    }
    return 0;
}
