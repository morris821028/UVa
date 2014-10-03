#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
#define oo 0xfffffff
using namespace std;
vector<int> g[65536];
int dp_down[65536][2], dp_up[65536];
int used[65536];
void dfs(int u) {
	used[u] = 1;
	dp_down[u][0] = dp_down[u][1] = 0;
    for(int i = 0; i < g[u].size(); i++) {
    	int v = g[u][i];
        if(used[v] == 0) {
            dfs(v);
            if(dp_down[v][0]+1 > dp_down[u][1])
                dp_down[u][1] = dp_down[v][0] + 1;
            if(dp_down[u][1] > dp_down[u][0])
                swap(dp_down[u][0], dp_down[u][1]);
        }
    }
}
void dfs2(int u, int dep) {
    dp_up[u] = dep, used[u] = 1;
    for(int i = 0; i < g[u].size(); i++) {
    	int v = g[u][i];
        if(used[v] == 0) {
            int hv;
            if(dp_down[v][0] + 1 != dp_down[u][0])
                hv = dp_down[u][0];
            else
                hv = dp_down[u][1];
            hv = max(hv, dp_up[u]);
            dfs2(v, hv+1);
        }
    }
}
int main() {
	int n, m;
	int x, y;
    while (scanf("%d %d", &n, &m) == 2) {
    	int mxpath[2][65636];
		int a_diameter = 0, b_diameter = 0;
    	for (int i = 0; i <= n; i++)
    		g[i].clear();
    	for (int i = 1; i < n; i++) {
    		scanf("%d %d", &x, &y);
    		g[x].push_back(y);
    		g[y].push_back(x);
    	}
    	memset(used, 0, sizeof(used));
    	dfs(1);
    	memset(used, 0, sizeof(used));
    	dfs2(1, 0);
    	for (int i = 1; i <= n; i++) {
    		mxpath[0][i] = max(max(dp_down[i][0], dp_down[i][1]), dp_up[i]);
    		a_diameter = max(a_diameter, dp_down[i][0] + dp_down[i][1]);
    		a_diameter = max(a_diameter, dp_down[i][0] + dp_up[i]);
    	}
    		
    	for (int i = 0; i <= m; i++)
    		g[i].clear();
    	for (int i = 1; i < m; i++) {
    		scanf("%d %d", &x, &y);
    		g[x].push_back(y);
    		g[y].push_back(x);
    	}
    	memset(used, 0, sizeof(used));
    	dfs(1);
    	memset(used, 0, sizeof(used));
    	dfs2(1, 0);
		for (int i = 1; i <= m; i++) {
    		mxpath[1][i] = max(max(dp_down[i][0], dp_down[i][1]), dp_up[i]);
    		b_diameter = max(b_diameter, dp_down[i][0] + dp_down[i][1]);
    		b_diameter = max(b_diameter, dp_down[i][0] + dp_up[i]);
    	}
    	double ret = 0, suffix[65536] = {};
    	sort(mxpath[0]+1, mxpath[0]+1+n);
    	sort(mxpath[1]+1, mxpath[1]+1+m);
    	for (int i = m; i >= 0; i--)
    		suffix[i] = suffix[i+1] + mxpath[1][i];
    	int mx_diameter = max(a_diameter, b_diameter);
    	for (int i = 1, j = m; i <= n; i++) {
    		while (j > 0 && mxpath[0][i] + mxpath[1][j] >= mx_diameter)
    			j--;
    		ret += j * mx_diameter + (suffix[j + 1] + mxpath[0][i] * (m - j) + m - j);
    	}
    	printf("%.3lf\n", ret / n / m);
    }
    return 0;
}
/*
4 5
1 2
2 3
4 2
2 3
3 4
4 1
4 5

1 5
1 2
2 3
3 4
4 5
*/
