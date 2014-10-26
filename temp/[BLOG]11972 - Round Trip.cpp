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
	int cap, flow;// x->y, v
    int next;
} edge[10005];
int e, head[MAXN], prev[MAXN], record[MAXN];
int level[MAXN], visited[MAXN];
void addEdge(int x, int y, int v) {
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
            int flow = 0x3f3f3f3f, bottleneck;
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
int clearflow() {
	for (int i = 0; i < e; i++)
		edge[i].flow = 0;
}
int main() {
    int n, m, c;
    int x, y, v;
    int cases = 0;
    int testcase;
    scanf("%d", &testcase);
    while(testcase--) {
    	scanf("%d %d %d", &n, &m, &c);
        e = 0;
        memset(head, -1, sizeof(head));
        for(int i = 0; i < m; i++) {
        	scanf("%d %d", &x, &y);
        	addEdge(x, y, 1);
        	addEdge(y, x, 1);
        }
        printf("Case %d: ", ++cases);
        int f = 0;
        for (int i = 1; i <= n; i++) {
        	if (i == c)	continue;
        	clearflow();
        	int flow = maxflowDinic(c, i);
        	if (flow >= 2) {
        		if (f)	putchar(' ');
        		printf("%d", i);
        		f = 1;
        	}
        }
        if (f == 0)
        	puts("none");
        else
        	puts("");
    }
    return 0;
}
/*
2
6 7 1
1 2
1 3
2 6
4 6
2 5
5 3
4 2
2 1 2
1 2
*/

