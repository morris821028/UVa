#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
#define MAXN 1024
vector<int> g[MAXN];
char cmd[MAXN][16];
int N[MAXN], used[MAXN], instk[MAXN];
int loopflag, endflag;
void dfs(int u) {
	instk[u] = 1, used[u] = 1;
	for (int i = 0; i < g[u].size(); i++) {
		if (used[g[u][i]] == 0)
			dfs(g[u][i]);
		if (instk[g[u][i]] == 1)
			loopflag = 1;
	}
	instk[u] = 0;
}
int main() {
	int testcase, L;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &L);
		for (int i = 0; i <= L + 1; i++)
			g[i].clear();
		for (int i = 1; i <= L; i++) {
			scanf("%s", cmd[i]);
			if (cmd[i][0] == 'A') {
				g[i].push_back(i+1);
			} else if (cmd[i][0] == 'J') {
				scanf("%d", &N[i]);
				g[i].push_back(N[i]);
			} else if (cmd[i][0] == 'C') {
				scanf("%d", &N[i]);
				g[i].push_back(N[i]);
				g[i].push_back(i+1);
			}
		}
		memset(used, 0, sizeof(used));
		memset(instk, 0, sizeof(instk));
		loopflag = 0, endflag = 0;
		dfs(1);
		endflag = used[L + 1];
		if (loopflag == 0 && endflag == 1)
			puts("ALWAYS");
		else if (loopflag == 1 && endflag == 0)
			puts("NEVER");
		else
			puts("SOMETIMES");
	}
	return 0;
}
/*
3
3
A
A
J 1
5
A
J 4
J 5
C 3
A
4
A
A
C 2
A
*/
