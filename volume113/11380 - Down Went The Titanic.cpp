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
} edge[100005];
int e, head[2048], prev[2048], record[2048];
int level[2048], visited[2048];
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
#define INF 0x3f3f3f3f
int main() {
	int X, Y, P;
	char g[32][32];
    while(scanf("%d %d %d", &X, &Y, &P) == 3) {
        e = 0;
        memset(head, -1, sizeof(head));
        int source = X * Y * 2 + 1, sink = source + 1;
        for(int i = 0; i < X; i++)
        	scanf("%s", g[i]);
        const int dx[] = {0, 0, 1, -1};
        const int dy[] = {1, -1, 0, 0};
        int x, y, tx, ty;
        for(int i = 0; i < X; i++) {
        	for(int j = 0; j < Y; j++) {
        		if(g[i][j] == '~')
        			continue;
        		for(int k = 0; k < 4; k++) {
        			tx = i + dx[k], ty = j + dy[k];
        			if(tx < 0 || ty < 0 || tx >= X || ty >= Y)
        				continue;
        			if(g[tx][ty] == '~')
        				continue;
        			x = (i * Y + j) * 2 + 1;
        			y = (tx * Y + ty) * 2;
        			addEdge(x, y, INF);
        		}
        		x = (i * Y + j) * 2;
        		y = (i * Y + j) * 2 + 1;
        		if(g[i][j] == '*')
        			addEdge(source, x, 1), addEdge(x, y, 1);
        		else if(g[i][j] == '.')
        			addEdge(x, y, 1);
        		else if(g[i][j] == '@')
        			addEdge(x, y, INF);
        		else if(g[i][j] == '#')
        			addEdge(x, y, INF), addEdge(y, sink, P);
        	}
        }
        int ret = maxflowDinic(source, sink);
        printf("%d\n", ret);
    }
    return 0;
}
