#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
using namespace std;
#define INF 0x3f3f3f3f
struct Node {
    int x, y, v;// x->y, v
    int next;
} edge[100005];
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
            int flow = INF, bottleneck;
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
//	freopen("in.txt", "r+t", stdin);
    int n, m, q;
    int testcase;
    char receptacle[105][105], plug[105][105];
    char pin[105][105], pout[105][105];
    scanf("%d", &testcase);
    while(testcase--) {
        e = 0;
        memset(head, -1, sizeof(head));
        
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
        	scanf("%s", receptacle[i]);
        scanf("%d", &m);
        for(int i = 0; i < m; i++)
        	scanf("%*s %s", plug[i]);
        scanf("%d", &q);
        for(int i = 0; i < q; i++)
        	scanf("%s %s", pin[i], pout[i]);
        	
        int source = n + m + q + 1, sink = source + 1;
        for(int i = 0; i < m; i++) {
            addEdge(source, n + i, 1);
            for(int j = 0; j < q; j++)
            	if(!strcmp(plug[i], pin[j]))
            		addEdge(n + i, n + m + j, INF);
        	
            for(int j = 0; j < n; j++)
            	if(!strcmp(plug[i], receptacle[j]))
            		addEdge(n + i, j, 1);
        }
        
        for(int i = 0; i < q; i++) {        	
            for(int j = 0; j < n; j++)
            	if(!strcmp(pout[i], receptacle[j]))
            		addEdge(n + m + i, j, INF);
            
            for(int j = 0; j < q; j++)
            	if(i != j && !strcmp(pout[i], pin[j]))
            		addEdge(n + m + i, n + m + j, INF);
        }

		for(int i = 0; i < n; i++)
			addEdge(i, sink, 1);
        int ret = maxflowDinic(source, sink);
        printf("%d\n", m - ret);
        
        if(testcase)
        	puts("");
    }
    return 0;
} 
