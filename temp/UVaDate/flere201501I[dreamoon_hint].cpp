#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <functional>
#include <deque>
#include <assert.h>
#include <algorithm>
using namespace std;
#define MAXN 2048
#define MAXM (526244)
struct Node {
    int x, y, cap;
    int cost;// x->y, v
    int next, sp;
} edge[MAXM];
int e, head[MAXN], pre[MAXN], record[MAXN], inq[MAXN];
int dis[MAXN];
void addEdge(int x, int y, int cap, int cost, int sp) {
    assert(x < MAXN && y < MAXN && e < MAXM);
    if (sp == 0) {
    	edge[e].x = x, edge[e].y = y, edge[e].cap = cap, edge[e].cost = cost;
    	edge[e].sp = 0, edge[e].next = head[x], head[x] = e++;
    	edge[e].x = y, edge[e].y = x, edge[e].cap = 0, edge[e].cost = -cost;
    	edge[e].sp = 0, edge[e].next = head[y], head[y] = e++;
	} else {
		edge[e].x = x, edge[e].y = y, edge[e].cap = cap, edge[e].cost = cost;
    	edge[e].sp = sp, edge[e].next = head[x], head[x] = e++;
    	edge[e].x = y, edge[e].y = x, edge[e].cap = cap, edge[e].cost = -cost;
    	edge[e].sp = -sp, edge[e].next = head[y], head[y] = e++;
	}
}

int pass[MAXN];
int f(Node &e) {
	if (e.sp == 0)
		return e.cost;
	if (e.sp == 1)
		return e.cost * pass[e.x] * 2 + 1;
	if (e.sp == -1) {
		if (pass[e.y] == 0)
			return 0x3f3f3f3f;
		return -(e.cost * pass[e.y] * 2 + 1);
	}
	assert(false);
}
int mincost(int s, int t, int n) {
    int mncost = 0;
    int flow, totflow = 0, x, y;
    int INF = 0x3f3f3f3f;
    for (int i = 0; i < n; i++)
    	pass[i] = 0;
    while (1) {
        for (int i = 0; i <= n; i++)
            dis[i] = INF;
        dis[s] = 0;
        deque<int> Q;
        Q.push_front(s);
        while (!Q.empty()) {
            x = Q.front(), Q.pop_front();
            inq[x] = 0;
            for (int i = head[x]; i != -1; i = edge[i].next) {
                y = edge[i].y;
                int ecost = f(edge[i]);
                if (edge[i].cap > 0 && dis[y] > dis[x] + ecost) {
                    dis[y] = dis[x] + ecost;
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
        if (dis[t] == INF)
            break;
        flow = INF;
        for (x = t; x != s; x = pre[x]) {
            int ri = record[x];
            flow = min(flow, edge[ri].cap);
        }
        for (x = t; x != s; x = pre[x]) {
            int ri = record[x];
            if (edge[ri].sp == 0)
            	edge[ri].cap -= flow;
            if (edge[ri^1].sp == 0)
            	edge[ri^1].cap += flow;
            	
        	if (edge[ri].sp == 1)
        		pass[edge[ri].x] ++;
        	if (edge[ri].sp == -1)
        		pass[edge[ri].y] --;
        }
        // printf("%d --\n", dis[t]);
        totflow += flow;
        mncost += dis[t] * flow;
    }
    return mncost;
}

const int MAXD = 105;
int main() {
    int testcase, N, S[1024], E[1024];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        
        for (int i = 0; i < N; i++)
            scanf("%d %d", &S[i], &E[i]);
        
        e = 0;
        memset(head, -1, sizeof(head));
        
        int source = N + MAXD + 2, sink = N + MAXD + 3;

        for (int i = 0; i < N; i++) {
            addEdge(source, i, 1, 0, 0);
            for (int j = S[i]; j <= E[i]; j++)
            	addEdge(i, N + j, 1, 0, 0);
        }
        
        for (int i = 1; i < MAXD; i++)
        	addEdge(N + i, sink, 1, 1, 1);
        
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
