#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, x, k, i;
    int test = 0;
    while(scanf("%d", &n) == 1) {
        scanf("%d", &x);
        int p[51], pt = n;
        for(i = 0; i <= n; i++)
            p[i] = 1;
        for(i = 0; i < 20; i++) {
            scanf("%d", &k);
            if(pt == x)
                continue;
            int j, cnt = 0;
            for(j = 1; j <= n; j++) {
                cnt += p[j];
                if(cnt == k) {
                    if(pt == x)
                        break;
                    p[j] = 0, cnt = 0, pt--;
                }
            }
        }
        printf("Selection #%d\n", ++test);
        int flag = 0;
        for(i = 1; i <= n; i++) {
            if(p[i]) {
                if(flag)
                    putchar(' ');
                printf("%d", i);
                flag = 1;
            }
        }
        puts("\n");
    }
    return 0;
}
