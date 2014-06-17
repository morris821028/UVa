#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define oo 32767
#define min(x, y) ((x) < (y) ? (x) : (y))

int g[20][20], dp[1<<18][18], t2[1<<18];
void tsp(int state, int last) {
    if(dp[state][last] != oo)   return;
    int i, j, tmp;
    dp[state][last]--;
    for(i = state; i; i -= j) {
        j = i&(-i);
        tsp(state-j, t2[j]);
        tmp = dp[state-j][t2[j]]+g[t2[j]][last];
        dp[state][last] = min(dp[state][last], tmp);
    }
}
int main() {
    int n, m, i, j, k, x[20], y[20];
    char s[30];
    for(i = 0; i < 18; i++) t2[1<<i] = i;
    while(scanf("%d %d", &n, &m) == 2) {
        int nut = 1;
        for(i = 0; i < n; i++) {
            scanf("%s", s);
            for(j = 0; s[j]; j++) {
                if(s[j] == '#')
                    x[nut] = i, y[nut++] = j;
                if(s[j] == 'L')
                    x[0] = i, y[0] = j;
            }
        }
        for(i = 0; i < nut; i++) {
            for(j = 0; j < nut; j++) {
                for(k = 0; ; k++)
                    if(x[i]+k >= x[j] && x[i]-k <= x[j] &&
                       y[i]+k >= y[j] && y[i]-k <= y[j]) {
                        g[i][j] = k;
                        break;
                    }
            }
        }
        for(i = 1<<nut; i >= 0; i--)
            for(j = 0; j < nut; j++)
                dp[i][j] = oo;
        dp[0][0] = 0;
        tsp((1<<nut)-1, 0);
        printf("%d\n", dp[(1<<nut)-1][0]);
    }
    return 0;
}
