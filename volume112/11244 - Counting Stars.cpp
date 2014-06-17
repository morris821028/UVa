#include <stdio.h>

int main() {
    int n, m;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        char map[102][102];
        int i, j, a, b;
        for(i = 0; i < n; i++)
            scanf("%s", map[i]);
        int ans = 0, x, y;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(map[i][j] == '*') {
                    int flag = 0;
                    for(a = -1; a <= 1; a++) {
                        for(b = -1; b <= 1; b++) {
                            if(a == 0 && b == 0)
                                continue;
                            x = i+a, y = j+b;
                            if(x < 0 || y < 0 || x >= n || y >= m)
                                continue;
                            if(map[x][y] == '*')
                                flag = 1;
                        }
                    }
                    if(flag == 0)
                        ans++;
                }
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}
