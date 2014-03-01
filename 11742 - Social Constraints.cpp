#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int p[105], used[105];
int ra[20], rb[20], rc[20];
int ret, n, m;
void dfs(int idx) {
    int i;
    if(idx == n) {
        for(i = 0; i < m; i++) {
            if(rc[i] < 0) {
                if(abs(p[ra[i]]-p[rb[i]]) < -rc[i])
                    break;
            } else {
                if(abs(p[ra[i]]-p[rb[i]]) > rc[i])
                    break;
            }
        }
        if(i == m)  ret++;
        return;
    }
    for(i = 0; i < n; i++) {
        if(used[i] == 0) {
            used[i] = 1;
            p[i] = idx;
            dfs(idx+1);
            used[i] = 0;
        }
    }
}
int main() {
    int i;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        for(i = 0; i < m; i++)
            scanf("%d %d %d", &ra[i], &rb[i], &rc[i]);
        ret = 0;
        dfs(0);
        printf("%d\n", ret);
    }
    return 0;
}
