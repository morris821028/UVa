#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int k, n;
    int A[30][10];
    while(scanf("%d %d", &k, &n) == 2) {
        int i, j, l;
        int map[30][30] = {}, bmap[30][30] = {};
        for(i = 0; i < k; i++) {
            for(j = 0; j < n; j++)
                scanf("%d", &A[i][j]);
            sort(A[i], A[i]+n);
        }
        int indeg[30] = {};
        for(i = 0; i < k; i++) {
            for(j = 0; j < k; j++) {
                for(l = 0; l < n; l++) {
                    if(A[i][l] >= A[j][l])
                        break;
                }
                if(l == n) {
                    map[i][j] = 1, indeg[j]++, bmap[j][i] = 1;
                } else
                    map[i][j] = 0, bmap[j][i] = 0;
            }
        }
        int dp[30] = {}, sour[30] = {}, used[30] = {};
        while(1) {
            for(i = 0; i < k; i++) {
                if(indeg[i] == 0 && used[i] == 0) {
                    int mm = -1, mi = -1;
                    for(j = 0; j < k; j++) {
                        if(bmap[i][j] == 1) {
                            if(dp[j] > mm)
                                mm = dp[j], mi = j;
                        }
                    }
                    mm++;
                    used[i] = 1, dp[i] = mm;
                    sour[i] = mi;
                    for(j = 0; j < k; j++) {
                        if(map[i][j] == 1 && used[j] == 0)
                            indeg[j]--;
                    }
                    break;
                }
            }
            if(i == k)  break;
        }
        int mm = -1, mi = -1;
        for(i = 0; i < k; i++)
            if(dp[i] > mm)
                mm = dp[i], mi = i;
        printf("%d\n", mm+1);
        int ans[30], at = -1;
        do {
            ans[++at] = mi;
            if(dp[mi] == 0) break;
            mi = sour[mi];
        } while(1);
        for(i = at; i >= 0; i--)
            printf("%s%d", i != at ? " " : "", ans[i]+1);
        puts("");
    }
    return 0;
}
