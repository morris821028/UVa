#include <stdio.h>
#include <stdlib.h>
int map[8][8], x[8], y[8], used[8];
int ans;
int check(int a, int b, int idx) {
    int i;
    for(i = 0; i < idx; i++)
        if(abs(x[i]-a) == abs(y[i]-b))
            return 0;
    return 1;
}
void dfs(int idx, int sum) {
    if(idx == 8) {
        if(sum > ans)
            ans = sum;
        return;
    }
    int i;
    for(i = 0; i < 8; i++) {
        if(used[i] == 0 && check(idx, i, idx) != 0) {
            used[i] = 1;
            x[idx] = idx, y[idx] = i;
            dfs(idx+1, sum+map[idx][i]);
            used[i] = 0;
        }
    }
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        for(i = 0; i < 8; i++) {
            for(j = 0; j < 8; j++)
                scanf("%d", &map[i][j]);
            used[i] = 0;
        }
        ans = 0;
        dfs(0, 0);
        printf("%5d\n", ans);
    }
    return 0;
}
