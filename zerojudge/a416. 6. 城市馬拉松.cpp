#include <stdio.h>
#include <vector>
using namespace std;
typedef struct {
    int to, v;
} Arc;
vector<Arc> g[1001];
int n, m, st, ed;
int Nodd[22] = {};
void spfa(int st) {
    queue<int> Q;
    static int used[1001], dist[1001];
    static int i;
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
}
int main() {
    int i;
    while(scanf("%d %d %d %d", &n, &m, &st, &ed) == 4) {
        for(i = 1; i <= n; i++)
            g[i].clear();
        Arc in;
        int x, y;
        int indeg[1001] = {};
        while(m--) {
            scanf("%d %d %d", &x, &y, &in.d);
            in.to = y;
            g[x].push_back(in);
            in.to = x;
            g[y].push_back(in);
            indeg[x]++, indeg[y]++;
        }
        indeg[st]++, indeg[ed]++;
        m = 0;
        for(i = 1; i <= n; i++) {
            if(indeg[i]&1) {
                Nodd[m++] = i;
            }
        }
    }
    return 0;
}
