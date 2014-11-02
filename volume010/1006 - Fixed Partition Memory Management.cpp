#include <stdio.h>
#include <string.h>
#include <queue>
#include <functional>
#include <deque>
#include <algorithm>
using namespace std;
struct Node {
    int x, y, cap, cost;// x->y, v
    int next;
} edge[1000005];
int e, head[600], dis[600], prev[600], record[600], inq[600];
void addEdge(int x, int y, int cap, int cost) {
    edge[e].x = x, edge[e].y = y, edge[e].cap = cap, edge[e].cost = cost;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].cap = 0, edge[e].cost = -cost;
    edge[e].next = head[y], head[y] = e++;
}
int mincost(int s, int t) {
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
        if(dis[t] == oo)
            break;
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
    int n, m, cases = 0;
    int x, y, d, a;
    int mem[128], needmem[128][128], runtime[128][128], ch[128];
    
    while(scanf("%d %d", &n, &m) == 2 && n+m) {
    	for (int i = 0; i < n; i++)
    		scanf("%d", &mem[i]);
    	for (int i = 0; i < m; i++) {
    		scanf("%d", &ch[i]);
    		for (int j = 0; j < ch[i]; j++)
    			scanf("%d %d", &needmem[i][j], &runtime[i][j]);
    		needmem[i][ch[i]] = 0x3f3f3f3f;
    	}
    	
        e = 0;
        memset(head, -1, sizeof(head));
        int source = n*m + m + 1, sink = n*m + m + 2;
        for (int i = 0; i < m; i++) {
        	addEdge(source, i, 1, 0);
        	for (int j = 0; j < ch[i]; j++) {
        		for (int k = 0; k < n; k++) {
        			if (needmem[i][j] <= mem[k] && mem[k] <= needmem[i][j+1]) {
        				for (int p = 0; p < m; p++)
        					addEdge(i, m + k * m + p, 1, runtime[i][j] * (p + 1));
        			}
        		}
        	}
        }
        for (int i = 0; i < n; i++)
        	for (int j = 0; j < m; j++)
        		addEdge(m + i * m + j, sink, 1, 0);
        
        double cost = mincost(source, sink);
        int prog[128], from[128] = {}, run[128];
        vector< pair<int, int> > runtable[128];
        for (int i = 0; i < m; i++) {
        	for (int j = head[i]; j != -1; j = edge[j].next) {
        		if (edge[j].cap == 0 && edge[j].y >= m && edge[j].y < m + n*m) {
        			prog[i] = (edge[j].y - m) / m;
        			run[i] = edge[j].cost / ((edge[j].y - m) % m + 1);
        			runtable[prog[i]].push_back(make_pair((edge[j].y - m) % m, i));
        			break;
        		}
        	}
        }
        for (int i = 0; i < n; i++) {
        	sort(runtable[i].begin(), runtable[i].end(), greater< pair<int, int> >());
        	for (int j = 1; j < runtable[i].size(); j++)
        		from[runtable[i][j].second] = from[runtable[i][j-1].second] + run[runtable[i][j-1].second];
        }
        printf("Case %d\n", ++cases);
        printf("Average turnaround time = %.2lf\n", (double) cost / m);
        for (int i = 0; i < m; i++) {
        	printf("Program %d runs in region %d from %d to %d\n", i+1, prog[i]+1, from[i], from[i] + run[i]);
        }
        puts("");
    }
    return 0;
}
/*
2 4
40 60
1 35 4
1 20 3
1 40 10
1 60 7
3 5
10 20 30
2 10 50 12 30
2 10 100 20 25
1 25 19
1 19 41
2 10 18 30 42
0 0
*/
