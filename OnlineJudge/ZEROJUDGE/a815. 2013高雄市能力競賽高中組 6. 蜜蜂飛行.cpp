#include <bits/stdc++.h>
using namespace std;
const int MAXN = 310;
int N, M, border[MAXN][MAXN];
char g[MAXN][MAXN];
const int dx[] = {0, 0, 1, 1, -1, -1};
const int dy[] = {1, -1, 0, -1, 0, 1};
const int MAXVN = 131072;
int parent[MAXVN], weight[MAXVN];
void init(int n) {
    for(int i= 0; i <= n; i++)
        parent[i] = i, weight[i] = 1;
}
int findp(int x) {
    return x == parent[x] ? x : (parent[x]=findp(parent[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if (x == y) return 0;
    if(weight[x] > weight[y])
        weight[x] += weight[y], parent[y] = x;
    else
        weight[y] += weight[x], parent[x] = y;
    return 1;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++)
			scanf("%s", g[i]);
		init(N*M + 10);
		int LL = N*M+1, RR = N*M+2;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++)
				border[i][j] = 0;
		}
		for (int i = 1; i < M; i++) {
			if (g[0][i] == 'O')
				joint(RR, 0*M+i);
			if (g[N-1][i-1] == 'O')
				joint(LL, (N-1)*M+i-1);
			border[N-1][i-1] |= 1;
			border[0][i] |= 2;
		}
		for (int i = 1; i < N; i++) {
			if (g[i][0] == 'O')
				joint(LL, i*M+0);
			if (g[i-1][M-1] == 'O')
				joint(RR, (i-1)*M+M-1);
			border[i][0] |= 1;
			border[i-1][M-1] |= 2;
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (g[i][j] == 'O') {
					int x, y, tx, ty;
					x = i, y = j;
					for (int k = 0; k < 6; k++) {
						tx = x + dx[k];
						ty = y + dy[k];
						if (tx < 0 || ty < 0 || tx >= N || ty >= M)
							continue;
						if (g[tx][ty] == 'O')
							joint(x*M+y, tx*M+ty);
					}
				}
			}
		}
		
		if (findp(LL) == findp(RR)) {
			puts("0");
			continue;
		}
		
		int ret = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (g[i][j] == '.') {
					int x, y, tx, ty, test = 0;
					x = i, y = j;
					for (int k = 0; k < 6; k++) {
						tx = x + dx[k];
						ty = y + dy[k];
						if (tx < 0 || ty < 0 || tx >= N || ty >= M)
							continue;
						if (g[tx][ty] == 'O') {
							if (findp(tx*M+ty) == findp(LL))
								test |= 1;
							if (findp(tx*M+ty) == findp(RR))
								test |= 2;
						}
					}
					if (border[i][j])
						test |= border[i][j];
					if (test == 3)
						ret = 1, i = N, j = M;
				}
			}
		}
		puts(ret ? "1" : "2");
	}
	return 0;
}
/*
999
2 2
..
..
4 3
.O.
.O.
.O.
.O.
4 3
...
OO.
...
OO.
4 3
.OO
OOO
OOO
OO.
*/

