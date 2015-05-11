// mincost, hard for choose always the one with lower order
#include <stdio.h>
#include <string.h>
#include <queue>
#include <functional>
#include <deque>
#include <algorithm>
using namespace std;
#define MAXN 2048
#define MAXM 1048576
struct Node {
    int x, y, cap;
	int cost;// x->y, v
    int next;
};
const int INF = 0x3f3f3f3f;
class MinCost {
public:
    int e, head[MAXN], pre[MAXN], record[MAXN], inq[MAXN];
    int dis[MAXN];
    int n;    
    Node edge[MAXM];
    void Addedge(int x, int y, int cap, int cost) {
        edge[e].x = x, edge[e].y = y, edge[e].cap = cap, edge[e].cost = cost;
        edge[e].next = head[x], head[x] = e++;
        edge[e].x = y, edge[e].y = x, edge[e].cap = 0, edge[e].cost = -cost;
        edge[e].next = head[y], head[y] = e++;
    }
    pair<int, int> mincost(int s, int t) {
        int mncost = 0;
		int flow, totflow = 0;
        int i, x, y;
        while(1) {
        	for (int i = 0; i < n; i++)
        		dis[i] = INF;
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
            flow = 0x3f3f3f3f;
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
        return make_pair(mncost, totflow);
    }
    void init(int n) {
    	this->n = n;
        e = 0;
        for (int i = 0; i <= n; i++)
            head[i] = -1;
    }
} g;
int main() {
    int testcase, N;
    int type[20][20];
    scanf("%d", &testcase);
    while (testcase--) {
    	scanf("%d", &N);
    	
    	int sum = 0;
    	for (int i = 0; i < N; i++) {
    		for (int j = 0; j < N; j++)
    			scanf("%d", &type[i][j]), sum += type[i][j];
    	}
        	
        int source = N + N, sink = N + N + 1;
        g.init(N + N + 2);
        for (int i = 0; i < N; i++) 
        	g.Addedge(source, i, 1, 0);
        for (int i = 0; i < N; i++) 
        	g.Addedge(N+i, sink, 1, 0);
			        	
        const int ADD = 50 * 100 * 2000;
        for (int i = 0; i < N; i++) {
        	for (int j = 0; j < N; j++) {
        		g.Addedge(i, j + N, 1, ADD - type[i][j]);
        	}
        }
        
        pair<int, int> ret = g.mincost(source, sink);
        int mn = ret.second * ADD - ret.first;
        int f[16] = {};
        for (int i = 0; i < N; i++) {
        	for (int j = g.head[i]; j != -1; j = g.edge[j].next) {
        		if (g.edge[j].cap == 0 && g.edge[j].y >= N && g.edge[j].y < N + N) {
        			int remain = g.edge[j].y - N;
        			f[i] = remain;
        		}
        	}
        }
        for (int i = 0; i < N; i++)
        	printf("%d", f[i]);
 		printf(" %d\n", sum - mn);
    }
    return 0;
}
/*
4
3 2 3 4 0 0 2 1 3 1
3 66 66 0 66 66 0 66 66 66
6 476 357 874 50 594 394 320 803 817 348 252 940 453 500 647 299
94 143 800 947 561 885 389 172 301 276 612 130 540 731 774 306 96
239 227 907
2 99 1 1 99
*/
