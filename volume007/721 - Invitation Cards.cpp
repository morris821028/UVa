#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define MAXN 1048576
vector< pair<int, long long> > g[MAXN], invg[MAXN];
long long dist[MAXN];
int inq[MAXN];
long long spfa(int source, int n, vector< pair<int, long long> > g[]) {
    for (int i = 0; i < n; i++) {
        dist[i] = 1LL<<60, inq[i] = 0;
    }
    queue<int> Q;
    int u, v;
    long long w;
    Q.push(source), dist[source] = 0;
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        inq[u] = 0;
        for (int i = 0; i < g[u].size(); i++) {
            v = g[u][i].first, w = g[u][i].second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!inq[v]) {
                    Q.push(v), inq[v] = 1;
                }
            }
        }
    }
    long long ret = 0;
    for (int i = 0; i < n; i++) {
        ret += dist[i];
    }
    return ret;
}
int main() {
    int testcase, N, M;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &N, &M);
        for (int i = 0; i < N; i++) {
            g[i].clear(), invg[i].clear();
        }
        for (int i = 0; i < M; i++) {
            int x, y, c;
            scanf("%d %d %d", &x, &y, &c);
            x--, y--;
            g[x].push_back(make_pair(y, c));
            invg[y].push_back(make_pair(x, c));
        }
        long long ret = 0;
        ret += spfa(0, N, g);
        ret += spfa(0, N, invg);
        printf("%lld\n", ret);
    }
    return 0;
}
/*
 2
 2 2
 1 2 13
 2 1 33
 4 6
 1 2 10
 2 1 60
 1 3 20
 3 4 10
 2 4 5
 4 1 50
*/