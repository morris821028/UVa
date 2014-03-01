#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
struct Node {
    int x, y, v;// x->y, v
    int next;
} edge[10005];
int e, head[105], dis[105], prev[105], record[105];
void addEdge(int x, int y, int v) {
    edge[e].x = x, edge[e].y = y, edge[e].v = v;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].v = 0;
    edge[e].next = head[y], head[y] = e++;
}
int maxflow(int s, int t) {
    int flow = 0;
    int i, j, x, y;
    while(1) {
        memset(dis, 0, sizeof(dis));
        dis[s] =  0xffff; // oo
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            x = Q.front();
            Q.pop();
            for(i = head[x]; i != -1; i = edge[i].next) {
                y = edge[i].y;
                if(dis[y] == 0 && edge[i].v > 0) {
                    prev[y] = x, record[y] = i;
                    dis[y] = min(dis[x], edge[i].v);
                    Q.push(y);
                }
            }
            if(dis[t])  break;
        }
        if(dis[t] == 0) break;
        flow += dis[t];
        for(x = t; x != s; x = prev[x]) {
            int ri = record[x];
            edge[ri].v -= dis[t];
            edge[ri^1].v += dis[t];
        }
    }
    return flow;
}
double nx[100], ny[100], mx[100], my[100];
double g[100][100];
int n, m, k;
int i, j;
int solve(double limit) {
    e = 0;
    memset(head, -1, sizeof(head));
    for(i = 0; i < n; i++) {
        addEdge(0, i+1, 1);
        for(j = 0; j < m; j++) {
            if(g[i][j] <= limit)
                addEdge(i+1, j+n+1, 1);
        }
    }
    for(i = 0; i < m; i++)
        addEdge(i+n+1, n+m+1, 1);
    int flow = maxflow(0, n+m+1);
    if(flow >= n-k)
        return 1;
    return 0;
}
int main() {
    int testcase, cases = 0;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d %d", &n, &m, &k);
        for(i = 0; i < n; i++)
            scanf("%lf %lf", &nx[i], &ny[i]);
        for(i = 0; i < m; i++)
            scanf("%lf %lf", &mx[i], &my[i]);
        double l = sqrt(pow(nx[0]-mx[0],2)+pow(ny[0]-my[0],2)), r = 0, mid;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                g[i][j] = sqrt(pow(nx[i]-mx[j],2)+pow(ny[i]-my[j],2));
                l = min(l, g[i][j]);
                r = max(r, g[i][j]);
            }
        }
        printf("Case #%d:\n", ++cases);
        if((n == 0 && m == 0) || (n == k) || n == 0)
            puts("0.000");
        else if(n-k > m)
            puts("Too bad.");
        else {
        #define eps 1e-5
            int cnt = 0;
            while(fabs(l-r) > eps && cnt < 100) {
                mid = (l+r)/2;
                int f = solve(mid);
                if(f == 0)
                    l = mid;
                else
                    r = mid;
                cnt++;
            }
            printf("%.3lf\n", l);
        }
        puts("");
    }
    return 0;
}/*
4
3 3 1
0 0
1 0
2 0
0 1
1 1
2 1.5
3 3 1
0 1
1 2
2 1
1 0
1 1
2 0
3 3 0
0 1
1 2
2 1
1 0
1 1
2 0
1 0 0
100.0 200.5
*/
