#include <stdio.h>
#include <string.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
int main() {
    int n, m, t = 0;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        char name[30][30];
        int map[30][30], x, y, v;
        int i, j, k;
        memset(map, 63, sizeof(map));
        for(i = 0; i < n; i++)
            scanf("%s", name[i]);
        while(m--) {
            scanf("%d %d %d", &x, &y, &v);
            x--, y--;
            map[x][y] = min(v, map[x][y]);
            map[y][x] = min(v, map[y][x]);
        }
        for(k = 0; k < n; k++)
            for(i = 0; i < n; i++)
                for(j = 0; j < n; j++)
                    map[i][j] = min(map[i][j], map[i][k]+map[k][j]);
        int ans = 0xfffffff, idx = 0, tmp;
        for(i = 0; i < n; i++) {
            tmp = 0;
            for(j = 0; j < n; j++)
                if(i != j)
                    tmp += map[i][j];
            if(tmp < ans)
                ans =  tmp, idx = i;
        }
        printf("Case #%d : %s\n", ++t, name[idx]);
    }
    return 0;
}
