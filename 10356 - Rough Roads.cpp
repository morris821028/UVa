#include <stdio.h>
#include <queue>
using namespace std;
struct edge {
    int to, v;
    edge(int a, int b):
        to(a), v(b){}
};
struct node {
    int nd, way;
    node(int a, int b):
        nd(a), way(b){}
};
vector<edge> g[505];
int main() {
    int n, m, x, y, v;
    int cases = 0;
    int i;
    while(scanf("%d %d", &n, &m) == 2) {
        int dist[505][2], inq[505][2];
        for(i = 0; i < n; i++) {
            g[i].clear();
            inq[i][0] = inq[i][1] = 0;
            dist[i][0] = dist[i][1] = 0xfffffff;
        }
        for(i = 0; i < m; i++) {
            scanf("%d %d %d", &x, &y, &v);
            g[x].push_back(edge(y, v));
            g[y].push_back(edge(x, v));
        }
        dist[0][0] = 0;
        queue<node> Q;
        Q.push(node(0,0));
        node tn(0,0);
        while(!Q.empty()) {
            tn = Q.front(), Q.pop();
            inq[tn.nd][tn.way] = 0;
            for(vector<edge>::iterator it = g[tn.nd].begin();
                it != g[tn.nd].end(); it++) {
                if(dist[it->to][!tn.way] > dist[tn.nd][tn.way] + it->v) {
                    dist[it->to][!tn.way] = dist[tn.nd][tn.way] + it->v;
                    if(!inq[it->to][!tn.way]) {
                        inq[it->to][!tn.way] = 1;
                        Q.push(node(it->to, !tn.way));
                    }
                }
            }
        }
        printf("Set #%d\n", ++cases);
        if(dist[n-1][0] == 0xfffffff)
            puts("?");
        else
            printf("%d\n", dist[n-1][0]);
    }
    return 0;
}
