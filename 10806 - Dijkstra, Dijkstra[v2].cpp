#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
struct Node {
    int x, y, cap, cost;// x->y, v
    int next;
} edge[500005];
int e, head[500], dis[500], prev[500], record[500], inq[500];
void addEdge(int x, int y, int cap, int cost) {
    edge[e].x = x, edge[e].y = y, edge[e].cap = cap, edge[e].cost = cost;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].cap = 0, edge[e].cost = -cost;
    edge[e].next = head[y], head[y] = e++;
}
int mincost(int s, int t) {
    int mncost = 0, flow, totflow = 0;
    int i, x, y;
    while(1) {
        memset(dis, 63, sizeof(dis));
        int oo = dis[0];
        dis[s] = 0;
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            x = Q.front(), Q.pop();
            inq[x] = 0;
            for(i = head[x]; i != -1; i = edge[i].next) {
                y = edge[i].y;
                if(edge[i].cap > 0 && dis[y] > dis[x] + edge[i].cost) {
                    dis[y] = dis[x] + edge[i].cost;
                    prev[y] = x, record[y] = i;
                    if(inq[y] == 0) {
                        inq[y] = 1;
                        Q.push(y);
                    }
                }
            }
        }
        if(dis[t] == oo)
            break;
        flow = oo;
        for(x = t; x != s; x = prev[x]) {
            int ri = record[x];
            flow = min(flow, edge[ri].cap);
        }
        for(x = t; x != s; x = prev[x]) {
            int ri = record[x];
            edge[ri].cap -= flow;
            edge[ri^1].cap += flow;
            edge[ri^1].cost = -edge[ri].cost;
        }
        totflow += flow;
        mncost += dis[t] * flow;
    }
    if(totflow != 2)
        puts("Back to jail");
    else
        printf("%d\n", mncost);
    return mncost;
}
int main() {
    int n, m, x, y, v;
    while(scanf("%d %d", &n, &m) == 2 && n) {
        e = 0;
        memset(head, -1, sizeof(head));
        while(m--) {
            scanf("%d %d %d", &x, &y, &v);
            addEdge(x, y, 1, v);
            addEdge(y, x, 1, v);
        }
        addEdge(0, 1, 2, 0);
        addEdge(1, 0, 2, 0);
        addEdge(n, n+1, 2, 0);
        addEdge(n+1, n, 2, 0);
        int ans = mincost(0, n+1);
    }
    return 0;
}
