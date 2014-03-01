#include <stdio.h>

int main() {
    int t, n, i, j, k;
    int x, y;
    int dir[8][2] = {{1,0},{-1,0},{0,1},{0,-1},
                {1,1},{1,-1},{-1,1},{-1,-1}};
    char g[150][150], a[150][150];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%s", g[i]);
        for(i = 0; i < n; i++)
            scanf("%s", a[i]);
        char res[30][30], touch = 0;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(a[i][j] == '.')  res[i][j] = '.';
                else {
                    int cnt = 0;
                    for(k = 0; k < 8; k++) {
                        x = i+dir[k][0], y = j+dir[k][1];
                        if(x < 0 || y < 0 || x >= n || y >= n)
                            continue;
                        if(g[x][y] == '*')
                            cnt++;
                    }
                    res[i][j] = cnt+'0';
                    if(g[i][j] == '*')  touch = 1;
                }
            }
        }
        for(i = 0; i < n; i++, puts("")) {
            for(j = 0; j < n; j++) {
                if(touch && g[i][j] == '*') {
                    putchar('*');
                    continue;
                }
                putchar(res[i][j]);
            }
        }
        if(t)   puts("");
    }
    return 0;
}
