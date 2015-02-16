#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
#include <iostream>
#include <sstream>
using namespace std;

#define MAXN 262144
struct edge {
    int x, y;
    long long v;
    edge(int a = 0, int b = 0, long long c = 0):
    x(a), y(b), v(c) {}
    bool operator<(const edge &a) const {
        return v > a.v;
    }
};
int parent[MAXN], weight[MAXN];
long long dp[MAXN];     // dp[u]: u as root, each node will get dp[u] for C(i, j)
int findp(int x) {      // disjoint set, forest
    int p = parent[x];
    if (p == x) return x;
    p = findp(p);
    if (p != parent[x]) // extra process
        dp[x] += dp[parent[x]];
    return parent[x] = p;
}
int main() {
    int N, x, y, px, py;
    long long v;
    while (scanf("%d", &N) == 1) {
        vector<edge> D;
        for (int i = 0; i <= N; i++)
            parent[i] = i, weight[i] = 1, dp[i] = 0;
        for (int i = 1; i < N; i++) {
            scanf("%d %d %lld", &x, &y, &v);
            D.push_back(edge(x, y, v));
        }
        sort(D.begin(), D.end());
        for (int i = 0; i < D.size(); i++) {
            x = D[i].x, y = D[i].y, v = D[i].v;
            px = findp(x), py = findp(y);
            dp[px] += weight[py] * v;
            dp[py] += weight[px] * v - dp[px];
            parent[py] = px, weight[px] += weight[py];
        }
        
        long long ret = 0;
        for (int i = 1; i <= N; i++) {
            findp(i);
            long long Cij = dp[i];
            if (parent[i] != i) {
                Cij += dp[parent[i]];
            }
            ret = max(ret, Cij);
//            printf("%d %lld parent %d\n", i, Cij, parent[i]);
        }
        printf("%lld\n", ret);
    }
    return 0;
}
/*
 4
 1 2 2
 2 4 1
 2 3 1
 4
 1 2 1
 2 4 1
 2 3 1
 */
