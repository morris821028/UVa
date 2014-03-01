#include <stdio.h>
#include <stdlib.h>
#define min(x,y) ((x)<(y)?(x):(y))
typedef struct {
    int x, y;
} Pt;
int cmp(const void *i, const void *j) {
    Pt *x, *y;
    x = (Pt *)i, y = (Pt *)j;
    if(x->x != y->x)
        return x->x - y->x;
    return x->y - y->y;
}
int main() {
    int n, m, cases = 0, i, j, k;
    int x, y;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n < 0 && m < 0)  break;
        int idx = 0, used[105] = {}, ut = -1;
        int cnt[105] = {}, hd[105], map[105][105];
        Pt A[10005];
        int dp[10005][2] = {};
        while(scanf("%d %d", &A[idx].x, &A[idx].y) == 2) {
            if(!A[idx].x && !A[idx].y)    break;
            used[A[idx].x] = 1;
            cnt[A[idx].x]++;
            idx++;
        }
        for(i = 1; i <= n; i++) {
            if(used[i] == 1) {
                used[++ut] = i;
            }
            hd[i] = 0xffff;
        }
        qsort(A, idx, sizeof(Pt), cmp);
        for(i = 0; i < idx; i++)
            hd[A[i].x] = min(hd[A[i].x], i);
        int top = -1;
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= m; j++) {
                if(top+1 < idx && i == A[top+1].x && j == A[top+1].y)
                    top++;
                map[i][j] = top;
            }
        }
        int st, ed, sk, k2;
        for(st = 0; st <= ut; st++) {
            i = used[st];
            for(k = hd[i], sk = 0; sk < cnt[i]; k++, sk++) {
                for(ed = st; ed >= 0; ed--) {
                    j = used[ed];
                    for(k2 = map[j][A[k].y]; k2 >= hd[j]; k2--) {
                        if(A[k].x == A[k2].x && A[k].y == A[k2].y)
                            continue;
                        if(dp[k][0] < dp[k2][0]+1)
                            dp[k][0] = dp[k2][0]+1, dp[k][1] = 0;
                        if(dp[k][0] == dp[k2][0]+1)
                            dp[k][1] += dp[k2][1];
                        break;
                        /*printf("%d %d - %d %d\n", A[k].x, A[k].y, A[k2].x, A[k2].y);*/
                    }
                }
                if(dp[k][0] == 0)   dp[k][0] = 1, dp[k][1] = 1;
            }
        }
        int ans = 0, way = 0;
        for(i = 0; i < idx; i++) {
            /*printf("%d %d - %d %d\n", A[i].x, A[i].y, dp[i][0], dp[i][1]);*/
            if(dp[i][0] > ans)
                ans = dp[i][0], way = 0;
            if(dp[i][0] == ans)
                way += dp[i][1];
        }
        printf("CASE#%d: %d %d\n", ++cases, ans, way);
    }
    return 0;
}
