#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
struct Node {
    int x, y, cap, cost;// x->y, v
    int next;
} edge[500005];
int e, head[500], dis[500], prev[500], record[500], inq[500];
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
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            x = Q.front(), Q.pop();
            inq[x] = 0;
            for(i = head[x]; i != -1; i = edge[i].next) {
                y = edge[i].y;
                if(edge[i].cap > 0 && dis[y] > dis[x] + edge[i].cost) {
                    dis[y] = dis[x] + edge[i].cost;
                    prev[y] = x, record[y] = i;
                    if(inq[y] == 0) {
                        inq[y] = 1;
                        Q.push(y);
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
// source - column - row - sink
int main() {
    /*freopen("inputA.txt", "r+t", stdin);
	freopen("outA.txt", "w+t", stdout);*/
    int testcase, cases = 0;
    char g[50][50];
    int n, m;
    int i, j, k;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &n, &m);
        char g[50][50];
        for(i = 0; i < n; i++)
            scanf("%s", g[i]);
        int ones = 0;
        for(i = 0; i < n; i++)
            for(j = 0; j < m; j++)
                ones += g[i][j]-'0';
        int ret = n*m;
        for(k = 0; k <= n*m; k++) {
            //each row(n) using x ones.
            //each column(m) using y ones.
            if(k%n == 0 && k%m == 0) {
                e = 0;
                memset(head, -1, sizeof(head));
                int x = k/n, y = x*n/m;
                int source = 0, sink = n+m+1;
                for(i = 0; i < n; i++)
                    addEdge(source, i+1, x, 0);
                for(i = 0; i < m; i++)
                    addEdge(i+n+1, sink, y, 0);
                for(i = 0; i < n; i++) {
                    for(j= 0; j < m; j++) {
                        if(g[i][j] == '0') {
                            addEdge(i+1,j+n+1,1,1);
                        } else {
                            addEdge(i+1,j+n+1,1,-1);
                        }
                    }
                }
                printf("%d %d\n", x, y);
                int ocost = k, mncost = mincost(source, sink);
                ret = min(ret, ones+mncost);
            }
        }
        printf("Case %d: %d\n", ++cases, ret);
    }
    return 0;
}
