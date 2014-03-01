#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <set>
#include <string.h>
using namespace std;
int A[105], B[105], Ax[105], Bx[105], used[105];
int t, d, n, i, j, ans;
int FA[105], FB[105];
int appA[105] = {}, appB[105] = {};
int gteam[10000][105], gt[105];
int dfs(int idx, int len) {
    int i, j;
    if(len >= 2) {
        int dd = 0xffff;
        for(i = 0; i < ans; i++) {
            int cnt = 0, app[105] = {};
            for(j = 0; j < gt[i]; j++)
                app[gteam[i][j]] = 1;
            for(j = 0; j < len; j++) {
                if(app[used[j]])
                    cnt++;
            }
            if(cnt == len)
                break;
            if(cnt == gt[i]) {
                for(j = 0; j < len; j++)
                    gteam[i][j] = used[j];
                gt[i] = len;
                break;
            }
        }
        if(i == ans) {
            for(i = 0; i < len; i++)
                gteam[ans][i] = used[i];
            gt[ans] = len;
            ans++;
        }
    }
    for(i = idx; i <= 100; i++) {
        if(appA[i] && appB[i]) {
            used[len] = i;
            dfs(i+1, len+1);
        }
    }
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &d, &n);

        memset(appA, 0, sizeof(appA));
        memset(appB, 0, sizeof(appB));
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]), appA[A[i]] = 1;
        for(i = 0; i < n; i++)
            scanf("%d", &Ax[i]), FA[A[i]] = Ax[i];
        for(i = 0; i < n; i++)
            scanf("%d", &B[i]), appB[B[i]] = 1;
        for(i = 0; i < n; i++)
            scanf("%d", &Bx[i]), FB[B[i]] = Bx[i];
        ans = 0;
        dfs(0, 0);
        printf("%d\n", ans);
    }
    return 0;
}/*
2
2
4
2 2 2 2
1 2 3 4
1 2 3 4
1 4 5 9
3
5
1 2 3 4 5
1 2 5 7 8
5 4 1 3 2
1 3 7 8 9
*/
