#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#define oo 0xfffffff
using namespace std;
typedef struct {
    int to, v;
} Arc;
vector<Arc> g[1001];
int n, m, st, ed;
int Nodd[22] = {}, gp[22][22], M;
void spfa(int st, int nd) {
    queue<int> Q;
    static int used[1001], dist[1001];
    static int i, tn;
    for(i = 1; i <= n; i++)
        used[i] = 0, dist[i] = 0xffff;
    Q.push(st);
    dist[st] = 0;
    while(!Q.empty()) {
        tn = Q.front();
        used[tn] = 0;
        Q.pop();
        for(vector<Arc>::iterator it = g[tn].begin();
            it != g[tn].end(); it++) {
            if(dist[it->to] > dist[tn]+it->v) {
                dist[it->to] = dist[tn]+it->v;
                if(!used[it->to]) {
                    used[it->to] = 1;
                    Q.push(it->to);
                }
            }
        }
    }
    for(i = 0; i < M; i++)
        gp[nd][i] = dist[Nodd[i]];
}
int dp[1<<22];
void dp_build(int n, int m) {
    if(n == 0 || dp[n] != oo)  return ;
    if(dp[m] == oo)
        dp_build(m, 0);
    int i, j, tmp;
    for(i = 0; i < M; i++) {
        if(n&(1<<i)) {
            for(j = i+1; j < M; j++) {
                if(n&(1<<j)) {
                    dp_build(n-(1<<i)-(1<<j), m+(1<<i)+(1<<j));
                    dp[n] = min(dp[n], dp[n-(1<<i)-(1<<j)]+gp[i][j]);
                }
            }
            break;
        }
    }
}
int main() {
    int i, j;
    while(scanf("%d %d %d %d", &n, &m, &st, &ed) == 4) {
        for(i = 1; i <= n; i++)
            g[i].clear();
        Arc in;
        int x, y;
        int indeg[1001] = {}, ans = 0;
        while(m--) {
            scanf("%d %d %d", &x, &y, &in.v);
            ans += in.v;
            in.to = y;
            g[x].push_back(in);
            in.to = x;
            g[y].push_back(in);
            indeg[x]++, indeg[y]++;
        }
        indeg[st]++, indeg[ed]++;
        M = 0;
        for(i = 1; i <= n; i++) {
            if(indeg[i]&1) {
                Nodd[M++] = i;
            }
        }
        for(i = 0; i < M; i++)
            spfa(Nodd[i], i);
        for(i = (1<<M)-1; i >= 0; i--)
            dp[i] = oo;
        dp[0] = 0;
        dp_build((1<<M)-1, 0);
        printf("%d\n", dp[(1<<M)-1]+ans);
    }
    return 0;
}
