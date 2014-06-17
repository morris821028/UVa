#include <stdio.h>

int main() {
    int w, h, n, x, y;
    int i, j;
    while(scanf("%d %d", &w, &h) == 2) {
        if(w == 0 && h == 0)
            break;
        int dp[101][101] = {}, cant[101][101] = {};
        scanf("%d", &n);
        while(n--) {
            scanf("%d %d", &x, &y);
            cant[x][y] = 1;
        }
        dp[0][0] = 1;
        for(i = 0; i <= w; i++) {
            for(j = 0; j <= h; j++) {
                if(i-1 >= 0 && !cant[i-1][j])
                    dp[i][j] += dp[i-1][j];
                if(j-1 >= 0 && !cant[i][j-1])
                    dp[i][j] += dp[i][j-1];
            }
        }
        if(dp[w][h] == 1)
            printf("There is one path from Little Red Riding Hood's house to her grandmother's house.");
        else if(dp[w][h] == 0)
            printf("There is no path.");
        else
            printf("There are %d paths from Little Red Riding Hood's house to her grandmother's house.", dp[w][h]);
        puts("");
    }
    return 0;
}
