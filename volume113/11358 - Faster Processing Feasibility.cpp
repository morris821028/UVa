#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
using namespace std;
struct Node {
    int x, y, v;// x->y, v
    int next;
} edge[10005];
int e, head[505], prev[505], record[505];
int level[505], visited[505];
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
int main() {
    int n, m;
    int testcase;
    int i, j, k, x, y;
    int P, T;
    int l[50], r[50], w[50];
    scanf("%d", &testcase);
    while(testcase--) {
    	e = 0;
		memset(head, -1, sizeof(head));
		scanf("%d %d", &P, &T);
		int sum = 0;
		set<int> R;
		for(i = 0; i < T; i++) {
			scanf("%d %d %d", &l[i], &w[i], &r[i]);
			sum += w[i];
			R.insert(l[i]);
			R.insert(r[i]);
		}
		int source = T + R.size() + 1, sink = source + 1;
		for(i = 0; i < T; i++)
			addEdge(source, i, w[i]);
		int node = T;
		for(set<int>::iterator it = R.begin(), jt; 
			it != R.end(); it++) {
			jt = it;
			jt++;
			if(jt == R.end())
				break;
			int work = *jt - *it;
			for(i = 0; i < T; i++)
				if(*it >= l[i] && *it < r[i])
					addEdge(i, node, work);
			addEdge(node, sink, work * P);
			node++;
		}
		int ret = maxflowDinic(source, sink);
		printf("%s\n", ret == sum ? "FEASIBLE" : "NO WAY");
    }
    return 0;
}

