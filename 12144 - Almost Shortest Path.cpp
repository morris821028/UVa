#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;
struct edge {
    int from, to, v, SP;//shortest path
    edge(int a, int b, int c, int d):
        to(a), v(b), SP(c), from(d) {}
};
vector<edge> g[505];
vector<edge*> pre[505];
int dis[505];
void spfa(int st, int ed, int save) {
    int inq[505] = {}, tn;
    memset(dis, 63, sizeof(dis));
    queue<int> Q;
    dis[st] = 0;
    Q.push(st), inq[st] = 1;
    while(!Q.empty()) {
        tn = Q.front(), Q.pop();
        inq[tn] = 0;
        for(vector<edge>::iterator it = g[tn].begin();
            it != g[tn].end(); it++) {
            if(it->SP)  continue;
            if(dis[it->to] > dis[tn] + it->v) {
                dis[it->to] = dis[tn] + it->v;
                pre[it->to].clear();
                if(inq[it->to] == 0)
                    Q.push(it->to), inq[it->to] = 1;
            }
            if(save && dis[it->to] == dis[tn] + it->v)
                pre[it->to].push_back(&(*it));
        }
    }
}
void cutSP(int st, int ed) {
    int inq[505] = {}, tn;
    queue<int> Q;
    inq[ed] = 1;
    Q.push(ed);
    while(!Q.empty()) {
        tn = Q.front(), Q.pop();
        for(vector<edge*>::iterator it = pre[tn].begin();
            it != pre[tn].end(); it++) {
            (*it)->SP = 1;
            if(inq[(*it)->from] == 0) {
                Q.push((*it)->from);
                inq[(*it)->from] = 1;
            }
        }
    }
}
int main() {
    int n, m, x, y, v;
    int st, ed;
    int i, j, k;
    while(scanf("%d %d", &n, &m) == 2 && n) {
        scanf("%d %d", &st, &ed);
        for(i = 0; i < n; i++) {
            g[i].clear();
            pre[i].clear();
        }
        while(m--) {
            scanf("%d %d %d", &x, &y, &v);
            g[x].push_back(edge(y,v,0,x));
        }
        spfa(st, ed, 1);
        cutSP(st, ed);
        spfa(st, ed, 0);
        if(dis[ed] == 0x3f3f3f3f)
            puts("-1");
        else
            printf("%d\n", dis[ed]);
    }
    return 0;
}
