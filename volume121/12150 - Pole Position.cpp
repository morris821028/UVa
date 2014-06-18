#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        int rank[10005] = {}, err = 0;
        int x, v, i;
        for(i = 0; i < n; i++) {
            scanf("%d %d", &x, &v);
            if(i+v < 0)     err = 1;
            if(i+v >= n)    err = 1;
            if(!err && rank[i+v])   err = 1;
            if(err) continue;
            rank[i+v] = x;
        }
        if(err) {
            puts("-1");
            continue;
        }
        printf("%d", rank[0]);
        for(i = 1; i < n; i++)
            printf(" %d", rank[i]);
        puts("");
    }
    return 0;
}
