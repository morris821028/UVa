#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <iostream>
#include <sstream>
using namespace std;

#define MAXN 1505
#define MAXM 1048576
struct Node {
    int x, y, v;// x->y, v
    int next;
} edge[MAXM];
int e, head[MAXN], prev[MAXN], record[MAXN];
int level[MAXN], visited[MAXN];
void addEdge(int x, int y, int v) {
    edge[e].x = x, edge[e].y = y, edge[e].v = v;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].v = 0;
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
            if(edge[i].v > 0 && level[y] == 0) {
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
                if(edge[i].v > 0) {
                    stk.push(y), prev[y] = now, record[y] = i;
                    break;
                }
            }
            if(stk.top() == now)
                stk.pop(), visited[now] = 1;
        } else {
            int flow = 1e+9, bottleneck;
            for(int i = t; i != s; i = prev[i]) {
                int ri = record[i];
                flow = min(flow, edge[ri].v);
            }
            for(int i = t; i != s; i = prev[i]) {
                int ri = record[i];
                edge[ri].v -= flow;
                edge[ri^1].v += flow;
                if(edge[ri].v == 0)
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
vector<int> g[MAXN];
int test(int n, int m, int limit) {
	e = 0;
    memset(head, -1, sizeof(head));
	int source = n + m + 1, sink = n + m + 2;
	for (int i = 0; i < n; i++)
		addEdge(source, i, 1);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < g[i].size(); j++)
			addEdge(i, n + g[i][j], 1);
	for (int i = 0; i < m; i++)
		addEdge(n + i, sink, limit);
	return maxflowDinic(source, sink) == n;
}
int main() {
	int n, m, x;
	string foo;
	char line[32767];
	while (scanf("%d %d", &n, &m) == 2 && n+m) {
		while (getchar() != '\n');
		
		int used[512] = {};
		for (int i = 0; i < n; i++) {
			gets(line);
			stringstream sin(line);
			sin >> foo;
			g[i].clear();
			while (sin >> x)
				g[i].push_back(x), used[x]++;
		}
		
		int l = 0, r = 0, mid;
		int ret = 0;
		for (int i = 0; i < m; i++)
			r = max(r, used[i]);
		while (l <= r) {
			mid = (l + r)/2;
			if (test(n, m, mid))
				r = mid - 1, ret = mid;
			else
				l = mid + 1;
		}
		printf("%d\n", ret);
	}
	return 0;
}
