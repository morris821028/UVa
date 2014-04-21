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
} edge[65536];
int e, head[6500], prev[6500], record[6500];
int level[6500], visited[6500];
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
    int testcase, cases = 0;
    int i, j, k, x, y;
    char g[128][128];
    int id[128][128];
    scanf("%d", &testcase);
    while(testcase--) {
        e = 0;
        memset(head, -1, sizeof(head));
        scanf("%d %d", &n, &m);
        for(int i = 0; i < n; i++)
        	scanf("%s", g[i]);
        int ST[2] = {0, 0};
        for(int i = 0; i < n; i++) {
        	for(int j = 0; j < m; j++) {
        		if(g[i][j] == '.') {
        			id[i][j] = ST[j&1]++;
        		} else {
        			id[i][j] = -1;
        		}
        	}
		} 
		int source = ST[0] + ST[1];
		int sink = source + 1;
		for(int i = 0; i < ST[0]; i++)
			addEdge(source, i, 1);
		for(int i = 0; i < ST[1]; i++)
			addEdge(i + ST[0], sink, 1);
		int dx[] = {-1, -1, 0, 0, 1, 1};
		int dy[] = {-1, 1, -1, 1, 1, -1};
		int tx, ty, u, v;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j += 2) {
				if(id[i][j] == -1)	
					continue;
				v = id[i][j];
				for(int k = 0; k < 6; k++) {
					tx = i + dx[k];
					ty = j + dy[k];
					if(tx < 0 || ty < 0 || tx >= n || ty >= m)
						continue;
					u = id[tx][ty];
					if(u == -1)
						continue;
					addEdge(v, u + ST[0], 1);
				}
			}
		}
        int ret = maxflowDinic(source, sink);
        printf("Case #%d: %d\n", ++cases, ST[0] + ST[1] - ret);
    }
    return 0;
}
