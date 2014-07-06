#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <vector>
using namespace std;
struct Node {
    int x, y, v, cap;// x->y, v
    int next;
} edge[100005];
int e, head[505], prev[505], record[505];
int level[505], visited[505];
void addEdge(int x, int y, int v) {
    edge[e].x = x, edge[e].y = y, edge[e].cap = edge[e].v = v;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].cap = edge[e].v = 0;
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
void recoverFlow() {
	for(int i = 0; i < e; i++)
		edge[i].v = edge[i].cap;
}
int main() {
    int testcase, N;
    int x[105], y[105], n[105], m[105];
    double D;
    scanf("%d", &testcase);
    while(testcase--) {
        e = 0;
        memset(head, -1, sizeof(head));
        scanf("%d %lf", &N, &D);
        int source = 2 * N + 1, sink;
        int tot = 0;
        for(int i = 0; i < N; i++) {
        	scanf("%d %d %d %d", &x[i], &y[i], &n[i], &m[i]);
        	addEdge(source, i, n[i]);
        	addEdge(i, N + i, m[i]);
        	tot += n[i];
        }
#define INF 0x3f3f3f3f
        for(int i = 0; i < N; i++) {
        	for(int j = 0; j < N; j++) {
        		if(i != j && (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]) <= D*D)
        			addEdge(N + i, j, INF), addEdge(N + j, i, INF);
        	}
        }
        vector<int> ret;
        for(int i = 0; i < N; i++) {
        	recoverFlow();
        	sink = i;
        	int f = maxflowDinic(source, sink);
        	if(f == tot) {
        		ret.push_back(i);
        	}        	
        }
        if(ret.size() == 0)
        	puts("-1");
        else {
        	printf("%d", ret[0]);
        	for(int i = 1; i < ret.size(); i++)
        		printf(" %d", ret[i]);
        	puts("");
        }
    }
    return 0;
}
/*
2
5 3.5
1 1 1 1
2 3 0 1
3 5 1 1
5 1 1 1
5 4 0 1
3 1.1
-1 0 5 10
0 0 3 9
2 0 1 1
*/
