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
    int x, y, cap, cost;// x->y, v
    int next;
} edge[MAXM];
class MinCost {
public:
    int e, head[MAXN], dis[MAXN], pre[MAXN], record[MAXN], inq[MAXN];
    void Addedge(int x, int y, int cap, int cost) {
        edge[e].x = x, edge[e].y = y, edge[e].cap = cap, edge[e].cost = cost;
        edge[e].next = head[x], head[x] = e++;
        edge[e].x = y, edge[e].y = x, edge[e].cap = 0, edge[e].cost = -cost;
        edge[e].next = head[y], head[y] = e++;
    }
    pair<int, int> mincost(int s, int t) {
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
        return make_pair(mncost, totflow);
    }
    void init(int n) {
        e = 0;
        for (int i = 0; i <= n; i++)
            head[i] = -1;
    }
} g;
char s[1024][1024];
int main() {
	int testcase, cases = 0;
    int n, m;
    scanf("%d", &testcase);
    while (testcase--) {
    	scanf("%d %d", &n, &m);
    	
    	int row[1024] = {}, col[1024] = {};
    	int tot = 0;
    	for (int i = 0; i < n; i++) {
    		scanf("%s", s[i]);
    		for (int j = 0; j < m; j++) {
    			if (s[i][j] == '1')
    				row[i]++, col[j]++, tot++;
    		}
    	}
    	
#define INF 0x3f3f3f3f
		pair<int, int> ret[2];
		ret[0] = ret[1] = make_pair(INF, INF);
    	if (tot%n == 0) {
    		g.init(n + 2);
    		int source = n, sink = n + 1;
    		for (int i = 0; i < n; i++) {
    			g.Addedge(source, i, row[i], 0);
    			g.Addedge(i, sink, tot/n, 0);
    			g.Addedge(i, (i+1)%n, INF, 1);
    			g.Addedge(i, (i+n-1)%n, INF, 1);
    		}
    		ret[0] = g.mincost(source, sink);
    	}
    	
    	if (tot%m == 0) {
    		g.init(m + 2);
    		int source = m, sink = m + 1;
    		for (int i = 0; i < m; i++) {
    			g.Addedge(source, i, col[i], 0);
    			g.Addedge(i, sink, tot/m, 0);
    			g.Addedge(i, (i+1)%m, INF, 1);
    			g.Addedge(i, (i+m-1)%m, INF, 1);
    		}
    		ret[1] = g.mincost(source, sink);
    	}
    	
    	printf("Case %d: ", ++cases);
        if (ret[0].first != INF && ret[1].first != INF)
        	printf("both %d\n", ret[0].first + ret[1].first);
        else if (ret[0].first != INF)
        	printf("row %d\n", ret[0].first);
        else if (ret[1].first != INF)
        	printf("column %d\n", ret[1].first);
        else
        	printf("impossible\n");
    }
    return 0;
}
/*
2
2 3
001
111
3 3
001
011
000
*/
