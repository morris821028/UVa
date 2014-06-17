#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;
struct Node {
    int x, y, v;// x->y, v
    int next;
} edge[500005];
int e, head[1100], dis[1100], prev[1100], record[1100];
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
    int n, m, x, y;
    int i, j, k;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0)  break;
        e = 0;
        memset(head, -1, sizeof(head));
        int st = 0, ed = n+m+1;
        int Pro = 0;
        for(i = 1; i <= n; i++) {
            scanf("%d", &x);
            addEdge(m+i, ed, x);
            Pro += x;
        }
        for(i = 1; i <= m; i++) {
            scanf("%d", &x);
            while(x--) {
                scanf("%d", &y);
                addEdge(i, m+y, 1);
            }
            addEdge(st, i, 1);
        }
        int flow = maxflow(st, ed);
        if(flow == Pro) {
            puts("1");
            vector<int> res[n];
            for(i = 1; i <= m; i++) {
                for(j = head[i]; j != -1; j = edge[j].next) {
                    if(edge[j].v == 0 && edge[j].y > m) {
                        res[edge[j].y-m-1].push_back(i);
                        break;
                    }
                }
            }
            for(i = 0; i < n; i++) {
                for(j = 0; j < res[i].size(); j++) {
                    if(j)   putchar(' ');
                    printf("%d", res[i][j]);
                }
                puts("");
            }
        } else
            puts("0");
    }
    return 0;
}
