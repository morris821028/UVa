#include<stdio.h>
#include<string.h>
#define oo 40000
int Trea[21], n, m;
int map[21][21], Ans, F[21][21];
int next[21];
void Floyd() {
	int a, b, c;
	for(a = 1; a <= n; a++) {
		for(b = 1; b <= n; b++) {
			F[a][b] = map[a][b];
			if(F[a][b] == 0)	F[a][b] = oo;
			if(a == b) F[a][b] = 0;
		}
	}
	for(a = 1; a <= n; a++)
		for(b = 1; b <= n; b++)
			for(c = 1; c <= n; c++)
				if(F[b][a]+F[a][c] < F[b][c])
					F[b][c] = F[b][a]+F[a][c];
	
}
int H(int now) {
	return F[now][n];
}
void DFS(int now, int find, int L) {
	if(find == m) {
		if(L+H(now) < Ans) Ans = L+H(now);
		return;
	}
	if(L+H(now)+(m-find-1) >= Ans)	return;
	int a, pre = 0;
	for(a = next[0]; a; pre = a, a = next[a]) {
		if(F[now][Trea[a]]) {
			next[pre] = next[a];
			DFS(Trea[a], find+1, L+F[now][Trea[a]]);
			next[pre] = a;
		}
	}
}
main() {
	while(scanf("%d %d", &n, &m) == 2) {
		memset(Trea, 0, sizeof(Trea));
		int a, b, find = 0, x;
		for(a = 1; a <= m; a++)
			scanf("%d", &Trea[a]);
		for(a = 0; a < m; a++)
			next[a] = a+1;
		next[m] = 0;
		for(a = 1; a <= n; a++)
			for(b = 1; b <= n; b++)
				scanf("%d", &map[a][b]);
		Floyd();
		if(Trea[1] == 1)	find++, next[0] = next[1];
		Ans = oo, DFS(1, find, 0);
		printf("%d\n", Ans);
	}
	return 0;
}
