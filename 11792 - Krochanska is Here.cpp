#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
vector<int> g[10005];
int n, m, path[10005];
int dist[10005], used[10005];
int spfa(int st) {
    int i, tn;
    queue<int> Q;
    for(i = 0; i <= n; i++)
        dist[i] = 0xfffffff, used[i] = 0;
    dist[st] = 0;
    Q.push(st);
    while(!Q.empty()) {
        tn = Q.front(), Q.pop();
        used[tn] = 0;
        for(i = 0; i < g[tn].size(); i++) {
            if(dist[g[tn][i]] > dist[tn]+1) {
                dist[g[tn][i]] = dist[tn]+1;
                if(!used[g[tn][i]]) {
                    used[g[tn][i]] = 1;
                    Q.push(g[tn][i]);
                }
            }
        }
    }
    int res = 0;
    for(i = 1; i <= n; i++) {
        if(path[i] > 1)
            res += dist[i];
    }
    return res;
}
int main() {
    int t, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i <= n; i++)
            g[i].clear(), path[i] = 0;
        int pre, next;
        for(i = 0; i < m; i++) {
            scanf("%d", &pre);
            path[pre]++;
            while(scanf("%d", &next) == 1) {
                if(next == 0)   break;
                g[pre].push_back(next);
                g[next].push_back(pre);
                pre = next;
                path[pre]++;
            }
        }
        int res = -1, mn = 0xfffffff;
        for(i = 1; i <= n; i++) {
            if(path[i] > 1) {
                int tmp = spfa(i);
                if(tmp < mn)
                    mn = tmp, res = i;
            }
        }
        printf("Krochanska is in: %d\n", res);
    }
    return 0;
}
