#include <stdio.h> 
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXV = 512;
const int MAXE = 65536;
const int INF = 1<<30;
struct Edge {
    int to, eid;
    int w;
    Edge *next;
};
Edge edge[MAXE], *adj[MAXV];
int e = 0;
int dist[MAXV];
void addEdge(int x, int y, int v)  {
    edge[e].to = y, edge[e].w = v, edge[e].eid = e;
    edge[e].next = adj[x], adj[x] = &edge[e++];
}
void dijkstra(int st, int dist[], int n) {
    typedef pair<int, int> PLL;
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
struct ELE {
	int x, y, r, c;
	ELE(int x=0, int y=0, int r=0, int c=0):
		x(x), y(y), r(r), c(c) {}
	bool operator<(const ELE &v) const {
		return r < v.r;
	}
};

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m;
		scanf("%d %d", &n, &m);		
		vector<ELE> A;
		for (int i = 0; i < m; i++) {
			int x, y, r, c;
			scanf("%d %d %d %d", &x, &y, &r, &c);
			A.push_back(ELE(x, y, r, c));
		}
		e = 0;
    	for (int i = 0; i < n; i++)
        	adj[i] = NULL;
		sort(A.begin(), A.end());
		int ret = -1;
		long long retp = 0;
		int l = 0, r = 100, mid;
		while (l <= r) {
			mid = (l + r)/2;
			e = 0;
			for (int i = 0; i < n; i++)
				adj[i] = NULL;
			for (int i = 0; i < m && A[i].r <= mid; i++)
				addEdge(A[i].x, A[i].y, A[i].c);
			dijkstra(0, dist, n);
			if (dist[n-1] == INF)
				l = mid+1;
			else
				r = mid-1, ret = mid, retp = dist[n-1];
		}
		if (ret == -1) {
			puts("-1");
			continue;
		}
		printf("%d %lld\n", ret, retp);
	}
	return 0;
}
