#include <stdio.h>
#include <string.h>

int map[201][201], mt[201];
int used[201];
int mx[201], my[201];
int dfs(int nd) {
    int i, y;
    for(i = 0; i < mt[nd]; i++) {
        y = map[nd][i];
        if(!used[i]) {
            used[i] = 1;
            if(my[i] == 0 || dfs(my[i])) {
                mx[nd] = y, my[y] = nd;
                return 1;
            }
        }
    }
    return 0;
}
int main() {
    int n, m, i, j;
    while(scanf("%d %d", &n, &m) == 2) {
        memset(mt, 0, sizeof(mt));
        memset(mx, 0, sizeof(mx));
        memset(my, 0, sizeof(my));
        for(i = 10; i <= m; i++) {
            for(j = 10; j <= m; j++) {
                if(i%10 == j/10) {
                    map[i][mt[i]++] = j;
                    //printf("%d %d\n", i, j);
                }
            }
        }
        for(i = 10; i <= m; i++) {
            if(mx[i] == 0) {
                memset(used, 0, sizeof(used));
                dfs(i);
            }
        }
        int ap[201] = {};
        while(1) {
            int flag = 0;
            for(i = 10; i <= m; i++) {
                if(my[i] == 0 && mx[i] != 0 && ap[i] == 0) {
                    ap[i] = 1;
                    int nd = i, pr;
                    printf("%d", nd/10);
                    flag = 1;
                    while(nd) {
                        printf("%d", nd%10);
                        pr = nd, nd = mx[nd];
                        my[nd] = 0, mx[pr] = 0;
                        mx[nd] = 0, my[pr] = 0;
                        if(ap[nd])
                            break;
                        ap[nd] = 1;
                    }
                }
            }
            if(flag == 0)
                break;
        }
        puts("");
        for(i = 10; i <= m; i++) {
            if(ap[i] == 0) {
                ap[i] = 1;
                int nd = i;
                printf("%d", nd/10);
                while(nd) {
                    printf("%d", nd%10);
                    nd = mx[nd];
                    if(ap[nd])
                        break;
                    ap[nd] = 1;
                }
                puts("");
            }
        }
    }
    return 0;
}
/*
110120130140150212223242531323334354142434445
11012013014019494847394629452844383736273526251834241733231622150
*/
