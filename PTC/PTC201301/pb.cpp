#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int g[20][20], J, res;
int used[20], H[20];
int t, n, m, K;
int way[20], V[20], W[20];
void dfs(int idx, int sum, int ch) {
    if(idx == n) {
        if() {
            res++;
            for(int i = 0; i < n; i++)
                printf("%d ", way[i]);
            puts("");
//            printf("%d\n", sum);
        }
        return;
    }
    int i;
    for(i = 0; i < m; i++) {
        if(used[i] == 0 && g[idx][i] != -1) {
            used[i] = 1;
            way[idx] = i;
            dfs(idx+1, p+(g[idx][i] > V[idx]), q+2);
            used[i] = 0;
        }
    }
    dfs(idx+1, p, q);
}
int main() {
    scanf("%d", &t);
    int i, j;
    while(t--) {
        scanf("%d %d", &n, &m);
        memset(H, 0, sizeof(H));
        for(i = 0; i < n; i++)
            for(j = 0; j < m; j++)
                scanf("%d", &g[i][j]), H[i] = max(H[i], g[i][j]);
        for(i = n-1; i >= 0; i--)
            H[i] += H[i+1];
        scanf("%d", &K);
        J = 0, res = 0;
        int x, y;
        for(i = 0; i < K; i++) {
            scanf("%d %d", &x, &y);
            V[x-1] = g[x-1][y-1];
            J += g[x-1][y-1];
        }
        dfs(0, 0, 0);
        printf("%d\n", res);
    }
    return 0;
}
/*
2
2 2
1 2
3 4
2
1 1
2 2
3 3
3 -1 2
5 1 3
3 1 2
3
1 1
2 2
3 3
*/
