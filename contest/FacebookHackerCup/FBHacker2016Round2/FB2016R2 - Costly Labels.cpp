#include <bits/stdc++.h>
using namespace std;

const int MAXN = 128;
const int MAXM = 1048576;
struct Node {
    int x, y, cap;
    int cost;// x->y, v
    int next;
} edge[MAXM];
class MinCost {
public:
    int e, head[MAXN], pre[MAXN], record[MAXN], inq[MAXN];
    int dis[MAXN];
    int n;
    const int INF = 0x3f3f3f3f;
    void Addedge(int x, int y, int cap, int cost) {
        edge[e].x = x, edge[e].y = y, edge[e].cap = cap, edge[e].cost = cost;
        edge[e].next = head[x], head[x] = e++;
        edge[e].x = y, edge[e].y = x, edge[e].cap = 0, edge[e].cost = -cost;
        edge[e].next = head[y], head[y] = e++;
    }
    pair<int, int> mincost(int s, int t) {
        int mncost = 0;
        int flow, totflow = 0;
        int i, x, y;
        while(1) {
        	for (int i = 0; i < n; i++)
        		dis[i] = INF;
            int oo = dis[0];
            dis[s] = 0;
            deque<int> Q;
            Q.push_front(s);
            while(!Q.empty()) {
                x = Q.front(), Q.pop_front();
                inq[x] = 0;
                for(i = head[x]; i != -1; i = edge[i].next) {
                    y = edge[i].y;
                    if(edge[i].cap > 0 && dis[y] > dis[x] + edge[i].cost) {
                        dis[y] = dis[x] + edge[i].cost;
                        pre[y] = x, record[y] = i;
                        if(inq[y] == 0) {
                            inq[y] = 1;
                            if(Q.size() && dis[Q.front()] > dis[y])
                                Q.push_front(y);
                            else
                                Q.push_back(y);
                        }
                    }
                }
            }
            if(dis[t] == oo)
                break;
            flow = 0x3f3f3f3f;
            for(x = t; x != s; x = pre[x]) {
                int ri = record[x];
                flow = min(flow, edge[ri].cap);
            }
            for(x = t; x != s; x = pre[x]) {
                int ri = record[x];
                edge[ri].cap -= flow;
                edge[ri^1].cap += flow;
                edge[ri^1].cost = -edge[ri].cost;
            }
            totflow += flow;
            mncost += dis[t] * flow;
        }
        return make_pair(mncost, totflow);
    }
    void init(int n) {
    	this->n = n;
        e = 0;
        for (int i = 0; i <= n; i++)
            head[i] = -1;
    }
} g;


int N, K, P;
int costG[1024][32];
vector<int> treeG[1024];
long long dp[1024][32];	// dp[subtree: u][color of u: c] = mincost, don't care penalty P
long long dpv[1024];
void dfs(int u, int p) {
	for (int i = 0; i < K; i++)
		dp[u][i] = costG[u][i];
	for (auto &v : treeG[u]) {
		if (v == p)	continue;
		dfs(v, u);
		
		int cost = P;
		for (auto &adj_v : treeG[v]) {
			if (adj_v == u)	continue;
			cost += dpv[adj_v];
		}
		
		if (treeG[v].size() > K) {
			for (int i = 0; i < K; i++)
				dp[u][i] += cost;
		} else {
			// find disjoint-color by maximum weighted matching
			for (int i = 0; i < K; i++) {	// u-color
				int source = 0, sink = treeG[v].size()+K+1;
				g.init(treeG[v].size()+K+2);
				for (int j = 0; j < K; j++) {
					if (j == i)	continue;
					g.Addedge(treeG[v].size()+j+1, sink, 1, 0);
				}
				for (int j = 0; j < treeG[v].size(); j++) {
					int adj_v = treeG[v][j];
					if (adj_v == u)	continue;
					for (int k = 0; k < K; k++) {
						if (k == i)	continue;
						g.Addedge(j+1, treeG[v].size()+k+1, 1, dp[adj_v][k]);
					}
					g.Addedge(source, j+1, 1, 0);
				}
				pair<int, int> mm = g.mincost(source, sink);
				dp[u][i] += min(cost, mm.first);
			}
		}
	}
	dpv[u] = INT_MAX;
	for (int i = 0; i < K; i++)
		dpv[u] = min(dpv[u], dp[u][i]);
}
long long final(int v) {
	int cost = P;
	for (auto &adj_v : treeG[v])
		cost += dpv[adj_v];
	
	if (treeG[v].size() > K)
		return cost;
	// find disjoint-color by maximum weighted matching
	for (int i = 0; i < K; i++) {	// u-color
		int source = 0, sink = treeG[v].size() + K + 1;
		g.init(treeG[v].size()+K+2);
		for (int j = 0; j < K; j++) {
			g.Addedge(j+treeG[v].size()+1, sink, 1, 0);
		}
		for (int j = 0; j < treeG[v].size(); j++) {
			int adj_v = treeG[v][j];
			for (int k = 0; k < K; k++)
				g.Addedge(j+1, treeG[v].size()+k+1, 1, dp[adj_v][k]);
			g.Addedge(source, j+1, 1, 0);
		}
		
		pair<int, int> mm = g.mincost(source, sink);
		cost = min(cost, mm.first);
	}
	return cost;
}
int main() {
	int testcase, cases = 0;	
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &N, &K, &P);
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < K; j++) {
				scanf("%d", &costG[i][j]);
			}
		}
		
		for (int i = 1; i <= N; i++)
			treeG[i].clear();
		for (int i = 1; i < N; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			treeG[x].push_back(y);
			treeG[y].push_back(x);
		}
		
		dfs(1, -1);
		
		long long ret = INT_MAX;
		for (int i = 0; i < K; i++)
			ret = min(ret, dp[1][i]);
		ret += final(1);
		printf("Case #%d: %lld\n", ++cases, ret);
	}
	return 0;
}

