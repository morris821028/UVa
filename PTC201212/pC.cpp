#include <stdio.h>
#include <string.h>
int g[105][105];
long long dp[105][105], arg[105][105];
long long dp2[105][105];
int run[105][105], used[105][105];
char ans[1024];
void back(int i, int j) {
    if(i == 0 && j == 0 || used[i][j])
        return;
    used[i][j] = 1;
    if(arg[i][j] == 1)
        back(i-1, j), run[i-1][j] |= 1; // down
    else if(arg[i][j] == 2)
        back(i, j-1), run[i][j-1] |= 2; // right
    else {
        back(i-1, j), run[i-1][j] |= 1;
        back(i, j-1), run[i][j-1] |= 2;
    }
}
int n, m, i, j;
void print(int i, int j) {
    if(i == n-1 && j == m-1)
        return;
    if(run[i][j]&2) {
        printf("0");
        print(i, j+1);
    } else {
        printf("1");
        print(i+1, j);
    }
}
int main() {
    int first = 0;
    while(scanf("%d %d", &n, &m) == 2) {
        first++;
        //if(first > 10)  break;
        if(n > 100 || m > 100 || n < 0 || m < 0)
            while(1);
        //if(n < 10 || m < 10)    while(1);
        if(n == 0 && m == 0)
            break;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(scanf("%d", &g[i][j]) != 1)
                    return 0;
                if(g[i][j] > 100 || g[i][j] < 0) {
                    while(1);
                }
                used[i][j] = 0;
            }
        }
        g[0][0] = 0, g[n-1][m-1] = 0;
        memset(run, 0, sizeof(run));
        memset(dp2, 0, sizeof(dp2));
        int tot = n+m-2;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                dp[i][j] = g[i][j];
                int t1 = -1000, t2 = -1000;
                if(i-1 >= 0) // 1
                    t1 = dp[i-1][j];
                if(j-1 >= 0) // 2
                    t2 = dp[i][j-1];
                if(t1 > t2 && t1 != -1000)
                    dp[i][j] += t1, dp2[i][j] = dp2[i-1][j]+g[i][j]*(tot-i-j), arg[i][j] = 1;
                else if(t1 < t2 && t2 != -1000)
                    dp[i][j] += t2, dp2[i][j] = dp2[i][j-1]+g[i][j]*(tot-i-j), arg[i][j] = 2;
                else {
                    if(t1 != -1000 && t2 != -1000) {
                        dp[i][j] += t2;
                        if(dp2[i-1][j] < dp2[i][j-1])
                            dp2[i][j] = dp2[i-1][j]+g[i][j]*(tot-i-j), arg[i][j] = 1;
                        else if(dp2[i-1][j] > dp2[i][j-1])
                            dp2[i][j] = dp2[i][j-1]+g[i][j]*(tot-i-j), arg[i][j] = 2;
                        else
                            dp2[i][j] = dp2[i][j-1]+g[i][j]*(tot-i-j), arg[i][j] = 3;
                    }
                }
            }
        }
        back(n-1, m-1);
        printf("%lld %lld ", dp[n-1][m-1], dp2[n-1][m-1]);
        print(0,0);
        puts("");
    }
    /*if(scanf("%d", &n) == 1)
        while(1);*/
    return 0;
}
/*
2 5
0 2 0 3 5
6 3 4 2 0
5 5
0 0 0 5 0
0 0 0 0 2
0 0 0 0 0
2 0 0 0 0
0 5 0 0 0
5 5
0 0 0 2 0
0 0 0 0 5
0 0 0 0 0
2 0 0 0 0
0 5 0 0 0
6 8
0 3 0 5 0 5 3 2
3 2 5 1 3 4 1 6
1 6 1 0 4 2 4 1
0 2 2 3 3 0 3 5
2 1 0 3 5 1 5 2
5 0 5 4 1 5 1 0
0 0
*/
