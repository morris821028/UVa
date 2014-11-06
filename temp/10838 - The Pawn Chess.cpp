#include <stdio.h> 
#include <algorithm>
using namespace std;

struct state {
	char g[4][5];
	int isEnd() {
		int b = 0, w = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)  {
				if (g[i][j] == 'p')
					b++;
				if (g[i][j] == 'P')
					w++;
			}
		}
		if (b == 0 || w == 0)	return 1;
		for (int i = 0; i < 4; i++) {
			if (g[0][i] == 'P')	return 1;
			if (g[3][i] == 'p')	return 1;
		}
		return 0;
	}
};
int alpha_beta(state board, int depth, int alpha, int beta) {
	if (board.isEnd())
		return depth%2 == 0 ? -depth : depth;
	int movable = 0;
	if (depth%2 == 0) { // first player
		for (int i = 1; i < 4; i++)  {
			for (int j = 0; j < 4; j++) {
				if (board.g[i][j] == 'P') {
					for (int k = j - 1; k <= j + 1; k++) {
						if (k < 0 || k >= 4)
							continue;
						if ((k != j && board.g[i-1][k] == 'p') || (k == j && board.g[i-1][k] == '.')) {
							state s = board;
							s.g[i][j] = '.', s.g[i-1][k] = 'P';
							alpha = max(alpha, alpha_beta(s, depth - 1, alpha, beta));
							if (beta <= alpha)
								return alpha;
							movable = 1;
						}
					}
				}
			}
		}
		if (!movable)	return -depth;
		return alpha;
	} else {
		for (int i = 0; i < 3; i++)  {
			for (int j = 0; j < 4; j++) {
				if (board.g[i][j] == 'p') {
					for (int k = j - 1; k <= j + 1; k++) {
						if (k < 0 || k >= 4)
							continue;
						if ((k != j && board.g[i+1][k] == 'P') || (k == j && board.g[i+1][k] == '.')) {
							state s = board;
							s.g[i][j] = '.', s.g[i+1][k] = 'p';
							beta = min(beta, alpha_beta(s, depth - 1, alpha, beta));
							if (beta <= alpha)
								return beta;
							movable = 1;
						}
					}
				}
			}
		}
		if (!movable)	return depth;
		return beta;
	}
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		state init;
		for (int i = 0; i < 4; i++)
			scanf("%s", init.g[i]);
		int ret = alpha_beta(init, 36, -9999, 9999);
		if (ret >= 0)
			printf("white (%d)\n", 36 - ret);
		else
			printf("black (%d)\n", 36 + ret);
	}
	return 0;
}
/*
2

.ppp
....
.PPP
....

...p
...p
pP.P
...P
*/
