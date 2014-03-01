#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define oo 0xfffffff
int grid[5][5], ch[5], ans[5];
int minv;
void dfs(int idx, int i) {
    if(idx == 5) {
        int sum = 0, tmp;
        int i, j, k, x, y;
        for(i = 0; i < 5; i++) {
            for(j = 0; j < 5; j++) {
                if(grid[i][j]) {
                    tmp = oo;
                    for(k = 0; k < 5; k++) {
                        x = ch[k]/5, y = ch[k]%5;
                        if(abs(x-i)+abs(y-j) < tmp)
                            tmp = abs(x-i)+abs(y-j);
                    }
                    sum += grid[i][j]*tmp;
                }
            }
        }
        if(sum < minv) {
            minv = sum;
            for(i = 0; i < 5; i++)
                ans[i] = ch[i];
        }
        return;
    }
    for(; i < 25; i++) {
        ch[idx] = i;
        dfs(idx+1, i+1);
    }
}
int main() {
    int t, n, i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        memset(grid, 0, sizeof(grid));
        while(n--) {
            scanf("%d %d %d", &i, &j, &k);
            grid[i][j] += k;
        }
        minv = oo;
        dfs(0, 0);
        for(i = 0; i < 5; i++) {
            if(i)
                putchar(' ');
            printf("%d", ans[i]);
        }
        puts("");
    }
    return 0;
}
