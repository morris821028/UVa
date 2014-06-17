#include <stdio.h>
#include <string.h>
int deg[205];
int visited[205];
int g[205][205];
int n, m, x, y;
void dfs(int u) {
	visited[u] = 1;
	for(int i = 0; i < n; i++) {
		if(g[u][i] && visited[i] == 0)
			dfs(i);
	}
}
int main() {
    while(scanf("%d %d", &n, &m) == 2) {
    	memset(g, 0, sizeof(g));
        int i, j;
        for(i = 0; i < n; i++) {
            deg[i] = 0;
            visited[i] = 1;
        }
        while(m--) {
            scanf("%d %d", &x, &y);
            deg[x]++, deg[y]++;
            g[x][y] = g[y][x] = 1;
            visited[x] = visited[y] = 0;
        }
        int flag = 0;
        for(i = 0; i < n; i++) {
            if(deg[i]%2 == 1) {
                flag = 1;
            }
        }
        if(flag)
            puts("Not Possible");
        else {
        	int cc = 0;
        	for(int i = 0; i < n && cc <= 1; i++)
        		if(visited[i] == 0)
        			dfs(i), cc++;
        	if(cc == 1)
            	puts("Possible");
            else
            	puts("Not Possible");
        }
    }
    return 0;
}
