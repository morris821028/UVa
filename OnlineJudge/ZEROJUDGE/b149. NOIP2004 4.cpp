#include <stdio.h>
#include <stdlib.h>
int n, m, tar[10005], acc, cnt;
int node[10005], p[10005], head;
int tmp[10005];
void dfs(int idx) {
    if(cnt == m)    return;
    if(idx == n) {
        if(acc == 0)
            acc = 1;
        else {
            cnt++;
            if(cnt == m) {
                int i;
                printf("%d", tmp[0]);
                for(i = 1; i < n; i++)
                    printf(" %d", tmp[i]);
                puts("");
            }
        }
        return;
    }
    int i, prev = 0;
    for(i = node[head]; i; i = node[i]) {
        prev = p[i];
        node[prev] = node[i];
        p[node[i]] = prev;
        if(acc || i == tar[idx]) {
            tmp[idx] = i;
            dfs(idx+1);
        }
        node[prev] = i;
        p[node[i]] = i;
    }
}
int main() {
    int i;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 0; i < n; i++)
            scanf("%d", &tar[i]);
        for(i = 1; i <= n; i++)
            node[i] = i+1, p[i] = i-1;
        node[0] = 1;
        node[n] = 0;
        head = 0;
        acc = 0, cnt = 0;
        dfs(0);
    }
    return 0;
}
