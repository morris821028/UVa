#include <bits/stdc++.h>
using namespace std;
/*
Paper: An O(nm)-Time Algorithm for Finding the Minimum Length Directed Cycle in a Graph
*/ 
namespace {
// <Min begin> 
const int MAXV = 5005;
const int INT_INF = 0x3f3f3f3f;
const int64_t LL_INF = 0x3f3f3f3f3f3f3f3fLL;
vector<pair<int, int64_t>> g[MAXV];
void init(int n) {
	for (int i = 1; i <= n; i++)
		g[i].clear();
}
// <SCC begin>
int vfind[MAXV], findIdx;
int stk[MAXV], stkIdx;
int in_stk[MAXV], visited[MAXV], contract[MAXV];
vector<int> scc_group[MAXV];
int scc_cnt;
int scc(int u) {
    in_stk[u] = visited[u] = 1;
    stk[++stkIdx] = u, vfind[u] = ++findIdx;
    int mn = vfind[u];
    for (auto e : g[u]) {
    	int v = e.first;
        if (!visited[v])
            mn = min(mn, scc(v));
        if (in_stk[v])
            mn = min(mn, vfind[v]);
    }
    if (mn == vfind[u]) {
    	scc_group[scc_cnt].clear();
        do {
            in_stk[stk[stkIdx]] = 0;
            contract[stk[stkIdx]] = scc_cnt;
            scc_group[scc_cnt].push_back(stk[stkIdx]);
        } while (stk[stkIdx--] != u);
        scc_cnt++;
    }
    return mn;
}
// <SCC end>
int cmp(pair<int, int64_t> &a, pair<int, int64_t> &b) {
	if (a.second != b.second)
		return a.second < b.second;
	return a.first < b.first;
}
pair<int64_t, int64_t> karp(int n, vector<vector<pair<int, int64_t>>> &sg) {
	// Karp's Algorithm
	static int64_t d[MAXV*MAXV];
	int s = 0;
	memset(d, 0x3f, sizeof(d[0])*(n+1)*n);
#define XY(x, y) ((x)*(n)+(y))
	d[XY(0, s)] = 0;
	for (int k = 0; k < n; k++) {
		for (int u = 0; u < n; u++) {
			if (d[XY(k, u)] == LL_INF)	continue;
			int64_t du = d[XY(k, u)];
			for (auto e : sg[u]) {
				if (du + e.second < d[XY(k+1, e.first)])
					d[XY(k+1, e.first)] = du + e.second;
			}
		}
	}
	pair<int64_t, int64_t> mean = {INT_INF, 1};
	for (int i = 0; i < n; i++) {
		if (d[XY(n, i)] == LL_INF)
			continue;
		pair<int64_t, int64_t> mx = {-INT_INF, 1};
		for (int j = 0; j < n; j++) {
			int64_t a = d[XY(n, i)] - d[XY(j, i)], b = n - j;
			if ((double) a/b > (double) mx.first/mx.second)
				mx = {a, b}; // max(a/b, mx)
		}
		if ((double) mx.first/mx.second < (double) mean.first/mean.second)
			mean = mx; // min(mean, mx)
	}
	return mean;
}
int64_t findMinWeightCycleByGroup(int sid, int64_t ret_upper) {
	static int label[MAXV];
	int n = scc_group[sid].size();
	vector<vector<pair<int, int64_t>>> sg(n, vector<pair<int, int64_t>>());
	for (int i = 0; i < n; i++)
		label[scc_group[sid][i]] = i;
	for (auto u : scc_group[sid]) {
		int x = label[u];
		for (auto v : g[u]) {
			if (contract[v.first] != sid)
				continue;
			sg[x].push_back({label[v.first], v.second});
		}
		sort(sg[x].begin(), sg[x].end(), cmp);
	}
	pair<int64_t, int64_t> mean = karp(n, sg);
	if (mean.first < 0)		return -1;
	if (mean.first == 0)	return 0;
	// MLDC Algorithm
	//// Adjustment-(1)
	for (int u = 0; u < n; u++) {
		for (auto &e : sg[u])	// adjust edge weight to minus mean
			e.second = e.second * mean.second - mean.first;
	}
	//// Bellman-Ford algorithm
	static int64_t dist[MAXV];
	int s = 0;
	memset(dist, 0x3f, sizeof(dist[0])*n);
	dist[s] = 0;
	for (int i = 1; i < n; i++) {
		int update = 0;
		for (int u = 0; u < n; u++) {
			if (dist[u] == LL_INF)	continue;
			for (auto e : sg[u]) {
				if (dist[u] + e.second < dist[e.first])
					dist[e.first] = dist[u] + e.second, update = 1;
			}
		}
		if (!update)	break;
	}
	//// Adjustment-(2)
	vector<vector<pair<int, int64_t>>> inv_sg(n, vector<pair<int, int64_t>>());
	for (int u = 0; u < n; u++) {
		for (auto &e : sg[u])	// adjust c^p_{ij} = c_{ij} + p(i) - p(j)
			e.second = e.second + dist[u] - dist[e.first] + mean.first,
			inv_sg[e.first].push_back({u, e.second});
	}
	//// Dial's Algorithm
	static list<int> bin[MAXV];
	const int64_t GAP = mean.first;
	int64_t ret = LL_INF;
	for (int st = 0; st < n; st++) {
		static vector<pair<int64_t, list<int>::iterator>> dist(MAXV);
		if (inv_sg[st].size() == 0 || sg[st].size() == 0)
			continue;
		for (int i = st; i < n; i++) {
			dist[i].first = LL_INF;
			bin[i].clear();
		}
		bin[0].push_back(st);
		dist[st].first = 0;
		int idx = 0;
		int LIMIT_BUK = n;
		if (ret_upper != LL_INF)
			LIMIT_BUK = min(LIMIT_BUK, (int) (ret_upper*mean.second/GAP));
		while (true) {
			while (bin[idx].size() == 0 && idx < LIMIT_BUK)
				idx++;
			if (idx >= LIMIT_BUK)
				break;
			int u = bin[idx].front();
			bin[idx].pop_front();
			for (auto e : sg[u]) {
				int v = e.first;
				if (v < st)	continue;
				int64_t w = e.second;
				int64_t du = dist[u].first, dv = dist[v].first;
				if (v == st) {
					ret = min(ret, du+w);
					LIMIT_BUK = min(LIMIT_BUK, (int) (ret*mean.second/GAP));
					continue;
				}
				if (dv > du + w) {
					int pbid = dv/GAP, qbid = (du+w)/GAP;
					if (qbid >= LIMIT_BUK)
						continue;
					if (dv != LL_INF)
						bin[pbid].erase(dist[v].second);
					dist[v].first = du + w;
					bin[qbid].push_front(v);
					dist[v].second = bin[qbid].begin();
				}
			}
		}
		// find a cycle on shortest path tree
		for (auto e : inv_sg[st]) {
			int v = e.first;
			if (v >= st && dist[v].first != LL_INF)
				ret = min(ret, dist[v].first + e.second);
		}
		if (ret != LL_INF && ret / mean.second < ret_upper)
			ret_upper = ret / mean.second;
	}
	return ret / mean.second;
}
int64_t findMinWeightCycle(int n) {
	// vertex in [1, n]
	memset(visited, 0, sizeof(visited[0])*(n+1));
	memset(in_stk, 0, sizeof(visited[0])*(n+1));
	scc_cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (visited[i])	continue;
		stkIdx = findIdx = 0;
		scc(i);
	}
	// check whether cycle exists
	int hasCycle = 0;
	for (int i = 0; i < scc_cnt && !hasCycle; i++) {
		if (scc_group[i].size() > 1)
			hasCycle = 1;
	}
	if (hasCycle == 0)
		return -2;
	// check whether negative cycle exists
	int64_t ret = LL_INF;
	for (int i = 0; i < scc_cnt; i++) {
		if (scc_group[i].size() == 1)
			continue;
		int64_t tmp = findMinWeightCycleByGroup(i, ret);
		if (tmp <= 0)
			return tmp;
		ret = min(ret, tmp);
	}
	return ret;
}
// <Min end>
}
int main() {
	int testcase, n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		init(n);
		for (int i = 0; i < m; i++) {
			int x, y, w;
			scanf("%d %d %d", &x, &y, &w);
			g[x].push_back({y, w});
		}
						
		int64_t ret = findMinWeightCycle(n);
		if (ret == -2) {
			puts("INF");
		} else if (ret == -1) {
			puts("-1");
		} else {
			printf("%lld\n", ret);
		}
	}
	return 0;
}
