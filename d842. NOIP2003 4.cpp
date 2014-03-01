#include <stdio.h>
int g[305][305], gt[305];
int tg[305][305], tgt[305], p[305];
int used[305];
int layer[305][305], lt[305] = {};
void make_root(int nd, int dep) {
    layer[dep][lt[dep]++] = nd;
    used[nd] = 1;
    int i;
    for(i = 0; i < gt[nd]; i++) {
        if(used[g[nd][i]] == 0) {
            tg[nd][tgt[nd]++] = g[nd][i];
            p[g[nd][i]] = nd;
            make_root(g[nd][i], dep+1);
        }
    }
}
int o[305], res = 0xffff;
void dfs(int dep, int sum) {
    int i, cnt = 0;
    for(i = 0; i < lt[dep]; i++) {
        if(o[p[layer[dep][i]]] == 1)
            o[layer[dep][i]] = 1;
        else
            cnt++, o[layer[dep][i]] = 0;
    }
    if(cnt == 0) {
        if(sum < res)
            res = sum;
        return;
    }
    if(sum >= res)   return;
    for(i = 0; i < lt[dep]; i++) {
        if(o[layer[dep][i]] == 0) {
            o[layer[dep][i]] = 1;
            dfs(dep+1, sum+cnt-1);
            o[layer[dep][i]] = 0;
        }
    }
}
int main() {
    int n, p, x, y;
    scanf("%d %d", &n, &p);
    while(p--) {
        scanf("%d %d", &x, &y);
        g[x][gt[x]++] = y;
        g[y][gt[y]++] = x;
    }
    make_root(1, 1);
    dfs(2, 1);
    printf("%d\n", res);
    return 0;
}
