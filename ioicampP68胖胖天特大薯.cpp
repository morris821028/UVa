#include <stdio.h>
#include <string.h>
#include <queue>
#include <deque>
using namespace std;
struct Node {
    int x, y, cap;
	long long cost;// x->y, v
    int next;
};
Node edge[1000005];
int e, head[300005], prevNode[300005], record[300005], inq[300005];
long long dis[300005];
void addEdge(int x, int y, int cap, long long cost) {
    edge[e].x = x, edge[e].y = y, edge[e].cap = cap, edge[e].cost = cost;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].cap = 0, edge[e].cost = -cost;
    edge[e].next = head[y], head[y] = e++;
}
long long mincost(int s, int t, long long special) {
    long long mncost = 0;
	int flow, totflow = 0;
    int i, x, y;
    while(1) {
        memset(dis, 63, sizeof(dis));
        long long oo = dis[0];
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
                    prevNode[y] = x, record[y] = i;
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
        if(mncost + dis[t] > special)
        	break;
        flow = oo;
        for(x = t; x != s; x = prevNode[x]) {
            int ri = record[x];
            flow = min(flow, edge[ri].cap);
        }
        for(x = t; x != s; x = prevNode[x]) {
            int ri = record[x];
            edge[ri].cap -= flow;
            edge[ri^1].cap += flow;
            edge[ri^1].cost = -edge[ri].cost;
        }
        totflow += flow;
        mncost += dis[t] * flow;
    }
    printf("%d\n", totflow);
    return mncost;
}
 
int main() {
	int testcase;
	int N, K, D, C;
	int i, j, k;
	long long M;
	scanf("%d", &testcase);
	while(testcase--) {
		e = 0; 
		memset(head, -1, sizeof(head));
		scanf("%d %d %lld", &N, &K, &M);
		int source = 0, sink = 1, Dnode = 2;
		for(i = 1; i <= N; i++) {
			scanf("%d %d", &C, &D);
			addEdge(source, 3*i, 1, 0);
			addEdge(3*i, 3*i+1, 1, D);
			addEdge(3*i, 3*i+2, 1, C);
			addEdge(3*i+1, Dnode, 1, 0);
			addEdge(3*i+2, sink, 1, 0);
		}
		addEdge(Dnode, sink, K, 0);
		mincost(source, sink, M);
	}
	return 0;
}
