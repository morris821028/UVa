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
long long dp[1024][32][32];	// dp[subtree: u][color of u: c][color of u'parent: c]
long long dpv[1024][32];
void dfs(int u, int p) {
	for (auto &v : treeG[u]) {
		if (v == p)	continue;
		dfs(v, u);
	}
	
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {
			int cost = costG[u][i] + P;
			for (auto &v : treeG[u]) {
				if (v == p)	continue;
				cost += dpv[v][i];
			}
			dp[u][i][j] = cost;
			
			if (treeG[u].size() > K)
				continue;
				
			int source = 0, sink = treeG[u].size()+K+1;
			g.init(treeG[u].size()+K+2);
			for (int k = 0; k < K; k++) {
				if (k == j && p != -1)	continue;	// parent color
				g.Addedge(treeG[u].size()+k+1, sink, 1, 0);
			}
			int branch = 0;
			for (int it = 0; it < treeG[u].size(); it++) {
				int v = treeG[u][it];
				if (v == p)	continue;
				branch++;
				for (int k = 0; k < K; k++) {
					if (k == j && p != -1)	continue;
					g.Addedge(it+1, treeG[u].size()+k+1, 1, dp[v][k][i]);
				}
				g.Addedge(source, it+1, 1, 0);
			}
			
			pair<int, int> mm = g.mincost(source, sink);
			if (mm.second != branch)
				continue;
			dp[u][i][j] = min(dp[u][i][j], (long long) mm.first + costG[u][i]);
		}
	}
	
	for (int i = 0; i < K; i++) {
		dpv[u][i] = INT_MAX;
		for (int j = 0; j < K; j++)
			dpv[u][i] = min(dpv[u][i], dp[u][j][i]);
	}
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
			for (int j = 0; j < K; j++)
				ret = min(ret, dp[1][i][j]);
		printf("Case #%d: %lld\n", ++cases, ret);
	}
	return 0;
}

