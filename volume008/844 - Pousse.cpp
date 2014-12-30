#include <stdio.h> 
#include <string.h>

char cmd[32767][64];
char g[128][128];
int n;
int isCompleted() {
	int Oline = 0, Xline = 0, cnt;
	char c;
	for (int i = 0; i < n; i++) {
		c = g[i][0], cnt = 0;
		for (int j = 0; g[i][0] == g[i][j] && j < n; cnt++, j++);
		if (cnt == n && c != ' ') {
			Oline += c == 'O';
			Xline += c == 'X';
		}
		c = g[0][i], cnt = 0;
		for (int j = 0; g[0][i] == g[j][i] && j < n; cnt++, j++);
		if (cnt == n && c != ' ') {
			Oline += c == 'O';
			Xline += c == 'X';
		}
	}
	return Oline == Xline ? 0 : (Oline < Xline ? -1 : 1);
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		int m = 0;
		while (scanf("%s", cmd[m]) == 1) {
			if (!strcmp(cmd[m], "QUIT"))
				break;
			m++;
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				g[i][j] = ' ';
		int ret = 0, turn = 0;
		for (int i = 0; i < m; i++, turn = !turn) {
			int x;
			sscanf(cmd[i]+1, "%d", &x);
			x--;
			if (cmd[i][0] == 'L') {
				int idx = 0;
				while (idx < n && g[x][idx] != ' ')	idx++;
				for (int i = idx; i > 0; i--)
					g[x][i] = g[x][i-1];
				g[x][0] = turn ? 'O' : 'X';
			}
			if (cmd[i][0] == 'R') {
				int idx = n-1;
				while (idx > 0 && g[x][idx] != ' ')	idx--;
				for (int i = idx; i < n-1; i++)
					g[x][i] = g[x][i+1];
				g[x][n-1] = turn ? 'O' : 'X';
			}
			if (cmd[i][0] == 'T') {
				int idx = 0;
				while (idx < n && g[idx][x] != ' ')	idx++;
				for (int i = idx; i > 0; i--)
					g[i][x] = g[i-1][x];
				g[0][x] = turn ? 'O' : 'X';
			}			
			if (cmd[i][0] == 'B') {
				int idx = n-1;
				while (idx > 0 && g[idx][x] != ' ')	idx--;
				for (int i = idx; i < n-1; i++)
					g[i][x] = g[i+1][x];
				g[n-1][x] = turn ? 'O' : 'X';
			}
//			for (int i = 0; i < n; i++, puts(""))
//				for (int j = 0; j < n; j++)
//					putchar(g[i][j]);
//			puts("---");
			if (ret = isCompleted())
				break;
		}
		if (ret)
			puts(ret < 0 ? "X WINS" : "O WINS");
		else
			puts("TIE GAME");
		if (testcase)
			puts("");
	}
	return 0;
}
/*
2

4
L2
T2
L2
B2
R2
QUIT

4
L2
T2
L2
B2
R2
T1
L2
QUIT
*/
