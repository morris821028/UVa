#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
struct arc {
    int to, v;
};
vector<arc> g[505];
int dist[505], used[505], inq[505];
int spfa(int x, int n) {// check neg cycle
    static int i, j, tn;
    queue<int> Q;
    for(i = 1; i <= n; i++) {
        dist[i] = 0, used[i] = 1;
        inq[i] = n+1;
        Q.push(i);
    }
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        used[tn] = 0;
        for(vector<arc>::iterator it = g[tn].begin();
            it != g[tn].end(); it++) {
            if(dist[it->to] > dist[tn] + it->v - x) {
                dist[it->to] = dist[tn] + it->v - x;
                if(!used[it->to]) {
                    used[it->to] = 1;
                    Q.push(it->to);
                    if(--inq[it->to] == 0)
                        return 1;
                }
            }
        }
    }
    return 0;
}
int main() {
    int n, m, i, x, y, v;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 1; i <= n; i++)
            g[i].clear();
        arc e;
        for(i= 0; i < m; i++) {
            scanf("%d %d %d", &x, &y, &v);
            e.to = y, e.v = v;
            g[x].push_back(e);
        }
        if(spfa(0, n)) {// 不具任何操作
            puts("No Solution");
            continue;
        }
        if(spfa(10001, n) == 0) {
            puts("Infinite");
            continue;
        }
        int l = 1, r = 10000;
        while(l <= r) {
            m = (l+r+1)/2;
            if(spfa(m, n))
                r = m-1;
            else
                l = m+1;
        }
        if(r)
            printf("%d\n", r);
        else
            puts("No Solution");
    }
    return 0;
}
