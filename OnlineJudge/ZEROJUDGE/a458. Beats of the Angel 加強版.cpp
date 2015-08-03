#include <bits/stdc++.h> 
using namespace std;
// http://zrt.github.io/2014/08/13/bzoj2725/
const int MAXV = 200005;
const int MAXE = 200005<<1;
const long long INF = 1LL<<60;
struct Edge {
	int to, eid;
	long long w;
	Edge *next;
};
Edge edge[MAXE], *adj[MAXV];
int e = 0;
long long Ds[MAXV], De[MAXV];
int Bs[MAXV], Be[MAXV], keye[MAXE];
void addEdge(int x, int y, long long v)  {
	edge[e].to = y, edge[e].w = v, edge[e].eid = e;
	edge[e].next = adj[x], adj[x] = &edge[e++];
	edge[e].to = x, edge[e].w = v, edge[e].eid = e;
	edge[e].next = adj[y], adj[y] = &edge[e++];
}
void dijkstra(int st, long long dist[], int n) {
typedef pair<long long, int> PLL;
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
int bottleneck(int st, int ed, long long Ds[], long long De[], int n) {
typedef pair<long long, pair<long long, int> > PLL;
	vector<PLL> A;
	// short path DAG st-ed
	long long d = Ds[ed];
	for (int i = 1; i <= n; i++) {
		for (Edge *p = adj[i]; p; p = p->next) {
			if (Ds[p->to] == Ds[i] + p->w && Ds[p->to] + De[p->to] == d) {
				A.push_back(PLL(Ds[i], {Ds[p->to], p->eid}));
			}
		}
	}
	// bottleneck edge st-ed
	sort(A.begin(), A.end());
	priority_queue<long long, vector<long long>, std::greater<long long>> pQ;
	int cnt = 0;
	for (int i = 0; i < e; i++)
		keye[i] = 0;
	for (int i = 0; i < A.size(); ) {
		long long l = A[i].first;
		while (!pQ.empty() && pQ.top() <= l)
			pQ.pop();
		while (i < A.size() && A[i].first <= l)
			pQ.push(A[i].second.first), i++;
		if (pQ.size() == 1) {
			keye[A[i-1].second.second] = 1;
			keye[A[i-1].second.second^1] = -1;
			cnt++;
		}
	} 
	return cnt;
}
void bfs(int st, int dist[], long long Ds[], int n, int f) {
typedef pair<long long, int> PLL;
	// work for short-path DAG, weight: key edge
	vector<PLL> A;
	for (int i = 1; i <= n; i++)
		A.push_back(PLL(Ds[i], i)), dist[i] = 0x3f3f3f3f;
	dist[st] = 0;
	sort(A.begin(), A.end());
	for (int i = 0; i < n; i++) {
		int x = A[i].second;
		for (Edge *p = adj[x]; p; p = p->next) {
			if (Ds[p->to] == Ds[x] + p->w)
				dist[p->to] = min(dist[p->to], dist[x] + (keye[p->eid] == f));
		}
	}
}
long long solve(int st, int ed, long long Ds[], long long De[], int n) {
typedef pair<long long, int> PLL;
typedef pair<int, int> PII;
typedef multiset<long long>::iterator MIT;
	bfs(st, Bs, Ds, n, 1);
	bfs(ed, Be, De, n, -1);
	vector<PLL> A;
	vector<PII> B, C;
	for (int i = 1; i <= n; i++) {
		A.push_back(PLL(Ds[i], i));
		B.push_back(PII(Bs[i], i));
		C.push_back(PII(Be[i], i));
	}
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	sort(C.begin(), C.end());
	long long d = Ds[ed];
	int Bidx = 0, Cidx = n-1;
	multiset<long long> S;
	vector< vector<MIT> > RM(n+1, vector<MIT>());
	long long ret = 0;
	for (int i = 0; i < n; i++) {
		int x = A[i].second;
		for (Edge *p = adj[x]; p; p = p->next) {
			if (Ds[p->to] == Ds[x] + p->w && Ds[p->to] + De[p->to] == d) {
				if (keye[p->eid]) {
					int bb = Bs[x], cut = Be[p->to];
					// relax
					for (; Bidx < B.size() && B[Bidx].first <= bb; Bidx++) {
						int u = B[Bidx].second;
						for (Edge *q = adj[u]; q; q = q->next) {
							if (Be[q->to] <= cut && p != q) {
								MIT it = S.insert(Ds[u] + q->w + De[q->to]);
								RM[q->to].push_back(it);
							}
						}
					}
					// remove
					for (; Cidx >= 0 && C[Cidx].first > cut; Cidx--) {
						int u = C[Cidx].second;
						for (auto e : RM[u])
							S.erase(e);
					}
					long long replace_path = INF;
					if (!S.empty())
						replace_path = *S.begin();
					replace_path = min(replace_path, d + p->w); // this edge double weight
					ret = max(ret, replace_path - d);
				}
			}
		}
	}
	return ret;
}
int main() {
	int n, m, x, y;
	int st, ed;
	long long v;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++)
			adj[i] = NULL;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %lld", &x, &y, &v);
			addEdge(x, y, v);
		}
		scanf("%d %d", &st, &ed);
		dijkstra(st, Ds, n);
		dijkstra(ed, De, n);
		int cnt = bottleneck(st, ed, Ds, De, n);
		if (cnt == 0)
			puts("0");
		else
			printf("%lld\n", solve(st, ed, Ds, De, n));
	}
	return 0;
}

