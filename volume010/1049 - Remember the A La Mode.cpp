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

int readDouble() {
	static char s[16];
	scanf("%s", s);
	if (s[0] == '-')	return -1;
	int i, x = 0;
	for (i = 0; s[i] && s[i] != '.'; i++)
		x = x * 10 + s[i] - '0';
	if (!s[i])	return x * 100;
	i++;
	x = x * 10 + s[i] - '0';
	if(!s[i+1]) return x * 10;
	i++;
	x = x * 10 + s[i] - '0';
	return x;
}
int main() {
    int N, M, Nsz[64], Msz[64], cases = 0;
    int NMp[64][64];
    while (scanf("%d %d", &N, &M) == 2 && N) {
    	
  		for (int i = 0; i < N; i++)
            scanf("%d", &Nsz[i]);
        for (int i = 0; i < M; i++)
        	scanf("%d", &Msz[i]);
        for (int i = 0; i < N; i++)
        	for (int j = 0; j < M; j++)
        		NMp[i][j] = readDouble();
        	
        int source = N + M, sink = N + M + 1;
        g.init(N + M + 2);
        for (int i = 0; i < N; i++) 
        	g.Addedge(source, i, Nsz[i], 0);
        for (int i = 0; i < M; i++) 
        	g.Addedge(i + N, sink, Msz[i], 0);
        for (int i = 0; i < N; i++) {
        	for (int j = 0; j < M; j++) {
        		if (NMp[i][j] < 0) 	continue;
        		g.Addedge(i, j + N, 0x3f3f3f3f, NMp[i][j]);
        	}
        }
        pair<int, int> ret1 = g.mincost(source, sink);
        
        g.init(N + M + 2);
        for (int i = 0; i < N; i++) 
        	g.Addedge(source, i, Nsz[i], 0);
        for (int i = 0; i < M; i++) 
        	g.Addedge(i + N, sink, Msz[i], 0);
        	
        const int ADD = 50 * 100 * 2000;
        for (int i = 0; i < N; i++) {
        	for (int j = 0; j < M; j++) {
        		if (NMp[i][j] < 0) 	continue;
        		g.Addedge(i, j + N, 0x3f3f3f3f, ADD - NMp[i][j]);
        	}
        }
        pair<int, int> ret2 = g.mincost(source, sink);
        double r1, r2;
        r1 = ret1.first / 100.0;
        r2 = (ret2.second * ADD - ret2.first) / 100.0;
        printf("Problem %d: ", ++cases);
 		printf("%.2lf to %.2lf\n", r1, r2);
    }
    return 0;
}
