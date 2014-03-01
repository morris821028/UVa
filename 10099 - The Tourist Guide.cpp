#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
struct arc {
    int to, v;
};
int main() {
    int n, r, x, y, c, i, j, st, ed, tn;
    int cases = 0, V;
    while(scanf("%d %d", &n, &r) == 2) {
        if(n == 0)  break;
        vector<arc> g[n+1];
        while(r--) {
            scanf("%d %d %d", &x, &y, &c);
            arc tmp;
            tmp.to = y, tmp.v = c;
            g[x].push_back(tmp);
            tmp.to = x;
            g[y].push_back(tmp);
        }
        scanf("%d %d %d", &st, &ed, &V);
        int dist[n+1], used[n+1];
        for(i = 1; i <= n; i++)
            dist[i] = 0, used[i] = 0;
        queue<int> Q;
        Q.push(st);
        dist[st] = 0xfffffff;
        while(!Q.empty()) {
            tn = Q.front();
            used[tn] = 0;
            Q.pop();
            for(i = 0; i < g[tn].size(); i++) {
                if(dist[g[tn][i].to] < min(g[tn][i].v, dist[tn])) {
                    dist[g[tn][i].to] = min(g[tn][i].v, dist[tn]);
                    if(!used[g[tn][i].to]) {
                        used[g[tn][i].to] = 1;
                        Q.push(g[tn][i].to);
                    }
                }
            }
        }
        dist[ed]--;
        printf("Scenario #%d\n", ++cases);
        printf("Minimum Number of Trips = %d\n\n", V/dist[ed]+(V%dist[ed] != 0));
    }
    return 0;
}
