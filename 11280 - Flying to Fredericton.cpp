#include <stdio.h>
#include <map>
#include <queue>
#include <iostream>
#define oo 0xfffffff
using namespace std;
struct arc {
    int to, v;
    arc(int x, int y) : to(x), v(y) {}
};
vector<arc> g[105];
int inq[105][105];
void spfa(int n, int k) {
    queue<arc> Q;
    arc tn(0,0);
    int dist[105][k+1], i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j <= k; j++)
            dist[i][j] = oo, inq[i][j] = 0;
    dist[0][0] = 0;
    Q.push(arc(0,0));
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        if(tn.v >= k)    continue;
        inq[tn.to][tn.v] = 0;
        for(vector<arc>::iterator it = g[tn.to].begin();
            it != g[tn.to].end(); it++) {
            if(dist[it->to][tn.v+1] > dist[tn.to][tn.v] + it->v) {
                dist[it->to][tn.v+1] = dist[tn.to][tn.v] + it->v;
                if(!inq[it->to][tn.v+1]) {
                    inq[it->to][tn.v+1] = 1;
                    Q.push(arc(it->to, tn.v+1));
                }
            }
        }
    }
    int ans = oo;
    for(i = 0; i <= k; i++)
        ans = ans < dist[n-1][i] ? ans : dist[n-1][i];
    if(ans == oo)
        puts("No satisfactory flights");
    else
        printf("Total cost of flight(s) is $%d\n", ans);
}
int main() {
    int cases = 0, n, m, i, j, v;
    char buf[105];
    scanf("%*d");
    while(scanf("%d", &n) == 1) {
        map<string, int> R;
        for(i = 0; i < n; i++) {
            scanf("%s", buf);
            R[buf] = i;
            g[i].clear();
        }
        scanf("%d", &m);
        while(m--) {
            scanf("%s", buf);
            i = R[buf];
            scanf("%s", buf);
            j = R[buf];
            scanf("%d", &v);
            g[i].push_back(arc(j, v));
        }
        if(cases)   puts("");
        printf("Scenario #%d\n", ++cases);
        int q, l;
        scanf("%d", &q);
        while(q--) {
            scanf("%d", &l);
            if(l < 0)   l = 0;
            spfa(n, l+1);
        }
    }
    return 0;
}
