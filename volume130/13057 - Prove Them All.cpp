#include <bits/stdc++.h>
using namespace std;
// similar as UVa 11504 - Dominos 
// algorithm: SCC
const int MAXN = 32767;
class SCC {
public:
    int n;
    vector<int> g[MAXN], dag[MAXN];
    // <SCC begin>
    int vfind[MAXN], findIdx;
    int stk[MAXN], stkIdx;
    int in_stk[MAXN], visited[MAXN];
    int contract[MAXN];
    int scc_cnt;
    // <SCC end>
    int scc(int u) {
        in_stk[u] = visited[u] = 1;
        stk[++stkIdx] = u, vfind[u] = ++findIdx;
        int mn = vfind[u], v;
        for(int i = 0; i < g[u].size(); i++) {
        	v = g[u][i];
            if(!visited[v])
                mn = min(mn, scc(v));
            if(in_stk[v])
                mn = min(mn, vfind[v]);
        }
        if(mn == vfind[u]) {
            do {
                in_stk[stk[stkIdx]] = 0;
                contract[stk[stkIdx]] = scc_cnt;
            } while(stk[stkIdx--] != u);
            scc_cnt++;
        }
        return mn;
    }
    void addEdge(int u, int v) { // u -> v
        g[u].push_back(v);
    }
    void solve() {
        for (int i = 0; i < n; i++)
            visited[i] = in_stk[i] = 0;
        scc_cnt = 0;
        for (int i = 0; i < n; i++) {
        	if (visited[i])	continue;
        	stkIdx = findIdx = 0;
        	scc(i);
        }
    }
    void make_DAG() {
        int x, y;
        for (int i = 0; i < n; i++) {
            x = contract[i];
            for (int j = 0; j < g[i].size(); j++) {
                y = contract[g[i][j]];
                if (x != y)
                    dag[x].push_back(y);
            }
        }
        for (int i = 0; i < scc_cnt; i++) {
            sort(dag[i].begin(), dag[i].end());
            dag[i].resize(unique(dag[i].begin(), dag[i].end()) - dag[i].begin());
        }
    }
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++)
            g[i].clear(), dag[i].clear();
    }
} g;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m, u, v;
		scanf("%d %d", &n, &m);
		g.init(n);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &u, &v);
			u--, v--;
			g.addEdge(u, v);
		}
		g.solve();
		g.make_DAG();
		
		int indeg[MAXN] = {}, ret = 0;
		for (int i = 0; i < g.scc_cnt; i++) {
			for (auto &e : g.dag[i]) {
				indeg[e]++;
			}
		}
		for (int i = 0; i < g.scc_cnt; i++)
			ret += indeg[i] == 0;
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}

