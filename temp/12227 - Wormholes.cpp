#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <map>
#include <stack>
using namespace std;

struct Point3D {
    long long x, y, z;
    Point3D(long long a = 0, long long b = 0, long long c = 0):
    x(a), y(b), z(c) {}
    void read() {
        scanf("%lld %lld %lld", &x, &y, &z);
    }
    long long dist(const Point3D &a) const {
        return ceil(sqrt((a.x - x) * (a.x - x)
                         + (a.y - y) * (a.y - y)
                         + (a.z - z) * (a.z - z)));
    }
};
struct Edge {
    int to;
    long long t, d;
    Edge(int a = 0, long long b = 0, long long c = 0):
    to(a), t(b), d(c) {}
    bool operator<(const Edge &a) const {
        return d < a.d;
    }
};
#define MAXN 128
#define INF (1LL<<60)
vector<Edge> g[MAXN];
long long dist[MAXN], preTime[MAXN];
int inq[MAXN], cnt[MAXN], pre[MAXN], neg[MAXN], used[MAXN], cases = 0;
void goToNegCycle(int st, int n, deque<int> &Q, int inq[]) {
    for (int i = 0; i < n; i++)
        cnt[i] = 0, neg[i] = 0;
    int u;
    Q.push_front(st);
    while (!Q.empty()) {
        u = Q.front(), Q.pop_front();
        inq[u] = 0;
        // printf("neg %d %lld\n", u, dist[u]);
        for (int i = 0; i < g[u].size(); i++) {
            long long cost = g[u][i].d;
            if (g[u][i].t > dist[u]) { // not exists wormholes
                cost = g[u][i].d + g[u][i].t - dist[u];
            }
            if (dist[g[u][i].to] > dist[u] + cost) {
                dist[g[u][i].to] = dist[u] + cost;
                pre[g[u][i].to] = u, preTime[g[u][i].to] = g[u][i].t;
                if (!inq[g[u][i].to]) {
                    if (++cnt[g[u][i].to] > n + 1) {
                        cases++;
                        cnt[g[u][i].to] = 1;
                        int st = g[u][i].to, ok = 0, disappear;
                        long long mx;
                        for (int j = pre[st]; j != -1; j = pre[j]) {
                            if (used[j] == cases) {
                                ok = 1, st = j;
                                break;
                            }
                            used[j] = cases;
                        }
                        mx = preTime[st], disappear = st;
                        for (int j = pre[st]; j != -1; j = pre[j]) {
                            if (j == st) {
                                break;
                            }
                            if (preTime[j] > mx) {
                                mx = preTime[j], disappear = j;
                            }
                        }
                        if (ok) {
                            if (dist[disappear] > mx) {
                                dist[disappear] = mx;
                                if (Q.size() && dist[Q.front()] > dist[disappear])
                                    Q.push_front(disappear);
                                else
                                    Q.push_back(disappear);
                            }
                        }
                    }
                    if (!inq[g[u][i].to]) {
                        inq[g[u][i].to] = 1;
                        if (Q.size() && dist[Q.front()] > dist[g[u][i].to])
                            Q.push_front(g[u][i].to);
                        else
                            Q.push_back(g[u][i].to);
                    }
                }
            }
        }
    }
}
void spfa(int st, int ed, int n) {
    for (int i = 0; i < n; i++)
        pre[i] = -1;
    int inq[MAXN];
    for (int i = 0; i < n; i++)
        dist[i] = INF, inq[i] = 0;
    int u;
    deque<int> Q;
    dist[st] = 0;
    goToNegCycle(st, n, Q, inq);
    printf("%lld\n", dist[ed]);
}
int main() {
    int testcase, n;
    long long t, d;
    Point3D D[MAXN];
    scanf("%d", &testcase);
    while (testcase--) {
        for (int i = 0; i < MAXN; i++)
            g[i].clear();
        D[0].read();
        D[1].read();
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            D[(1 + i) * 2].read();
            D[(1 + i) * 2 + 1].read();
            scanf("%lld %lld", &t, &d);
            g[(1 + i) * 2].push_back(Edge((1 + i) * 2 + 1, t, d));
        }
        n = (n + 1) * 2;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                g[i].push_back(Edge(j, -INF, D[i].dist(D[j])));
            }
        }
        spfa(0, 1, n);
    }
    return 0;
}
/*
 2
 0 0 0 100 0 0
 2
 1 1 0 1 2 0 -100 -2
 0 1 0 100 1 0 -150 10
 0 0 0 10 0 0
 1
 5 0 0 -5 0 0 0 0
 */