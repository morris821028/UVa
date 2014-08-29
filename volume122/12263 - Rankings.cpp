#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;

int g[512][512], indeg[512];
void topo(int n) {
    queue<int> Q;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0)
            Q.push(i);
    }
    int r[512], rt = 0, u;
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        r[rt++] = u;
        for (int i = 1; i <= n; i++) {
            if (g[u][i]) {
                if (--indeg[i] == 0)
                    Q.push(i);
            }
        }
    }
    if (rt != n) {
        puts("IMPOSSIBLE");
        return;
    }
    for (int i = 0; i < n; i++) {
        printf("%d%c", r[i], i == n-1 ? '\n' : ' ');
    }
}
int main() {
    int testcase, rank[512];
    int n, m, x, y;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &rank[i]);
        
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                g[i][j] = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                g[rank[i]][rank[j]] = 1;
        
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            swap(g[x][y], g[y][x]);
        }
        
        for (int i = 1; i <= n; i++) {
            indeg[i] = 0;
            for (int j = 1; j <= n; j++)
                indeg[i] += g[j][i];
        }
        topo(n);
    }
    return 0;
}

/*
 3
 5
 5 4 3 2 1
 2
 2 4
 3 4
 3
 2 3 1
 0
 4
 1 2 3 4
 3
 1 2
 3 4
 2 3
 */