#include <stdio.h>
int g[105][105];
int main() {
    int t, n, m;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        int ix, iy;
        int i, j;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                scanf("%d", &g[i][j]);
                if(!g[i][j])    ix = i, iy = j;
            }
        }
        int flag = 0, cnt = 0;
        while(1) {
            flag = 0;
            cnt = 0;
            while(iy-1 >= 0 && g[ix][iy-1] == g[ix][iy]+1)
                cnt++, iy--, flag = 1;
            if(cnt) printf("W%d", cnt);
            cnt = 0;
            while(iy+1 < m && g[ix][iy+1] == g[ix][iy]+1)
                cnt++, iy++, flag = 1;
            if(cnt) printf("E%d", cnt);
            cnt = 0;
            while(ix-1 >= 0 && g[ix-1][iy] == g[ix][iy]+1)
                cnt++, ix--, flag = 1;
            if(cnt) printf("N%d", cnt);
            cnt = 0;
            while(ix+1 < n && g[ix+1][iy] == g[ix][iy]+1)
                cnt++, ix++, flag = 1;
            if(cnt) printf("S%d", cnt);
            if(flag == 0)   break;
        }
        puts("");
    }
    return 0;
}
/*
2
3 6
-1 -1 -1 -1 -1 -1
-1  3  2 1 0 -1
-1 -1 -1 -1 -1 -1
4 5
-1 3 4 5 6
-1 2 -1 -1 -1
-1 1 -1 -1 -1
-1 0 -1 -1 -1
*/
