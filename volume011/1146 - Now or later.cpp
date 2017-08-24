#include <bits/stdc++.h>
using namespace std;
const int MAXN = 262144;
class TwoSat {
public:
    int n;
    vector<int> g[MAXN];
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
                contract[stk[stkIdx]] = u;
            } while(stk[stkIdx--] != u);
            scc_cnt++;
        }
        return mn;
    }
    void addEdge(int u, int v) { // u -> v
        g[u].push_back(v);
    }
    int solvable() {
        for (int i = 0; i < n; i++)
            visited[i] = in_stk[i] = 0;
        scc_cnt = 1;
        for (int i = 0; i < n; i++) {
        	if (visited[i])	continue;
        	stkIdx = findIdx = 0;
        	scc(i);
        }
        
        for(int i = 0; i < n; i += 2)
            if(contract[i] == contract[i^1])
                return 0;
        return 1;
    }
    void computeChoice() {
        if (!solvable())
            return ;
        for (int i = 0; i < n; i += 2) {
            int val = 0;
            g[i].push_back(i^1);
            if (solvable())	val |= 1;
            g[i].pop_back();
            
            g[i^1].push_back(i);
            if (solvable())	val |= 2;
            g[i^1].pop_back();
            
            printf("%c", "-yn?"[val]);
        }
        puts("");
    }
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++)
            g[i].clear();
    }
} g;

int test(int gap, int n, int t[][2]) {
	g.init(2*n);
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			int a = t[i][0], b = t[i][1];
			int p = t[j][0], q = t[j][1];
			
			int ii = i<<1, jj = j<<1;
			if (abs(a-p) < gap) {
				g.addEdge(ii, jj^1);
				g.addEdge(jj, ii^1);
			}
			if (abs(a-q) < gap) {
				g.addEdge(ii, jj);
				g.addEdge(jj^1, ii^1);
			}
			if (abs(b-p) < gap) {
				g.addEdge(ii^1, jj^1);
				g.addEdge(jj, ii);
			}
			if (abs(b-q) < gap) {
				g.addEdge(ii^1, jj);
				g.addEdge(jj^1, ii);
			}
		}
	}
	
	int ret = g.solvable();
	return ret;
}
int main() {
	int n;
	int t[2048][2];
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%d %d", &t[i][0], &t[i][1]);
			
		int mx = 0, mn = 1e+7;
		for (int i = 0; i < n; i++)
			mn = min(mn, t[i][0]), mx = max(mx, t[i][1]);
		int l = 0, r = mx-mn+1, ret = 0;
		while (l <= r) {
			int mid = (l+r)/2;
			if (test(mid, n, t))
				l = mid+1, ret = mid;
			else
				r = mid-1;
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
10
44 156
153 182
48 109
160 201
55 186
54 207
55 165
17 58
132 160
87 197
*/
