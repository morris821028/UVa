#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
using namespace std;
#define MAXN 8192
struct Node {
    int x, y, v;// x->y, v
    int next;
} edge[1048576 * 4];
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

int channel[300005];
int main() {
	int testcase, cases = 0, n, m;
	char line[1024];
	scanf("%d", &testcase);
    while(testcase--) {
        e = 0;
        memset(head, -1, sizeof(head));
        scanf("%d", &n);
        while(getchar() != '\n');
        int source = n + 3001, sink = n + 3002;
        int price, sum = 0;
        char cc;
        memset(channel, 0, sizeof(channel));
        for (int i = 0; i < n; i++) {
        	scanf("%d", &price);
        	int x;
        	while (scanf("%d%c", &x, &cc) == 2)  {
        		channel[x] = i+1;
        		if (cc == '\n')
        			break;
        	}
        	addEdge(source, i, price);
        	sum += price;
        }
        scanf("%d", &m);
        while(getchar() != '\n');
        for (int i = 0; i < m; i++) {
        	scanf("%d", &price);
        	int x;
        	set<int> ch;
        	while (scanf("%d%c", &x, &cc) == 2) {
        		if (channel[x])
        			ch.insert(channel[x] - 1);
        		if (cc == '\n')
        			break;
        	}
        	for (set<int>::iterator it = ch.begin();
				it != ch.end(); it++) {
        		addEdge(*it, i+n, 1e+9);
        	}
        	addEdge(i+n, sink, price);
        	sum += price;
        }
        printf("Case %d:\n", ++cases);
        int mincut = maxflowDinic(source, sink);
        printf("%d\n", sum - mincut);
        if (testcase)
        	puts("");
    }
    return 0;
}
