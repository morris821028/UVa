#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 105;
const int MAXM = 8192;
struct Node {
    int x, y, cap, cost;// x->y, v
    int next;
} edge[MAXM];
class MinCost {
public:
	int n;
    int e, head[MAXN], dis[MAXN], pre[MAXN], record[MAXN], inq[MAXN];
    void AddEdge(int x, int y, int cap, int cost) {
        edge[e].x = x, edge[e].y = y, edge[e].cap = cap, edge[e].cost = cost;
        edge[e].next = head[x], head[x] = e++;
        edge[e].x = y, edge[e].y = x, edge[e].cap = 0, edge[e].cost = -cost;
        edge[e].next = head[y], head[y] = e++;
    }
    pair<int, int> mincost(int s, int t) {
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
	    return {mncost, totflow};
	}
    void init(int n) {
        e = 0;
        this->n = n;
        for (int i = 0; i < n; i++)
            head[i] = -1;
    }
} g;

int N, R, C;
int r[MAXN], c[MAXN], p[MAXN], d[MAXN], s[MAXN];
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &N, &C, &R);
		int sumr = 0;
		for (int i = 0; i < N; i++)
			scanf("%d", &r[i]), sumr += r[i];
		for (int i = 0; i < C; i++)
			scanf("%d %d", &c[i], &p[i]);
		for (int i = 0; i < R; i++)
			scanf("%d %d", &d[i], &s[i]);
		int source = 2*N, sink = 2*N+1, sale = 2*N+2;
		g.init(2*N+3);
		for (int i = 0; i < N; i++) {
			g.AddEdge(sale, 2*i+1, sumr, 0);
			g.AddEdge(2*i, 2*(i+1), sumr, 0);

			g.AddEdge(source, 2*i, r[i], 0);
			g.AddEdge(2*i+1, sink, r[i], 0);
		}
		for (int i = 0; i < C; i++)
			g.AddEdge(source, sale, c[i], p[i]);
		for (int i = 0; i < R; i++) {
			for (int j = 0; j+d[i]+1 < N; j++) {
				g.AddEdge(2*j, 2*(j+d[i]+1)+1, sumr, s[i]);
			}
		}
		pair<int, int> ret = g.mincost(source, sink);
		printf("Case %d: ", ++cases);
		if (ret.second == sumr)
			printf("%d\n", ret.first);
		else
			puts("impossible");
	}
	return 0;
}
/*
2
3  2  1
10  20  30
40  90  15  100
1  5
3  2  1
10  20  30
40  90  15  100
2  5
*/
