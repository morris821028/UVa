#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
char s[1024];
int prefer[128][128], votes[128];
int n, m, st, visited[128];
int same[128][128];
vector<int> g[128], g2[128];
void dfs(int u) {
    visited[u] = 1;
    int v;
    for (int i = 0; i < g[u].size(); i++) {
        v = g[u][i];
        if (visited[v] == 0)
            dfs(v);
    }
}
int member[128];
int dfs_clique(int idx, int mm) {
    if (idx == n) {
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < mm; i++)
            dfs(member[i]);
        
        int ret = 0;
        for (int i = 0; i < n; i++)
            ret += visited[i];
        return ret == n;
    }
    int ok = 1;
    for (int i = 0; i < mm; i++)
        ok &= same[member[i]][idx];
    if (ok) {
        member[mm] = idx;
        if (dfs_clique(idx+1, mm+1))
            return 1;
    }
    return dfs_clique(idx+1, mm);
}
int solve() {
    for (int i = 0; i < n; i++)
        g[i].clear(), g2[i].clear();
    memset(same, 0, sizeof(same));
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int a = 0, b = 0;
            for (int k = 0; k < m; k++) {
                if (prefer[k][i] < prefer[k][j])
                    a += votes[k];
                else
                    b += votes[k];
            }
            if (a > b)
                g[i].push_back(j);
            else if (b > a)
                g[j].push_back(i);
            else {
                g2[i].push_back(j), g2[j].push_back(i);
                same[i][j] = same[j][i] = 1;
            }
        }
        same[i][i] = 1;
    }
    member[0] = st;
    return dfs_clique(0, 1);
}
int main() {
    while (scanf("%d %d %s", &n, &m, s) == 3) {
        st = s[0] - 'a';
        for (int i = 0; i < m; i++) {
            scanf("%d %s", &votes[i], s);
            for (int j = 0; s[j]; j++)
                prefer[i][s[j]-'a'] = j;
        }
        puts(solve() ? "Y" : "N");
    }
    return 0;
}