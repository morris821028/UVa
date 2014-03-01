#include <stdio.h>
int p[2000], pt = 0;
void sieve() {
    int m[11000] = {};
    int i, j;
    for(i = 2; i < 11000; i++) {
        if(m[i] == 0) {
            p[pt++] = i;
            for(j = 2; i*j < 11000; j++)
                m[i*j] = 1;
        }
    }
}
int main() {
    sieve();
    int n, i, t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int ans = 0, r = 0;
        for(i = 0; i < pt; i++) {
            if(p[i] <= n) {
                if(r < n%p[i]) {
                    r = n%p[i];
                    ans = p[i];
                }
            } else
                break;
        }
        printf("%d\n", ans);
    }
    return 0;
}
