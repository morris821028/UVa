#include <stdio.h> 
#include <vector>
#include <assert.h>
using namespace std;

int N, X[16] = {}, Y[16] = {};
int g[16][16] = {};
vector<int> row[16];
vector<int> f[1024];
int used[1024] = {};
int dfs(int idx) {
	if (idx == N) {
		for (int i = 0; i < N; i++, puts("")) {
			for (int j = 0; j < N; j++) {
				if (j) putchar(' ');
				printf("%3d", g[j][i]);
			}
		}
		return 1;
	}
	for (int p = 0; p < N; p++) {
		for (int q = p + 1; q < N; q++) {
			if (row[p].size() == 2 || row[q].size() == 2)
				continue;
			for (int i = 0; i < f[X[idx]].size(); i++) {
				int a, b, ok = 1;
				a = f[X[idx]][i];
				b = X[idx]/a;
				if (used[a] || used[b] || a == b) 
					continue;
				g[idx][p] = a, g[idx][q] = b;
				used[a] = used[b] = 1;
				row[p].push_back(a);
				row[q].push_back(b);
				if (row[p].size() == 2 && row[p][0] * row[p][1] != Y[p]) 
					ok = 0;
				if (row[q].size() == 2 && row[q][0] * row[q][1] != Y[q]) 
					ok = 0;
				if (Y[p]%a || Y[q]%b)	
					ok = 0;
				if (ok) {
					if (dfs(idx + 1)) {
						g[idx][p] = 0, g[idx][q] = 0;
						row[p].pop_back();
						row[q].pop_back();
						used[a] = used[b] = 0;
						return 1;
					}
				}
				g[idx][p] = 0, g[idx][q] = 0;
				used[a] = used[b] = 0;
				row[p].pop_back();
				row[q].pop_back();
			}	
		}
	}
	return 0;
}
int main() {
	for (int i = 1; i < 1024; i++) {
		for (int j = 1; j <= i; j++) {
			if (i%j == 0)
				f[i].push_back(j);
		}
	}
	while (scanf("%d", &N) == 1 && N) {
		for (int i = 0; i < N; i++)
			scanf("%d", &X[i]);
		for (int i = 0; i < N; i++)
			scanf("%d", &Y[i]);
		assert(dfs(0) == 1);
		puts("");
	}
	return 0;
}
/*
2
2 12
3 8
3
5 8 18
2 30 12
5
54 6 12 20 88
18 9 132 32 10
10
2 12 30 56 90 132 182 240 306 380
19 36 51 64 75 84 91 96 99 200
0
*/
