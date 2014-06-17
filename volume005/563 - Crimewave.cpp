#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
struct Node {
    int x, y, v;// x->y, v
    int next;
} edge[500005];
int e, head[50000], dis[50000], prev[50000], record[50000];
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
    int testcase;
    int n, m, b, x, y;
    int i, j, k;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d %d", &n, &m, &b);
        e = 0;
        memset(head, -1, sizeof(head));
        int dirx[4] = {1,-1,0,0};
        int diry[4] = {0,0,1,-1};
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                int innode = i*m+j+1, outnode = i*m+j+1+n*m;
                addEdge(innode, outnode, 1);
                for(k = 0; k < 4; k++) {
                    x = i+dirx[k], y = j+diry[k];
                    if(x < 0 || y < 0 || x >= n || y >= m)
                        continue;
                    int y_innode = x*m+y+1;
                    addEdge(outnode, y_innode, 0xffff);
                }
            }
        }
        for(i = 0; i < b; i++) {
            scanf("%d %d", &x, &y);
            x--, y--;
            int node = x*m + y + 1;
            addEdge(0, node, 1);
        }
        for(i = 0; i < n; i++) {
            int outnode = i*m+1+n*m;// g[i][0]
            addEdge(outnode, 2*n*m+1, 1);
            outnode = i*m+m-1+1+n*m;// g[i][m-1]
            addEdge(outnode, 2*n*m+1, 1);
        }
        for(i = 1; i < m-1; i++) {
            int outnode = i+1+n*m;// g[0][i]
            addEdge(outnode, 2*n*m+1, 1);
            outnode = (n-1)*m+i+1+n*m;// g[n-1][i]
            addEdge(outnode, 2*n*m+1, 1);
        }
        int flow = maxflow(0, 2*n*m+1);
        if(flow == b)
            puts("possible");
        else
            puts("not possible");
    }
    return 0;
}
/*
n*m, node(g[i][j])
g[i][j] innode : i*m+j+1, outnode : i*m+j+1+n*m
source(0), sink(2*n*m+1);
*/
