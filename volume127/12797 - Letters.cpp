#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;

int N, letter_cnt[128], letter_used[128];
int used[128][128] = {}, dist[128][128], testcase = 0, ret;
char g[128][128];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
void dfs(int idx) {
	if (idx == 10) {
		queue<int> X, Y;
		int tx, ty, x, y;
		if (letter_used[g[0][0]] == 0)
			return;
		testcase++;
		X.push(0), Y.push(0);
		used[0][0] = testcase;
		dist[0][0] = 1;
		while (!X.empty()) {
			x = X.front(), X.pop();
			y = Y.front(), Y.pop();
			if (x == N-1 && y == N-1) {
				ret = min(ret, dist[x][y]);
				return;
			}
			for (int i = 0; i < 4; i++) {
				tx = x + dx[i], ty = y + dy[i];
				if (tx < 0 || ty < 0 || tx >= N || ty >= N)
					continue;
				if (used[tx][ty] == testcase || letter_used[g[tx][ty]] == 0)
					continue;
				used[tx][ty] = testcase;
				dist[tx][ty] = dist[x][y] + 1;
				X.push(tx), Y.push(ty);
			}
		}
		return ;
	}
	int c = 0;
	if (letter_cnt[idx + 'a']) {
		letter_used[idx + 'a'] = 1;
		dfs(idx+1);
		letter_used[idx + 'a'] = 0;
		c++;
	}
	if (letter_cnt[idx + 'A']) {
		letter_used[idx + 'A'] = 1;
		dfs(idx+1);
		letter_used[idx + 'A'] = 0;
		c++;
	}
	if (c == 0)
		dfs(idx+1);
}
int main() {
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++)
			scanf("%s", g[i]);
		memset(letter_cnt, 0, sizeof(letter_cnt));
		memset(letter_used, 0, sizeof(letter_used));
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				letter_cnt[g[i][j]]++;
		ret = 0x3f3f3f3f;
		dfs(0);
		printf("%d\n", ret == 0x3f3f3f3f ? -1 : ret);
	}
	return 0;
}
/*
6
DdaAaA
CBAcca
eEaeeE
bBbabB
DbDdDc
fFaAaC
7
aAaaaaa
aAaaaAa
aAaaaAA
aaAaAaa
AaAaaAa
aaAAaAa
aaaaaAa
*/
