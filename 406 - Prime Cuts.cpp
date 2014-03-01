#include <stdio.h>

int main() {
    int n, c, i, j, p[1001] = {1}, pt = 1;
    for(i = 2; i < 1001; i++) {
        int flag = 0;
        for(j = 2; j*j <= i; j++) {
            if(i%j == 0) {
                flag = 1;
                break;
            }
        }
        if(!flag)
            p[pt++] = i;
    }
    while(scanf("%d %d", &n, &c) == 2) {
        printf("%d %d:", n, c);
        int list[1001], lt = 0;
        for(i = 0; i < pt; i++) {
            if(p[i] <= n)
                list[lt++] = p[i];
            else
                break;
        }
        if(lt&1)    c = c*2-1;
        else        c = c*2;
        if(c > lt)  c = lt;
        for(i = lt/2-c/2, j = 0; j < c; j++, i++)
            printf(" %d", list[i]);
        puts("\n");
    }
    return 0;
}
