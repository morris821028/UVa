#include "nextMove.h"

static int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
static int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
int nextMove(int r, int c, int n, int visited[100][100]) {
	int ret = -1, mn = 9;
	for (int i = 0; i < 8; i++) {
		int lib = validMoveNum(r+dx[i], c+dy[i], n, visited);
		if (lib >= 0 && lib < mn)
			mn = lib, ret = i;
	}
	return ret;
}
