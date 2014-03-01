#include <stdio.h>
int Prime[5200], Pt;
int ans[10001] = {};
void sieve() {
    char mark[10000] = {};
    Pt = 0;
    int i, j;
    for(i = 2; i < 10000; i++) {
        if(mark[i] == 0) {
            Prime[Pt++] = i;
            for(j = 2; i*j < 10000; j++)
                mark[i*j] = 1;
        }
    }
    for(i = 0; i < Pt; i++) {
        int tmp = 0;
        for(j = i; j < Pt; j++) {
            tmp += Prime[j];
            if(tmp > 10000) break;
            ans[tmp]++;
        }
    }
}
int main() {
    sieve();
    int n;
    while(scanf("%d", &n) == 1 && n) {
        printf("%d\n", ans[n]);
    }
    return 0;
}
