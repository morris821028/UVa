#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#define maxN 200005
#define oo 1000000007
using namespace std;
struct Arc {
    int to, v;
};
typedef vector<Arc>::iterator it;
vector<Arc> g1[maxN], g2[maxN];
int dis[2][maxN], used[maxN];
int ans = 0;
void spfa(int st, int idx) {
    int tn;
    Arc e;
    queue<int> Q;
    Q.push(st);
    dis[idx][st] = 0;
    while(!Q.empty()) {
        used[tn = Q.front()] = 0;
        Q.pop();
        for(it i = g1[tn].begin(); i != g1[tn].end(); i++) {
            if(dis[idx][i->to] > dis[idx][tn] + i->v) {
                dis[idx][i->to] = dis[idx][tn] + i->v;
                if(!used[i->to]) {
                    used[i->to] = 1;
                    Q.push(i->to);
                }
            }
        }
    }
}
int main() {
    int n, m, i, a, b, w, st, ed;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 1; i <= n; i++) {
            g1[i].clear(), g2[i].clear();
            dis[0][i] = oo, dis[1][i] = oo;
            used[i] = 0;
        }
        Arc e;
        int mxw = 0;
        for(i = 0; i < m; i++) {
            scanf("%d %d %d", &a, &b, &w);
            e.to = b, e.v = w;
            g1[a].push_back(e);
            e.to = a;
            g1[b].push_back(e);
            if(w > mxw) mxw = w;
        }
        mxw++;
        for(i = 1; i <= n; i++) {
            for(it j = g1[i].begin(); j != g1[i].end(); j++) {
                j->v = -j->v + mxw;
                printf("%d - %d %d\n", i, j->to, j->v);
            }
        }
        scanf("%d %d", &st, &ed);
        ans = 0;
        spfa(st, 0);
        spfa(ed, 1);
        for(i = 1; i <= n; i++) {
            for(it j = g1[i].begin(); j != g1[i].end(); j++) {
                double tmp1 = j->v/2.0 + dis[0][i] + dis[1][j->to];
                double tmp2 = j->v/2.0 + dis[1][i] + dis[0][j->to];
                if(tmp1 < tmp2) tmp1 = tmp2;
                printf("%9.2lf %d\n", tmp1, -j->v+mxw);
            }
        }
        for(i = 1; i <= n; i++)
            printf("%d %d\n", dis[0][i], dis[1][i]);
        printf("%d\n", ans);
    }
    return 0;
}
