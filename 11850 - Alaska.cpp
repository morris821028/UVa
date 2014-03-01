#include <stdio.h>

int main() {
    int n, x, i, j;
    while(scanf("%d", &n) == 1 && n) {
        int mile[2000] = {}, sta[1500] = {};
        for(i = 0; i < n; i++) {
            scanf("%d", &x);
            sta[x] = 1;
        }
        int last = 0;
        for(i = 0; i <= 1422; i++) {
            if(sta[i]) {
                for(j = 0; j <= 200; j++)
                    mile[i+j] = 1;
                last = i;
            }
        }
        for(i = 0; i <= 1422; i++)
            if(!mile[i])    break;
        if(i != 1423 || (1422-last)*2 > 200)
            puts("IMPOSSIBLE");
        else
            puts("POSSIBLE");
    }
    return 0;
}
