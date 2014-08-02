#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

int dfsMinExp(int u, int p, vector<int> g[]) {
	vector<int>	branch;
	for(int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if(v == p)	continue;
		branch.push_back(dfsMinExp(v, u, g));
	}
	sort(branch.begin(), branch.end());

//	string exp = "";
//	for(int i = 0; i < branch.size(); i++)
//		exp += branch[i];	
//	return "(" + exp + ")";	
	int a = 63689, b = 378551;
	int ret = 0;
	branch.push_back(1);
	for(int i = 0; i < branch.size(); i++)
		ret = ret * a + branch[i], a *= b;
	return ret;
}
vector<int> getTreeMinExp(vector<int> g[], int n) {
	if(n == 1)	return vector<int>({1});
	int deg[10005] = {}, u, v;
	int topo[10005] = {}, idx = 0;
	queue<int> Q;
	for(int i = 1; i <= n; i++) {
		deg[i] = g[i].size();
		if(deg[i] == 1)	Q.push(i);
	}
	while(!Q.empty()) {
		u = Q.front(), Q.pop();
		topo[idx++] = u;
		for(int i = 0; i < g[u].size(); i++) {
			v = g[u][i];
			if(--deg[v] == 1)
				Q.push(v);
		}
	}
	vector<int> ret;
	ret.push_back(dfsMinExp(topo[idx-1], -1, g));
	ret.push_back(dfsMinExp(topo[idx-2], -1, g));
	return ret;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int n, x, y;
	vector<int> g1[65536], g2[65536];
	while(scanf("%d", &n) == 1) {
		for(int i = 1; i <= n; i++)
			g1[i].clear(), g2[i].clear();
		for(int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			g1[x].push_back(y);
			g1[y].push_back(x);
		}
		for(int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			g2[x].push_back(y);
			g2[y].push_back(x);
		}
		vector<int> hash1 = getTreeMinExp(g1, n);
		vector<int> hash2 = getTreeMinExp(g2, n);
		int same = 0;
		for(int i = 0; i < hash1.size(); i++)
			for(int j = 0; j < hash2.size(); j++)
				same |= hash1[i] == hash2[j];
		puts(same ? "S" : "N");
//		printf("%d %d\n", hash1, hash2);
	}
	return 0;
}
/*
8
2 1
3 2
4 3
5 2
6 5
7 5
8 1
2 1
3 2
4 2
5 3
6 1
7 4
8 3
*/
