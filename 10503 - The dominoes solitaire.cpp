#include <stdio.h>
int x[50], y[50];
int used[50];
int n, m, flag;
void dfs(int idx, int l) {
    if(idx == n) {
        if(l == x[1])
            flag = 1;
        return;
    }
    int i;
    for(i = 2; i < m+2; i++) {
        if(used[i] == 0) {
            if(l == x[i]) {
                used[i] = 1;
                dfs(idx+1, y[i]);
                used[i] = 0;
            }
            if(l == y[i]) {
                used[i] = 1;
                dfs(idx+1, x[i]);
                used[i] = 0;
            }
        }
    }
}
int main() {
    int i;
    while(scanf("%d", &n) == 1 && n) {
        scanf("%d", &m);
        for(i = 0; i < m+2; i++) {
            scanf("%d %d", &x[i], &y[i]);
            used[i] = 0;
        }
        flag = 0;
        dfs(0, y[0]);
        puts(flag ? "YES" : "NO");
    }
    return 0;
}
