// 2-satisify problem
// UVa 1391, enum one solution for 2-satisify problem.
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;
const int MAXN = 262144;
class TwoSat {
public:
    int n, mark[MAXN];
    int stk[MAXN], stkIdx;
    vector<int> g[MAXN];
    void addEdge(int u, int v) { // u -> v
        g[u].push_back(v);
    }
    int dfs(int u) {
        if (mark[u^1])  return 0;
        if (mark[u])    return 1;
        mark[u] = 1, stk[++stkIdx] = u;
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (!dfs(v))
                return false;
        }
        return true;
    }
    int solvable() {
        for(int i = 0; i < n; i += 2) {
            if (mark[i] == 0 && mark[i+1] == 0) {
                stkIdx = -1;
                if (!dfs(i)) {
                    while (stkIdx >= 0)
                        mark[stk[stkIdx]] = 0, stkIdx--;
                    if (!dfs(i+1))
                        return 0;
                }
            }
        }
        return 1;
    }
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++)
            g[i].clear(), mark[i] = 0;
    }
} g;

int main() {
    int n, m, age[131072], u, v;
    while (scanf("%d %d", &n, &m) == 2 && n) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &age[i]);
            sum += age[i];
        }
        
        for (int i = 0; i < n; i++)
            age[i] = age[i] * n < sum; // 1: young, 0:senior
        
        g.init(2*n);
        /*
            xi = 0, mean assign C
         */
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &u, &v);
            u--, v--;
            if (age[u] != age[v]) {
                g.addEdge(u*2, v*2+1);
                g.addEdge(v*2, u*2+1);
            } else {
                g.addEdge(u*2, v*2+1);
                g.addEdge(v*2, u*2+1);
                g.addEdge(u*2+1, v*2);
                g.addEdge(v*2+1, u*2);
            }
        }
        
        if (!g.solvable()) {
            puts("No solution.");
        } else {
            for (int i = 0; i < 2*n; i += 2) {
                if (g.mark[i])
                    puts("C");
                else
                    puts(age[i/2] ? "B" : "A");
            }
        }
    }
}