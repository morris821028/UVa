#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 128
struct Node {
    int x, y, cap, cost;// x->y, v
    int next;
} edge[100005];
int e, head[MAXN], dis[MAXN], pre[MAXN], record[MAXN], inq[MAXN];
void addEdge(int x, int y, int cap, int cost) {
    edge[e].x = x, edge[e].y = y, edge[e].cap = cap, edge[e].cost = cost;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].cap = 0, edge[e].cost = -cost;
    edge[e].next = head[y], head[y] = e++;
}
int mincost(int s, int t, int &totflow) {
    totflow = 0;
    int mncost = 0, flow;
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
                    pre[y] = x, record[y] = i;
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
        for(x = t; x != s; x = pre[x]) {
            int ri = record[x];
            flow = min(flow, edge[ri].cap);
        }
        for(x = t; x != s; x = pre[x]) {
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
    int testcase, N, M, K;
    int x, y, v;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d %d", &N, &M, &K);
        e = 0;
        memset(head, -1, sizeof(head));
        int source = 2 * N, sink = 2 * N + 1;
        for (int i = 0; i < M; i++) {
            scanf("%d %d %d", &x, &y, &v);
            addEdge(2 * x, 2 * y + 1, 1, v);
        }
        
        for (int i = 0; i < N; i++) {
            addEdge(source, 2 * i, K, 0);
            addEdge(2 * i + 1, sink, K, 0);
        }
        int flow = 0;
        int cost = mincost(source, sink, flow);
        if (flow != N * K)
            puts("-1");
        else
            printf("%d\n", cost);
    }
    return 0;
}

/*
 4
 4 8 1
 0 1 1
 1 0 2
 2 3 1
 3 2 2
 0 2 5
 2 0 6
 1 3 5
 3 1 6
 
 4 8 1
 0 1 1
 1 0 10
 2 3 10
 3 2 1
 0 2 10
 2 0 1
 1 3 1
 3 1 10
 
 4 8 2
 0 1 1
 1 0 2
 2 3 1
 3 2 2
 0 2 5
 2 0 6
 1 3 5
 3 1 6
 
 3 4 1
 0 1 5
 1 0 6
 0 2 7
 2 0 8
 */