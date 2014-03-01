#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct edge {
    int to, v;
    edge(int a, int b):
        to(a), v(b) {}
};
vector<edge> g[105];
#define oo 0xfffffff
void spfa(int st, int ed, int n) {
    int dis[105][2], inq[105] = {};
    int i, tn, tmp;
    for(i = 0; i < n; i++)
        dis[i][0] = dis[i][1] = oo;
    dis[st][0] = 0;
    queue<int> Q;
    Q.push(st);
    while(!Q.empty()) {
        tn = Q.front(), Q.pop();
        inq[tn] = 0;
        if(dis[tn][0] >= dis[ed][1])
            continue;
        for(vector<edge>::iterator it = g[tn].begin();
            it != g[tn].end(); it++) {
            tmp = dis[tn][0] + it->v;
            if(tmp == dis[it->to][0] || tmp == dis[it->to][1])
                {}
            else {
                if(dis[it->to][1] > tmp) {
                    dis[it->to][1] = tmp;
                    if(inq[it->to] == 0) {
                        inq[it->to] = 1;
                        Q.push(it->to);
                    }
                    if(dis[it->to][1] < dis[it->to][0])
                        swap(dis[it->to][0], dis[it->to][1]);
                }
            }
            tmp = dis[tn][1] + it->v;
            if(tmp == dis[it->to][0] || tmp == dis[it->to][1])
                {}
            else {
                if(dis[it->to][1] > tmp) {
                    dis[it->to][1] = tmp;
                    if(inq[it->to] == 0) {
                        inq[it->to] = 1;
                        Q.push(it->to);
                    }
                    if(dis[it->to][1] < dis[it->to][0])
                        swap(dis[it->to][0], dis[it->to][1]);
                }
            }
        }
    }
    if(dis[ed][1] == oo)
        puts("?");
    else
        printf("%d\n", dis[ed][1]);
}
int main() {
    int n, m, q, cases = 0;
    int x, y, v, i;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 0; i < n; i++)
            g[i].clear();
        while(m--) {
            scanf("%d %d %d", &x, &y, &v);
            g[x].push_back(edge(y, v));
            g[y].push_back(edge(x, v));
        }
        printf("Set #%d\n", ++cases);
        scanf("%d", &q);
        while(q--) {
            scanf("%d %d", &x, &y);
            spfa(x, y, n);
        }
    }
    return 0;
}
