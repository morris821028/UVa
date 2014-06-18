#include <stdio.h>
int p[10000] = {};
void sieve() {
    int i, j;
    for(i = 2; i < 10000; i++) {
        if(p[i] == 0) {
            for(j = i+i; j < 10000; j += i)
                p[j] = 1;
        }
    }
}
int main() {
    sieve();
    int a, b;
    scanf("%*d");
    while(scanf("%d %d", &a, &b) == 2) {
        int Q[9999], Qt, used[10000] = {};
        int step[10000] = {}, i, j, k, tn;
        char buf[10];
        Q[Qt = 0] = a, used[a] = 1;
        for(i = 0; i <= Qt && !used[b]; i++) {
            tn = Q[i];
            for(k = 0; k < 4; k++) {
                sprintf(buf, "%d", tn);
                for(j = '0'; j <= '9'; j++) {
                    buf[k] = j;
                    sscanf(buf, "%d", &a);
                    if(p[a] == 0 && used[a] == 0 && a >= 1000) {
                        used[a] = 1, step[a] = step[tn]+1;
                        Q[++Qt] = a;
                    }
                }
            }
        }
        if(used[b])
            printf("%d\n", step[b]);
        else
            puts("Impossible");
    }
    return 0;
}
