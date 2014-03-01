#include <stdio.h>

int main() {
    int b[1001] = {0}, n, test = 0, i, j;
    while(scanf("%d", &n) == 1) {
        int flag = 0;
        for(i = 1; i <= n; i++) {
            scanf("%d", &b[i]);
            if(b[i] <= b[i-1]) {
                flag = 1;
            }
        }
        int mark[20001] = {};
        if(flag == 0)
        for(i = 1; i <= n; i++) {
            for(j = i; j <= n; j++) {
                if(mark[b[i]+b[j]] != 0)
                    flag = 1;
                mark[b[i]+b[j]] = 1;
            }
        }
        printf("Case #%d: It is ", ++test);
        if(!flag)
            puts("a B2-Sequence.");
        else
            puts("not a B2-Sequence.");
        puts("");
    }
    return 0;
}
