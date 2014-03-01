#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
struct Node {
    int x, y, cap, cost;// x->y, v
    int next;
} edge[10005];
int e, head[100], dis[100], prev[100], record[100], inq[100];
void addEdge(int x, int y, int cap, int cost) {
    edge[e].x = x, edge[e].y = y, edge[e].cap = cap, edge[e].cost = cost;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].cap = 0, edge[e].cost = 0;
    edge[e].next = head[y], head[y] = e++;
}
int ret, ones, n, m, TOTFLOW;//global
int precost, pretotflow;
int mincost(int s, int t) {
    int mncost = 0, flow, totflow = 0;
    int i, x, y;
    mncost = precost, totflow = pretotflow;
    while(1) {
        memset(dis, 63, sizeof(dis));
        memset(inq, 0, sizeof(inq));
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
            if(dis[t] < 0)
                break;
        }
        if(dis[t] == oo)
            break;
        flow = oo;
        for(x = t; x != s; x = prev[x]) {
            int ri = record[x];
            flow = min(flow, edge[ri].cap);
        }
        //this problem special condition
        if(ones + (mncost - (TOTFLOW - totflow)) >= ret)
            return 0xffffff;
        if(dis[t] > 0) {
            //printf("%d %d %d\n", mncost, flow, TOTFLOW);
            precost = mncost, pretotflow = totflow;
            return mncost + TOTFLOW - totflow;
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
    precost = mncost, pretotflow = totflow;
    return mncost;
}
// source - column - row - sink
int main() {
    /*freopen("inputA.txt", "r+t", stdin);
	freopen("outA.txt", "w+t", stdout);*/
    int testcase, cases = 0;
    char g[55][55];
    int i, j, k;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &n, &m);
        char g[50][50];
        for(i = 0; i < n; i++)
            scanf("%s", g[i]);
        ones = 0;
        for(i = 0; i < n; i++)
            for(j = 0; j < m; j++)
                ones += g[i][j]-'0';
        ret = min(ones, n*m-ones);
        e = 0;
        memset(head, -1, sizeof(head));
        int source = 0, sink = n+m+1;
        for(i = 0; i < n; i++)
            addEdge(source, i+1, 0, 0);
        for(i = 0; i < m; i++)
            addEdge(i+n+1, sink, 0, 0);
        for(i = 0; i < n; i++) {
            for(j= 0; j < m; j++) {
                if(g[i][j] == '0') {
                    addEdge(i+1,j+n+1,1,1);
                } else {
                    addEdge(i+1,j+n+1,1,-1);
                }
            }
        }
        int prex = 0, prey = 0;
        precost = 0, pretotflow = 0;
        for(k = 0; k <= m; k++) {
            //each row(n) using x ones.
            //each column(m) using y ones.
            int x = k;
            if(x*n%m)   continue;
            int y = x*n/m;
            /*e = 0;
            memset(head, -1, sizeof(head));
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
            }*/
            for(i = head[source]; i != -1; i = edge[i].next) {
                edge[i].cap += x-prex;
            }
            for(i = head[sink]; i != -1; i = edge[i].next) {
                edge[i^1].cap += y-prey;
            }
            TOTFLOW = x*n;
            prex = x, prey = y;
            int mncost = mincost(source, sink);
            //printf("%d %d\n", x, y);
            //printf("mincost %d\n", mncost);
            ret = min(ret, ones+mncost);
        }
        printf("Case %d: %d\n", ++cases, ret);
    }
    return 0;
}
/*
1000
8 10
1000001101
0011110011
1101100110
0101111110
1011010111
0000000100
1011100101
1110101110
5 5
10110
11010
01100
10101
01001
5 5
10010
00000
00111
11011
00001
3 3
110
110
110
4 4
1000
1000
0000
0011
5 5
10110
11010
01100
10101
01001
5 5
10010
00000
00111
11011
00001
*/
