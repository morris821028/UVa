#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
struct Node {
    int x, y, v;// x->y, v
    int next;
} edge[500005];
int e, head[500], dis[500], prev[500], record[500];
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
    int t, n, m;
    int i, j;
    char g[105][105];
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)
            scanf("%s", g[i]);
        int st = 0, ed = n*m+1;
        //g[i][j] = i*m+j+1
        e = 0;
        memset(head, -1, sizeof(head));
        int cntNode = 0;
        for(i = 0; i < n;  i++) {
            for(j = 0; j < m; j++) {
                if(g[i][j] == '*')
                    cntNode++;
                if((i+j)%2 && g[i][j] == '*') {
                    addEdge(st, i*m+j+1, 1);
                    if(i-1 >= 0 && g[i-1][j] == '*')
                        addEdge(i*m+j+1, (i-1)*m+j+1, 1);
                    if(j-1 >= 0 && g[i][j-1] == '*')
                        addEdge(i*m+j+1, i*m+j-1+1, 1);
                    if(i+1 < n && g[i+1][j] == '*')
                        addEdge(i*m+j+1, (i+1)*m+j+1, 1);
                    if(j+1 < m && g[i][j+1] == '*')
                        addEdge(i*m+j+1, i*m+j+1+1, 1);
                }
                if((i+j)%2 == 0 && g[i][j] == '*') {
                    addEdge(i*m+j+1, ed, 1);
                }
            }
        }
        int flow = maxflow(st, ed);
        printf("%d\n", (cntNode-2*flow)+flow);
    }
    return 0;
}
