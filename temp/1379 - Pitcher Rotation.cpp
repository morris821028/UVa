#include <stdio.h>
#include <stack>
#include <algorithm>
#include <string.h>
#include <functional>
#define MAXN 1024
using namespace std;

pair<int, int> pitcher[128][128];
int days[256];
int dp[2][6][6][6][6];

int main() {
    int testcase;
    int n, m, g;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d %d", &n, &m, &g), g += 10;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%d", &pitcher[i][j].first);
                pitcher[i][j].second = j;
            }
            sort(pitcher[i]+1, pitcher[i]+1+n, greater< pair<int, int> >());
        }
        days[0] = 0;
        for (int i = 1; i <= g; i++)
            scanf("%d", &days[i]);
        memset(dp, 0, sizeof(dp));
        
        int flag = 0, ret = 0;
        for (int i = 1; i <= g; i++) {
            int p = flag, q = !flag;
            memset(dp[q], 0, sizeof(dp[q]));
            flag = !flag;
            if (days[i] == 0) {
                for (int a = 0; a <= 0; a++) {
                    for (int b = 0; b <= 5; b++) {
                        for (int c = 0; c <= 5; c++) {
                            for (int d = 0; d <= 5; d++) {
                                for (int e = 0; e <= 5; e++) {
                                    dp[q][a][b][c][d] = max(dp[q][a][b][c][d], dp[p][b][c][d][e]);
                                    ret = max(ret, dp[q][a][b][c][d]);
                                }
                            }
                        }
                    }
                }
            } else {
                int op = days[i];
                for (int a = 1; a <= 5; a++) {
                    for (int b = 0; b <= 5; b++) {
                        if (i > 1 && pitcher[days[i-1]][b].second == pitcher[op][a].second)
                            continue;
                        for (int c = 0; c <= 5; c++) {
                            if (i > 2 && pitcher[days[i-2]][c].second == pitcher[op][a].second)
                                continue;
                            for (int d = 0; d <= 5; d++) {
                                if (i > 3 && pitcher[days[i-3]][d].second == pitcher[op][a].second)
                                    continue;
                                for (int e = 0; e <= 5; e++) {
                                    if (i > 4 && pitcher[days[i-4]][e].second == pitcher[op][a].second)
                                        continue;
                                    dp[q][a][b][c][d] = max(dp[q][a][b][c][d], dp[p][b][c][d][e] +  pitcher[op][a].first);
                                    ret = max(ret, dp[q][a][b][c][d]);
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("%.2lf\n", ret/100.0);
    }
    return 0;
}
/*
 1
 5 3 6
 91 90 50 50 50
 65 40 60 60 60
 66 40 60 60 60
 1
 2
 3
 3
 2
 1
 0
 0
 0
 0
 0
 0 
 0 
 0 
 0 
 0
*/
