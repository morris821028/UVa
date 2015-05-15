#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <functional>
#include <deque>
#include <assert.h>
#include <algorithm>
using namespace std;
#define eps 1e-8
#define MAXN 131072
#define MAXM (1048576<<2)
struct Node {
    int x, y, cap;
    int cost;// x->y, v
    int next;
} edge[MAXM];
int e, head[MAXN], pre[MAXN], record[MAXN], inq[MAXN];
int dis[MAXN];
void addEdge(int x, int y, int cap, int cost) {
    assert(x < MAXN && y < MAXN && e < MAXM);
    edge[e].x = x, edge[e].y = y, edge[e].cap = cap, edge[e].cost = cost;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].cap = 0, edge[e].cost = -cost;
    edge[e].next = head[y], head[y] = e++;
}
int mincost(int s, int t, int n) {
    int mncost = 0;
    int flow, totflow = 0;
    int i, x, y;
    int oo = 0x3f3f3f3f;
    while (1) {
        for (int i = 0; i <= n; i++)
            dis[i] = oo;
        dis[s] = 0;
        deque<int> Q;
        Q.push_front(s);
        while (!Q.empty()) {
            x = Q.front(), Q.pop_front();
            inq[x] = 0;
            for (i = head[x]; i != -1; i = edge[i].next) {
                y = edge[i].y;
                if (edge[i].cap > 0 && dis[y] > dis[x] + edge[i].cost) {
                    dis[y] = dis[x] + edge[i].cost;
                    pre[y] = x, record[y] = i;
                    if (inq[y] == 0) {
                        inq[y] = 1;
                        if (Q.size() && dis[Q.front()] > dis[y])
                            Q.push_front(y);
                        else
                            Q.push_back(y);
                    }
                }
            }
        }
        if (dis[t] == oo)
            break;
        flow = 0x3f3f3f3f;
        for (x = t; x != s; x = pre[x]) {
            int ri = record[x];
            flow = min(flow, edge[ri].cap);
        }
        for (x = t; x != s; x = pre[x]) {
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
    int testcase, N, S[1024], E[1024];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        
        int A[128] = {}, B[128] = {};
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &S[i], &E[i]);
            for (int j = S[i]; j <= E[i]; j++)
                A[j]++;
        }
        
        e = 0;
        memset(head, -1, sizeof(head));
        
        for (int i = 1; i <= 100; i++)
            B[i] = B[i-1] + A[i];
//        printf("%d\n", A[100]);
        int source = N + B[100] + 1, sink = N + B[100] + 2;
//        printf("source %d sink %d\n", source, sink);
        for (int i = 1; i <= 100; i++) {
//            printf("---- %d\n", A[i]);
            for (int j = 0, lj = B[i-1]; j < A[i]; j++, lj++) {
                addEdge(N + lj, sink, 1, j * 2 + 1);
                assert(N + lj < source);
//                printf("%d %d\n", N + lj, sink);
            }
        }
        for (int i = 0; i < N; i++) {
            addEdge(source, i, 1, 0);
            for (int j = S[i]; j <= E[i]; j++) {
                for (int k = 0, lk = B[j-1]; k < A[j]; k++, lk++) {
                    addEdge(i, N + lk, 1, 0);
                }
            }
        }
        
        int ret = mincost(source, sink, sink + 1);
        printf("%d\n", ret);
    }
    return 0;
}
/*
999
10
46 89
34 51
72 94
8 12
3 66
36 63
2 69
2 3
22 43
90 93 
*/ 
/*
 4
 3 
 1 3 
 1 3
 1 3
 3 
 2 3 
 1 2 
 1 2 
 5 
 2 3 
 1 2 
 1 2 
 3 3
 3 3 
 6 
 2 3
 1 2
 1 2
 3 3
 3 3
 2 3
*/
