#include <stdio.h>
#include <string.h>
char g[16][16], h[7][16][16];
const char pattern[3][16] = {" _ _ ", "|   |", "|_ _|"};
int ret;
void place(char h[][16], int x, int y) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == 0 && (j == 0 || j == 2 || j == 4))
				continue;
			h[x+i][y+j] = pattern[i][j];
		}
	}
}
int check(char h[][16]) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 9; j++)
			if (g[i][j] != h[i][j])
				return 0;
	return 1;
} 
void dfs(int idx) {
	if (check(h[idx])) {
		ret = 1;
		return;
	}
	if (idx == 6)  return;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j += 2) {
			memcpy(h[idx+1], h[idx], sizeof(h[idx]));
			place(h[idx+1], i, j);
			dfs(idx+1);
			if (ret)
				return;
		}
	}
}
int main() {
	int cases = 0;
	while (true) {
		for (int i = 0; i < 5; i++) {
			gets(g[i]);
			if (g[i][0] == '0')
				return 0;
		}
		memset(h, ' ', sizeof(h));
		ret = 0;
		dfs(0);
		printf("Case %d: %s\n", ++cases, ret ? "Yes" : "No");
	}
	return 0;
}
