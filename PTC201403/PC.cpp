#include <stdio.h> 
#include <string.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;
int g[35][35], n;
int used[35] = {}, flag;
void dfs(int nd, int dep, int st) {
	if(flag || dep >= 4)
		return;
	if(dep == 3) {
		if(g[nd][st])
			flag = 1;
		return;
	}
	used[nd] = 1;
	for(int i = 0; i < n; i++) {
		if(used[i] == 0 && g[nd][i]) {
			dfs(i, dep+1, st);
		}
	}
	used[nd] = 0;
}
int main() {
	while(scanf("%d", &n) == 1 && n) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				scanf("%d", &g[i][j]);
			}
		}
		flag = 0;
		for(int i = 0; i < n; i++) {
		memset(used, 0, sizeof(used));
			dfs(i, 0, i);
		}
		puts(flag ? "yes" : "no");
	}
	return 0;
}
/*
5
0 1 0 1 1
1 0 1 1 0
0 1 0 1 0
1 1 1 0 1
1 0 0 1 0
5
0 1 0 0 1
1 0 1 0 0
0 1 0 1 0
0 0 1 0 1
1 0 0 1 0
*/
