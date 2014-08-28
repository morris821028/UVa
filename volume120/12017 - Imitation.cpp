#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;

vector<int> g[1005], dag[1005];
int vfind[1005], findIdx;
int stk[1005], stkIdx;
int in_stk[1005], visited[1005];
int contract[1005], contract_cnt[1005];
int scc(int nd) {
    in_stk[nd] = visited[nd] = 1;
    stk[++stkIdx] = nd;
    vfind[nd] = ++findIdx;
    int mn = vfind[nd];
    for(int i = 0; i < g[nd].size(); i++) {
        if(!visited[g[nd][i]])
            mn = min(mn, scc(g[nd][i]));
        if(in_stk[g[nd][i]])
            mn = min(mn, vfind[g[nd][i]]);
    }
    if(mn == vfind[nd]) {
        contract_cnt[nd] = 0;
        do {
            in_stk[stk[stkIdx]] = 0;
            contract[stk[stkIdx]] = nd;
            contract_cnt[nd]++;
        } while(stk[stkIdx--] != nd);
    }
    return mn;
}

int min_edge, max_edge, mg[1024][1024];

void dfs(int u, int start) {
    mg[start][u] = 1, max_edge++;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!mg[start][v]) {
            dfs(v, start);
        }
    }
}
void bfs(int st, int n) {
    queue<int> Q;
    int dist[1024] = {}, u, v;
    Q.push(st);
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        for (int i = 0; i < dag[u].size(); i++) {
            v = dag[u][i];
            if (dist[v] < min(dist[u] + 1, 2)) {
                dist[v] = min(dist[u] + 1, 2);
                Q.push(v);
            }
        }
    }
    for (int i = 0; i < dag[st].size(); i++) {
        int v = dag[st][i];
//        printf("%d %d %d\n", st, v, dist[v]);
        if (dist[v] != 1) {
            if (mg[st][v]) {
                mg[st][v] = 0, min_edge--;
            }
        }
    }
}
int main() {
    int testcase, cases = 0, n, m;
    int u, v;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i <= n; i++)
            g[i].clear(), dag[i].clear();
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &u, &v);
            g[u].push_back(v);
        }
        min_edge = max_edge = 0;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                mg[i][j] = 0;
        
        for (int i = 1; i <= n; i++)
            dfs(i, i);
        
        // SCC
        memset(visited, 0, sizeof(visited));
        memset(in_stk, 0, sizeof(in_stk));
        for(int i = 1; i <= n; i++) {
            if(!visited[i]) {
                findIdx = stkIdx = 0;
                scc(i);
            }
        }
        
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                mg[i][j] = 0;
        
        for(int i = 1; i <= n; i++) {
            int x = contract[i], y;
            for(vector<int>::iterator it = g[i].begin();
                it != g[i].end(); it++) {
                y = contract[*it];
                if(x != y) {
                    if (!mg[x][y]) {
                        mg[x][y] = 1, dag[x].push_back(y);
                        min_edge++;
                    }
                }
            }
        }
        
        for (int i = 1; i <= n; i++) {
            if (contract[i] == i) {
                if (contract_cnt[i] > 1)
                    min_edge += contract_cnt[i];
                bfs(i, n);
            }
        }
        printf("Case #%d: %d %d\n", ++cases, min_edge, max_edge - n);
    }
    return 0;
}

/*
 3
 3 3
 1 2
 2 3
 1 3
 3 3
 1 2
 2 3
 3 1
 9 9
 1 2
 2 3
 3 1
 4 5
 5 6
 6 4
 7 8
 8 9
 9 7
 */