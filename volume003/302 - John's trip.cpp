#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;
struct edge {
	int to, label;
	edge(int a=0, int b=0):
		to(a), label(b) {}
	bool operator<(const edge &x) const {
		return label < x.label;
	}
};
#define MAXN 2048
vector<edge> g[MAXN];
int label_used[MAXN];
deque<int>	path;
void dfs(int u) {
    for(int i = 0; i < g[u].size(); i++) {
        if(label_used[g[u][i].label] == 0) {
        	label_used[g[u][i].label] = 1;
            dfs(g[u][i].to);
            path.push_front(g[u][i].label);
        }
    }
}
int main() {
	int x, y, z;
    while(true) {
    	for(int i = 0; i < MAXN; i++)
    		g[i].clear();
    	int e = 0, start = 0;
    	while(scanf("%d %d", &x, &y) == 2) {
    		if(x == 0 && y == 0)
    			break;
    		/* Johnny lives at the junction ending the 1st street 
				input with smaller number. */
    		if(e == 0)
    			start = min(x, y);
    		scanf("%d", &z);
    		g[x].push_back(edge(y, z));
    		g[y].push_back(edge(x, z));
    		e++;
    	}
    	if(e == 0)	break;
    	
    	int odd = 1;
    	for(int i = 0; i < MAXN; i++) {
    		odd &= g[i].size()%2 == 0;
    	}
    	if(!odd) {
    		puts("Round trip does not exist.\n");
    		continue;
    	}
    	for(int i = 0; i < MAXN; i++)
    		sort(g[i].begin(), g[i].end());
    	memset(label_used, 0, sizeof(label_used));
    	path.clear();
    	dfs(start);
    	for(int i = 0; i < path.size(); i++) 
    		printf("%d%c", path[i], i == path.size()-1 ? '\n' : ' ');
    	puts("");
    }
    return 0;
}
