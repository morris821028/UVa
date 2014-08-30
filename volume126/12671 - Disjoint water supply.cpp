#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <map>
#include <algorithm>
using namespace std;

int parent[32767], weight[32767];

int findp(int x) {
    return parent[x] == x ? x : parent[x] = findp(parent[x]);
}

int main() {
    int n, m, x, y;
    while (scanf("%d %d", &n, &m) == 2 && n) {
        for (int i = 0; i <= n; i++) {
            parent[i] = 0, weight[i] = 0;
        }
        
        vector<int> g[1024];
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            if (x == 1) {
                parent[y] = y;
            } else
                g[y].push_back(x);
        }
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j < g[i].size(); j++) {
                int u = g[i][j];
                if (parent[i] == 0)
                    parent[i] = u;
                else if(findp(i) != findp(u))
                    parent[i] = i;
            }
        }
        
        for (int i = 2; i <= n; i++) {
            weight[findp(i)]++;
        }
        int ret = 0;
        for (int i = 2; i <= n; i++) {
            if (i == parent[i]) {
                ret += weight[i] * (n - 1 - weight[i]);
            }
        }
        printf("%d\n", ret/2 + n - 1);
    }
    return 0;
}
/*
 6 6
 1 2
 1 3
 1 4
 2 5
 2 6
 3 6
 8 11
 1 2
 1 3
 1 4
 2 5
 3 4
 6 7
 3 6
 3 7
 4 8
 2 6
 5 6
 */