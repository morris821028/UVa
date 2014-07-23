#include <stdio.h>
#include <string.h>
#include <queue>
#include <deque>
using namespace std;
struct Node {
    int x, y;
	long long cap, cost;// x->y, v
    int next;
} edge[262144];
int e, head[512], prev[512], record[512], inq[512];
long long dis[512];
void addEdge(int x, int y, long long cap, long long cost) {
    edge[e].x = x, edge[e].y = y, edge[e].cap = cap, edge[e].cost = cost;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].cap = 0, edge[e].cost = -cost;
    edge[e].next = head[y], head[y] = e++;
}
long long mincost(int s, int t) {
    long long mncost = 0, flow, totflow = 0;
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
        if(dis[t] > 0)	break;
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
    int testcase, cases = 0;
    int M, I;
    int pm[128], pn[128], pp[128], ps[128], pe[128];
    scanf("%d", &testcase);
    while(testcase--) {
    	scanf("%d %d", &M, &I);
    	e = 0;
        memset(head, -1, sizeof(head));
        
        int source = 2 * M + 2, sink = source + 1;
        for(int i = 1; i <= M; i++)
        	scanf("%d %d %d %d %d", pm+i, pn+i, pp+i, ps+i, pe+i);
#define INF 0x3f3f3f3f
        for(int i = 1; i <= M; i++) {
        	addEdge(source, 2*i, pn[i], pm[i]);
        	for(int j = i; j <= min(i + pe[i], M); j++)
        		addEdge(2*i, 2*j+1, INF, (j - i) * I);
        	addEdge(2*i+1, sink, ps[i], -pp[i]);
        }
        
        printf("Case %d: %lld\n", ++cases, -mincost(source, sink));
    }
    return 0;
}
