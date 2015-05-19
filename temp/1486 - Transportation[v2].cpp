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
	double cost;// x->y, v
    int next;
} edge[MAXM];
class MinCost {
public:
    int e, head[MAXN], pre[MAXN], record[MAXN], inq[MAXN];
    int dis[MAXN];
    int n;
    const int INF = 0x3f3f3f3f;
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
    int N, M, K, u, v, a, c;
    while (scanf("%d %d %d", &N, &M, &K) == 3) {
    	
    	g.init(N + 1);
        
        int source = 0, sink = N;
        for (int i = 0; i < M; i++) {
        	scanf("%d %d %d %d", &u, &v, &a, &c);
        	for (int j = 1; j <= c; j++)
        		g.Addedge(u, v, 1, a * (j * j - (j-1) * (j-1)));
        }
        
        g.Addedge(source, 1, K, 0);
        
        pair<int, int> ret = g.mincost(source, sink);
        if (ret.second == K)
        	printf("%d\n", ret.first);
        else
        	printf("-1\n");
    }
    return 0;
}
/*
2 1 2 
1 2 1 2 
2 1 2 
1 2 1 1 
2 2 2 
1 2 1 2 
1 2 2 2
*/
