#include <bits/stdc++.h>
using namespace std;

int G[128][128];
int N, M, Q;
const char dir[] = "NESW";
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
void draw(int sx, int sy, char sd[], int sv) {
	int d = 0;
	for (int i = 0; i < 4; i++) {
		if (sd[0] == dir[i])
			d = i;
	}
	G[sx][sy]++;
	for (int i = 1; ; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < i; k++) {
				sx += dx[d], sy += dy[d];
				if (sx > N || sy > M || sx <= 0 || sy <= 0)
					return ;
				G[sx][sy]++;
				sv--;
				if (sv == 0)	return ;
			}
			d = (d + 1)%4;
		}
	}
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &N, &M, &Q);
		memset(G, 0, sizeof(G));
		for (int i = 0; i < Q; i++) {
			char s[128];
			int x, y, v;
			scanf("%d %d %s %d", &x, &y, s, &v);
			draw(x, y, s, v);
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++)
				printf("%d%c", G[i][j], j == M ? '\n' : ' ');
		}
		puts("---");
	}
	return 0;
}
/*
2
7 8 3
1 2 E 2
6 3 N 25
4 6 E 21
4 3 2
1 1 N 3
4 2 W 3
*/
