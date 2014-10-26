#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
using namespace std;
#define MAXN 128
struct Node {
    int x, y;
	long long cap, flow;// x->y, v
    int next;
} edge[100005];
int e, head[MAXN], prev[MAXN], record[MAXN];
int level[MAXN], visited[MAXN];
void addEdge(int x, int y, long long v) {
    edge[e].x = x, edge[e].y = y, edge[e].cap = v, edge[e].flow = 0;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].cap = 0, edge[e].flow = 0;
    edge[e].next = head[y], head[y] = e++;
}
bool buildLevelGraph(int s, int t) {
    memset(level, 0, sizeof(level));
    queue<int> Q;
    Q.push(s), level[s] = 1;
    while(!Q.empty()) {
        int tn = Q.front();
        Q.pop();
        for(int i = head[tn]; i != -1; i = edge[i].next) {
            int y = edge[i].y;
            if(edge[i].cap > edge[i].flow && level[y] == 0) {
                level[y] = level[tn] + 1;
                Q.push(y);
            }
        }
    }
    return level[t] > 0;
}
int constructBlockingFlow(int s, int t) {
    int ret = 0;
    stack<int> stk;
    memset(visited, 0, sizeof(visited));
    stk.push(s);
    while(!stk.empty()) {
        int now = stk.top();
        if(now != t) {
            for(int i = head[now]; i != -1; i = edge[i].next) {
                int y = edge[i].y;
                if(visited[y] || level[y] != level[now] + 1)
                    continue;
                if(edge[i].cap > edge[i].flow) {
                    stk.push(y), prev[y] = now, record[y] = i;
                    break;
                }
            }
            if(stk.top() == now)
                stk.pop(), visited[now] = 1;
        } else {
            long long flow = 1LL<<32, bottleneck;
            for(int i = t; i != s; i = prev[i]) {
                int ri = record[i];
                flow = min(flow, edge[ri].cap - edge[ri].flow);
            }
            for(int i = t; i != s; i = prev[i]) {
                int ri = record[i];
                edge[ri].flow += flow;
                edge[ri^1].flow -= flow;
                if(edge[ri].cap - edge[ri].flow == 0)
                    bottleneck = prev[i];
            }
            while(!stk.empty() && stk.top() != bottleneck)
                stk.pop();
            ret += flow;
        }
    }
    return ret;
}
int maxflowDinic(int s, int t) {
    int flow = 0;
    while(buildLevelGraph(s, t))
        flow += constructBlockingFlow(s, t);
    return flow;
}
vector<int> maxflowCut(int s, int t, int n) {
	buildLevelGraph(s, t);
	vector<int> ret;
	for (int i = 1; i <= n; i++) {
		for (int j = head[i]; j != -1; j = edge[j].next) {
			if (level[edge[j].x] && !level[edge[j].y] && edge[j].cap > 0 && edge[j].cap == edge[j].flow)
				ret.push_back(j);
		}
	}
	return ret;
}
int clearflow(int n) {
	for (int i = 1; i <= n; i++) {
    	for (int j = head[i]; j != -1; j = edge[j].next)
    		edge[j].flow = 0;
	}
}
int main() {
    int n, m, c;
    int x, y, v;
    int cases = 0;
    while(scanf("%d %d %d", &n, &m, &c) == 3 && n) {
        e = 0;
        memset(head, -1, sizeof(head));
        int source = 1, sink = n;
        for(int i = 0; i < m; i++) {
        	scanf("%d %d %d", &x, &y, &v);
        	addEdge(x, y, v);
        }
        printf("Case %d: ", ++cases);
        int maxflow = maxflowDinic(source, sink);
        if (maxflow >= c || c == 0)
        	puts("possible");
        else {
        	vector<int> cut = maxflowCut(source, sink, n);
        	vector< pair<int, int> > ret;
        	for (int i = 1; i <= n; i++) {
        		for (int j = head[i]; j != -1; j = edge[j].next)
        			edge[j].cap -= edge[j].flow;
        	}
        	for (int i = 0; i < cut.size(); i++) {
        		clearflow(n);
        		int x = cut[i], aug;
        		edge[x].cap += c;
        		aug = maxflowDinic(source, sink);
        		if (maxflow + aug >= c)
        			ret.push_back(make_pair(edge[x].x, edge[x].y));
        		edge[x].cap -= c;
        	}
        	if (ret.size() == 0)
        		puts("not possible");
        	else {
        		sort(ret.begin(), ret.end());
        		printf("possible option:");
        		for (int i = 0; i < ret.size(); i++) {
        			if (i)	printf(",");
        			printf("(%d,%d)", ret[i].first, ret[i].second);
        		}
        		puts("");
        	}
        }
    }
    return 0;
}
/*
4 4 5
1 2 5
1 3 5
2 4 5
3 4 5
4 4 5
1 2 1
1 3 5
2 4 5
3 4 1
4 4 5
1 2 1
1 3 1
2 4 1
3 4 1
0 0 0
*/
