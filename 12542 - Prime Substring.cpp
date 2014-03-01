#include <stdio.h>
#include <string.h>
int mark[100005] = {};
void sieve() {
    int i, j;
    mark[1] = 1;
    mark[0] = 1;
    for(i = 2; i <= 100000; i++) {
        if(mark[i] == 0) {
            for(j = i+i; j <= 100000; j += i)
                mark[j] = 1;
        }
    }
}
int main() {
    sieve();
    char s[1024];
    while(scanf("%s", s) == 1) {
        if(s[0] == '0' && s[1] == '\0')
            break;
        int slen = strlen(s), tmp, n;
        int ans = 0, i, j;
        for(i = 0; i < slen; i++) {
            for(j = 1; j <= 9; j++) {
                tmp = s[i+j];
                s[i+j] = '\0';
                sscanf(s+i, "%d", &n);
                if(n < 100000) {
                    if(n > ans && mark[n] == 0)
                        ans = n;
                }
                s[i+j] = tmp;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
