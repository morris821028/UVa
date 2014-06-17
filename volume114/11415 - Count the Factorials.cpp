#include <stdio.h>
int count[3000000] = {1,1,1};
short num[3000000] = {};
int prime[5500], pt = 0;
void sieve() {
    int i, j, mark[5000] = {};
    for(i = 2; i < 2000; i++) {
        if(!mark[i]) {
            prime[pt++] = i;
            for(j = i+i; j < 2000; j += i)
                mark[j] = 1;
        }
    }
}
void build() {
    int i, j, tn;
    num[2] = 1;
    for(i = 3; i < 3000000; i++) {
        count[i] = count[i-1];
        tn = i;
        for(j = 0; prime[j]*prime[j] <= tn && j < pt; j++) {
            if(tn%prime[j] == 0) {
                tn /= prime[j];
                num[i] = num[tn]+1;
                break;
            }
        }
        if(tn == i) num[i] = 1;
        count[i] += num[i];
    }
}
int main() {
    sieve();
    build();
    int t, n, l, r, m;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        l = 0, r = 2999999;
        while(l <= r) {
            m = (l+r)>>1;
            if(count[m] <= n)
                l = m+1;
            else
                r = m-1;
        }
        printf("%d\n", l);
    }
    return 0;
}
