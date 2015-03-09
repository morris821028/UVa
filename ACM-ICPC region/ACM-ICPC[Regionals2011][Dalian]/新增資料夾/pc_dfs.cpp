#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int n, i;
int T[1000], X[1000], flag;
int used[1000];
int way[1000];
void dfs(int idx, int nowtime, int st, int limit) {
    if(flag)
        return ;
    printf("%d %d %d\n", idx, limit, nowtime);
    if(idx == n-1) {
        for(i = 1; i <= n; i++) {
            if(used[i] == 0) {
                if(nowtime+abs(X[way[idx-1]]-X[i]) < limit) {
                    way[idx] = i;
                    for(i = 0; i <= idx; i++)
                        printf("%d ", way[i]);
                    puts("");
                    flag = 1;
                }
                return;
            }
        }
    }
    if(st == 1) {
        for(i = 1; i <= n; i++) {
            if(used[i] == 0 && nowtime+abs(X[way[idx-1]]-X[i]) <= limit) {
                used[i] = 1;
                way[idx] = i;
                dfs(idx+1, nowtime+abs(X[way[idx-1]]-X[i]), 1, min(limit, nowtime+T[i]));
                used[i] = 0;
            }
        }
    } else {
        for(i = 1; i <= n; i++) {
            if(used[i] == 0) {
                used[i] = 1;
                way[idx] = i;
                dfs(idx+1, 0, 1, T[i]);
                used[i] = 0;
            }
        }
    }
}
int main() {
    while(scanf("%d", &n) == 1) {
        for(i = 1; i <= n; i++)
            scanf("%d", &T[i]), used[i] = 0;
        for(i = 1; i <= n; i++)
            scanf("%d", &X[i]);
        flag = 0;
        dfs(0,0,0,0);
        if(flag == 0)
            puts("Mission Impossible");
    }
    return 0;
}
