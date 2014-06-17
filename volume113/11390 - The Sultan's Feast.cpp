#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;
vector<int> g[105], dag[105];
int vfind[105], findIdx;
int stk[105], stkIdx;
int in_stk[105], visited[105];
int contract[105];
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
        do {
            in_stk[stk[stkIdx]] = 0;
            contract[stk[stkIdx]] = nd;
        } while(stk[stkIdx--] != nd);
    }
    return mn;
}
int L[105], val_L[105], next_search[105];
int invited[105], max_like;
vector<int> cover[105];
int H() {
	int ret = 0;
	for(int i = next_search[0]; i != -1; i = next_search[i]) {
		if(invited[i] == 0)
			ret += val_L[i];
	}
	return ret;
}
int get_like(int idx) {
	int ret = 0;
	for(int i = 0; i < cover[idx].size(); i++) {
		int y = cover[idx][i];
		if(invited[y] == 0)
			ret += val_L[y];
		invited[y]++;
	}
	return ret;
}
void remove_like(int idx) {
	for(int i = 0; i < cover[idx].size(); i++) {
		int y = cover[idx][i];
		invited[y]--;
	}
}
void dfs(int idx, int like, int s) {
	if(s)
		max_like = max(max_like, like);
	if(idx == -1 || like + H() <= max_like)
		return ;
	if(invited[idx] == 0) {
		int f = get_like(idx);
		dfs(next_search[idx], like + f, 1);
		remove_like(idx);
	}
	dfs(next_search[idx], like, s);
}
void bfs(int idx) {
	int visited[105] = {};
	queue<int> Q;
	Q.push(idx), visited[idx] = 1;
	while(!Q.empty()) {
		int tn = Q.front();
		Q.pop();
		cover[idx].push_back(tn);
		for(int i = 0; i < dag[tn].size(); i++) {
			int y = dag[tn][i];
			if(visited[y] == 0) {
				visited[y] = 1;
				Q.push(y);
			}
		}
	}
}
int main() {
	int testcase, cases = 0;
	int n, m, x, y;
	int i, j, k;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		for(i = 0; i <= n; i++) {
			g[i].clear();
			dag[i].clear();
			cover[i].clear();
			val_L[i] = 0;
			invited[i] = 0;
		}
		for(i = 1; i <= n; i++) {
			scanf("%d %d", &L[i], &m);
			while(m--) {
				scanf("%d", &x);
				g[i].push_back(x);
			} 
		}
		// SCC
        memset(visited, 0, sizeof(visited));
        memset(in_stk, 0, sizeof(in_stk));
        for(i = 1; i <= n; i++) {
            if(!visited[i]) {
                findIdx = stkIdx = 0;
                scc(i);
            }
        }
        //
        for(i = 1; i <= n; i++) {
            x = contract[i];
            val_L[x] += L[i];
            for(vector<int>::iterator it = g[i].begin();
                it != g[i].end(); it++) {
                y = contract[*it];
                if(x != y)
                    dag[x].push_back(y);
            }
        }
        //
        int prev = -1;
        for(i = n; i >= 0; i--) {
        	next_search[i] = prev;
        	if(val_L[i] >= 0 && contract[i] == i)
        		prev = i;
        }
        for(i = 1; i <= n; i++)
        	bfs(i);
        max_like = -1;
        dfs(next_search[0], 0, 0);
        printf("Case #%d: ", ++cases);
        if(max_like < 0)
        	puts("Alas, sultan can't invite anyone!");
        else
        	printf("%d\n", max_like);
	}
	return 0;
}
