#include <stdio.h>
#include <string.h>

int main() {
    int t, n, m, x, y, i, j;
    scanf("%d", &t);
    char ch[2][100];
    while(t--) {
        scanf("%d %d", &n, &m);
        memset(ch, 0, sizeof(ch));
        scanf("%d", &x);
        x = x%m;
        if(x < 0)   x += m;
        ch[0][x] = 1;
        char flag;
        for(i = 1, flag = 0; i < n; i++, flag ^= 1) {
            scanf("%d", &x);
            x = x%m;
            if(x < 0)   x += m;
            for(j = 0; j < m; j++) {
                if(ch[flag][j]) {
                    y = j+x;
                    if(y >= m)  y -= m;
                    ch[flag^1][y] = 1;
                    y = j-x;
                    if(y < 0)  y += m;
                    ch[flag^1][y] = 1;
                }
            }
            memset(ch[flag], 0, sizeof(ch[flag]));
        }
        int ans = ch[flag][0];
        puts(ans ? "Divisible" : "Not divisible");
    }
    return 0;
}
