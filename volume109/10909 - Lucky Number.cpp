#include <stdio.h>
#include <algorithm>
using namespace std;
int st[(1<<22)+1];
int lucky[262144] = {1, 3};
int main() {
    int M;
    int n = 2000000;
    int i, j, k;
    for(M = 1; M < n+2; M <<= 1);
    for(i = 2*M-1; i > 0; i--) {
        if(i >= M)
            st[i] = (i-M)&1; // odd;
        else
            st[i] = st[i<<1] + st[i<<1|1];
    }
    int idx = 3;
    int pos, m, s;
    for(i = 1; idx <= 2000000; i++) {
        lucky[i] = idx;
        pos = 0;
        int cnt = 0;
        while(true) {
            pos += lucky[i], m = pos-cnt;
            //printf("m = %d\n", m);
            for(s = 1; s < M;) {
                if(st[s<<1] < m)
                    m -= st[s<<1], s = s<<1|1;
                else
                    s = s<<1;
            }
            if(s-M > 2000000)
                break;
            //printf("kill %d %d %d\n", pos, s-M, m);
            //getchar();
            cnt++;
            while(s)    st[s]--, s >>= 1;
        }
        idx++;
        while(st[idx+M] == 0)
            idx++;
    }
    m = i;
    while(scanf("%d", &n) == 1) {
        if(n&1) {
            printf("%d is not the sum of two luckies!\n", n);
            continue;
        }
        int pos = lower_bound(lucky, lucky+m, n/2)-lucky;
        for(i = pos; i >= 0; i--) {
            if(st[n-lucky[i]+M] && lucky[i] <= n-lucky[i]) {
                printf("%d is the sum of %d and %d.\n", n, lucky[i], n-lucky[i]);
                break;
            }
        }
        if(i < 0) {
            printf("%d is not the sum of two luckies!\n", n);
            continue;
        }
    }
    return 0;
}
