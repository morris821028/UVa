#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <set>
#include <algorithm>
using namespace std;
const int MAXV = 2048;
const int MAXE = 131072;
const long long INF = 1e+60;
struct Edge {
    int to, eid;
    double w;
    Edge *next;
};
Edge edge[MAXE], *adj[MAXV];
int e = 0;
double dist[MAXV];
void addEdge(int x, int y, double v)  {
    edge[e].to = y, edge[e].w = v, edge[e].eid = e;
    edge[e].next = adj[x], adj[x] = &edge[e++];
}
void dijkstra(int st, double dist[], int n) {
    typedef pair<double, int> PLL;
    for (int i = 0; i <= n; i++)
        dist[i] = INF;
    set<PLL> pQ;
    PLL u;
    pQ.insert(PLL(0, st)), dist[st] = 0;
    while (!pQ.empty()) {
        u = *pQ.begin(), pQ.erase(pQ.begin());
        for (Edge *p = adj[u.second]; p; p = p->next) {
            if (dist[p->to] > dist[u.second] + p->w) {
                if (dist[p->to] != INF)
                    pQ.erase(pQ.find(PLL(dist[p->to], p->to)));
                dist[p->to] = dist[u.second] + p->w;
                pQ.insert(PLL(dist[p->to], p->to));
            }
        }
    }
}

int I[MAXE], J[MAXE], A[MAXE], B[MAXE];
double f(int N, int M, double t) {
    e = 0;
    for (int i = 1; i <= N; i++)
        adj[i] = NULL;
    for (int i = 0; i < M; i++) {
        double cost = t * A[i] + B[i];
        addEdge(I[i], J[i], cost);
        addEdge(J[i], I[i], cost);
    }
    
    dijkstra(1, dist, N);
    return dist[N];
}
int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) == 2) {
        for (int i = 0; i < M; i++)
            scanf("%d %d %d %d", &I[i], &J[i], &A[i], &B[i]);
        double l = 0, r = 24 * 60, mid, midmid, md, mmd;
        double ret = 0;
        for (int it = 0; it < 100; it++) {
            mid = (l+r)/2;
            midmid = (mid+r)/2;
            md = f(N, M, mid);
            mmd = f(N, M, midmid);
            ret = max(ret, md);
            if (fabs(md - mmd) < 1e-6)
                break;
            if (md < mmd)
                l = mid;
            else
                r = midmid;
        }
        printf("%.5lf\n", ret);
    }
    return 0;
}

