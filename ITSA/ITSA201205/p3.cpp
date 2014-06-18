#include <stdio.h>
#include <queue>
using namespace std;
int i, j, map[10][10], deg[10];
int ans = 0xfffff, way[10], tmp[10], len, used[10];
void dfs(int now, int sum, int l) {
    int i;
    if(sum >= ans)
        return;
    if(now == 9) {
        if(sum < ans) {
            ans = sum;
            len = l;
            for(i = 0; i < l; i++)
                way[i] = tmp[i];
        }
        return ;
    }
    for(i = 0; i < 10; i++) {
        if(map[now][i] != 0 && used[i] == 0) {
            used[i] = 1;
            tmp[l] = i;
            dfs(i, sum+deg[i], l+1);
            used[i] = 0;
        }
    }
}
int main() {
    while(scanf("%d", &map[0][0]) == 1) {
        for(i = 0; i < 10; i++) {
            deg[i] = 0;
            for(j = 0; j < 10; j++) {
                if(i == 0 && j == 0)
                    continue;
                scanf("%d", &map[i][j]);
                if(map[i][j] != 0)
                    deg[i]++;
            }
            used[i] = 0;
        }
        ans = 0xffff;
        tmp[0] = 0;
        dfs(0, deg[0], 1);
        for(i = 0; i < len; i++)
            printf("%d", way[i]);
        printf(" %d\n", ans);
    }
    return 0;
}
