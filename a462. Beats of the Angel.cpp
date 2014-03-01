#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
struct Arc {
    int to, v;
};
typedef vector<Arc>::iterator it;
vector<Arc> nlist[1001];
int dis[1001], dis2[1001];
int used[1001], used2[1001];
int ans = 0;
int spfa2(int, int);
void spfa(int st, int ed) {
    memset(dis, 63, sizeof(dis));
    memset(used, 0, sizeof(used));
    dis[st] = 0;
    queue<int> Q;
    Q.push(st);
    int tn;
    while(!Q.empty()) {
        tn = Q.front();
        used[tn] = 0;
        Q.pop();
        for(it i = nlist[tn].begin(); i != nlist[tn].end(); i++) {
            if(dis[i->to] > dis[tn] + i->v) {
                dis[i->to] = dis[tn] + i->v;
                if(used[i->to] == 0) {
                    used[i->to] = 1;
                    Q.push(i->to);
                }
            }
        }
    }
    Q.push(ed);
    int spath = dis[ed];
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        for(it i = nlist[tn].begin(), j; i != nlist[tn].end(); i++) {
            if(dis[tn] - i->v == dis[i->to]) {
                Q.push(i->to);
                for(j = nlist[i->to].begin(); j != nlist[i->to].end(); j++) {
                    if(j->to == tn && j->v == i->v) {
                        break;
                    }
                }
                if(i->v <= ans)
                    break;
                i->v <<= 1;
                j->v <<= 1;
                int tpath = spfa2(st, ed);
                if(tpath - spath > ans)
                    ans = tpath - spath;
                i->v >>= 1;
                j->v >>= 1;
                break;
            }
        }
    }
}
int spfa2(int st, int ed) {
    memset(dis2, 63, sizeof(dis2));
    memset(used2, 0, sizeof(used2));
    dis2[st] = 0;
    queue<int> Q2;
    Q2.push(st);
    int tn;
    while(!Q2.empty()) {
        tn = Q2.front();
        used2[tn] = 0;
        Q2.pop();
        for(it i = nlist[tn].begin(); i != nlist[tn].end(); i++) {
            if(dis2[i->to] > dis2[tn] + i->v) {
                dis2[i->to] = dis2[tn] + i->v;
                if(used2[i->to] == 0) {
                    used2[i->to] = 1;
                    Q2.push(i->to);
                }
            }
        }
    }
    return dis2[ed];
}
int main() {
    int n, m, i, a, b, w;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 1; i <= n; i++)
            nlist[i].clear();
        Arc tmp;
        for(i = 0; i < m; i++) {
            scanf("%d %d %d", &a, &b, &w);
            tmp.to = b, tmp.v = w;
            nlist[a].push_back(tmp);
            tmp.to = a;
            nlist[b].push_back(tmp);
        }
        ans = 0;
        spfa(1, n);
        printf("%d\n", ans);
    }
    return 0;
}
