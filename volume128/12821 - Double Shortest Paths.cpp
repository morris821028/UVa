#include <stdio.h>
#include <string.h>
#include <queue>
#include <deque>
using namespace std;
struct Node {
    int x, y, cap, cost;// x->y, v
    int next;
} edge[100005];
int e, head[505], dis[505], prev[505], record[505], inq[505];
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
        deque<int> Q;
        Q.push_front(s);
        while(!Q.empty()) {
            x = Q.front(), Q.pop_front();
            inq[x] = 0;
            for(i = head[x]; i != -1; i = edge[i].next) {
                y = edge[i].y;
                if(edge[i].cap > 0 && dis[y] > dis[x] + edge[i].cost) {
                    dis[y] = dis[x] + edge[i].cost;
                    prev[y] = x, record[y] = i;
                    if(inq[y] == 0) {
                        inq[y] = 1;
                        if(Q.size() && dis[Q.front()] > dis[y])
                            Q.push_front(y);
                        else
                            Q.push_back(y);
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
    return mncost;
}
int main() {
    int n, m, cases = 0;
    int x, y, d, a;
    while(scanf("%d %d", &n, &m) == 2) {
        e = 0;
        memset(head, -1, sizeof(head));
        int source = n + 1, sink = n + 2;
        for (int i = 0; i < m; i++) {
        	scanf("%d %d %d %d", &x, &y, &d, &a);
        	addEdge(x, y, 1, d);
        	addEdge(x, y, 1, d + a);
        }
        addEdge(source, 1, 2, 0);
        addEdge(n, sink, 2, 0);
        printf("Case %d: %d\n", ++cases, mincost(source, sink));
    }
    return 0;
}
/*
4 4
1 2 5 1
2 4 6 0
1 3 4 0
3 4 9 1
4 4
1 2 5 10
2 4 6 10
1 3 4 10
3 4 9 10
*/
