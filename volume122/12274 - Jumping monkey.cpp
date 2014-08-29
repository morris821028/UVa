#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <math.h>
#include <iostream>
#include <map>
using namespace std;

int n, m;
int g[32];
int parent[32], weight[32];

int findp(int x) {
    return parent[x] == x ? x : parent[x] = findp(parent[x]);
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if (x == y) return 0;
    parent[x] = y, weight[y] += weight[x];
    return 1;
}

int dp[1<<21], used[1<<21] = {}, testcase = 0;
int pre[1<<21][2];
void bfs() {
    queue<int> Q;
    int u, v;
    testcase++;
    dp[(1<<n)-1] = 0, used[(1<<n)-1] = testcase;
    Q.push((1<<n)-1);
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        for (int i = 0; (1<<i) <= u; i++) {
            if ((u>>i)&1) { // kill
                v = 0;
                for (int j = 0; (1<<j) <= u; j++) {
                    if ((u>>j)&1) {
                        if (j != i)
                            v |= g[j];
                    }
                }
                if (used[v] != testcase) {
                    used[v] = testcase;
                    pre[v][0] = u, pre[v][1] = i;
                    dp[v] = dp[u] + 1;
                    if (v == 0) {
                        printf("%d:", dp[v]);
                        stack<int> stk;
                        do {
                            stk.push(pre[v][1]);
                            v = pre[v][0];
                        } while (v != (1<<n)-1);
                        while (!stk.empty()) {
                            printf(" %d", stk.top());
                            stk.pop();
                        }
                        puts("");
                        return;
                    }
                    Q.push(v);
                }
            }
        }
    }
    puts("Impossible");
}
int main() {
    int x, y;
    while (scanf("%d %d", &n, &m) == 2 && n + m) {
        for (int i = 0; i < n; i++)
            g[i] = 0, parent[i] = i, weight[i] = 1;
        int cycle = 0;
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            g[x] |= 1<<y, g[y] |= 1<<x;
            if (!joint(x, y))
                cycle = 1;
        }
        
        if (cycle) {
            puts("Impossible");
            continue;
        }
        bfs();
    }
    return 0;
}
/*
 2 1
 0 1
 
 3 3
 0 1
 1 2
 2 0
 
 4 3
 0 1
 2 3
 1 3
 
 0 0
 */