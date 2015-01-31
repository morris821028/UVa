#include <stdio.h>
#include <map>
#include <vector>
#include <set>
#include <math.h>
#include <algorithm>
#include <assert.h>
using namespace std;
#define MAXN 32767
vector<int> g[MAXN];
int color[MAXN], used[MAXN], visited[MAXN], N, M, K;
pair<int, int> A[MAXN];
vector<int> topo;
void dfs(int u) {
    visited[u] = 1;
    for (int i = 0; i < g[u].size(); i++) {
        if (visited[g[u][i]] == 0) {
            dfs(g[u][i]);
        }
    }
    topo.push_back(u);
}
int randomTest() {
    for (int i = 0; i < N; i++)
        color[i] = -1, used[i] = 0, visited[i] = 0;
    topo.clear();
    for (int i = 0; i < N; i++) {
        if (visited[i] == 0) {
            dfs(i);
        }
    }
    int testcase = 0;
    for (int i = N-1; i >= 0; i--) {
        int x = topo[i];
        testcase++;
        for (int j = 0; j < g[x].size(); j++)
            if (color[g[x][j]] >= 0)
                used[color[g[x][j]]] = testcase;
        for (int j = 0; j < K; j++) {
            if (used[j] != testcase) {
                color[x] = j;
            }
        }
        assert(color[x] >= 0);
        if (color[x] < 0)   return 0;
    }
    return 1;
}
int main() {
    int cases = 0, x, y;
    while (scanf("%d %d", &N, &M) == 2 && N) {
        for (int i = 0; i < N; i++)
            g[i].clear();
        for (int i = 0; i < M; i++) {
            scanf("%d %d", &x, &y);
            x--, y--;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        
        K = 0;
        for (int i = 0; i < N; i++) {
            K = max(K, (int) g[i].size());
        }
        if (K%2 == 0)   K++;
    
        randomTest();
        
        if (cases++)    puts("");
        printf("%d\n", K);
        for (int i = 0; i < N; i++) {
            printf("%d\n", color[i] + 1);
        }
    }
    return 0;
}
/*

*/