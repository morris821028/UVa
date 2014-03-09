#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
struct Node {
    int x, y, v;// x->y, v
    int next;
} edge[100005];
int e, head[5005], prevNode[5005], record[5005];
int level[5005], visited[5005];
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
                    stk.push(y), prevNode[y] = now, record[y] = i;
                    break;
                }
            }
            if(stk.top() == now)
                stk.pop(), visited[now] = 1;
        } else {
            int flow = 0xfffffff, bottleneck;
            for(int i = t; i != s; i = prevNode[i]) {
                int ri = record[i];
                flow = min(flow, edge[ri].v);
            }
            for(int i = t; i != s; i = prevNode[i]) {
                int ri = record[i];
                edge[ri].v -= flow;
                edge[ri^1].v += flow;
                if(edge[ri].v == 0)
                    bottleneck = prevNode[i];
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
    int n, m, B, D;
    int testcase;
    int i, x, y, v;
    scanf("%d", &testcase);
    while(testcase--) {
        e = 0;
        memset(head, -1, sizeof(head));
    	int source = 0, sink = 1;
    	scanf("%d", &n);
    	for(i = 1; i <= n; i++) {
    		scanf("%d", &v);
    		addEdge(2*i, 2*i+1, v);
    	}
    	scanf("%d", &m);
    	for(i = 0; i < m; i++) {
    		scanf("%d %d %d", &x, &y, &v);
    		addEdge(2*x+1, 2*y, v);
    	}
    	scanf("%d %d", &B, &D);
    	for(i = 0; i < B; i++) {
    		scanf("%d", &x);
    		addEdge(source, 2*x, 0x7f7f7f7f);
    	}
    	for(i = 0; i < D; i++) {
    		scanf("%d", &x);
    		addEdge(2*x+1, sink, 0x7f7f7f7f);
    	}
    	printf("%d\n", maxflowDinic(source, sink));
    }
    return 0;
}
