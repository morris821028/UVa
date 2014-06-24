#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
struct Node {
    int x, y, v;// x->y, v
    int next;
} edge[50005];
int e, head[1005], dis[1005], prev[1005], record[1005];
void addEdge(int x, int y, int v) {
    edge[e].x = x, edge[e].y = y, edge[e].v = v;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].v = 0;
    edge[e].next = head[y], head[y] = e++;
}
int maxflow(int s, int t) {
    int flow = 0;
    int i, j, x, y;
    while(1) {
        memset(dis, 0, sizeof(dis));
        dis[s] =  0xffff; // oo
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            x = Q.front();
            Q.pop();
            for(i = head[x]; i != -1; i = edge[i].next) {
                y = edge[i].y;
                if(dis[y] == 0 && edge[i].v > 0) {
                    prev[y] = x, record[y] = i;
                    dis[y] = min(dis[x], edge[i].v);
                    Q.push(y);
                }
            }
            if(dis[t])  break;
        }
        if(dis[t] == 0) break;
        flow += dis[t];
        for(x = t; x != s; x = prev[x]) {
            int ri = record[x];
            edge[ri].v -= dis[t];
            edge[ri^1].v += dis[t];
        }
    }
    return flow;
}
int main() {
    int n, m;
    int cases = 0, testcase;
    int i, j, k, x, y;
    scanf("%d", &testcase);
    while(testcase--) {
    	scanf("%d %d", &n, &m);
        e = 0;
        memset(head, -1, sizeof(head));
        int S = 1, T = n + m + 1;
        int w[30][30] = {};
        for(i = 1; i <= n; i++) {
        	scanf("%d", &x);
        	for(j = 0; j < x; j++)
        		scanf("%d", &y), w[i][y]++;
        }
        for(int j = 1; j <= m; j++)
        	addEdge(S, n+j, w[1][j]), addEdge(n+j, T, 1);
        for(int i = 2; i <= n; i++) {
        	for(j = 1; j <= m; j++) {
        		if(w[i][j] > 1)
        			addEdge(i, n+j, w[i][j] - 1);
        		else if(w[i][j] == 0)
        			addEdge(n+j, i, 1);
        	}
        }
        int flow = maxflow(S, T);
        printf("Case #%d: %d\n", ++cases, flow);
    }
    return 0;
}
