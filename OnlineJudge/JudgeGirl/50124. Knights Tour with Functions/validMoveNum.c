#include "validMoveNum.h"

static int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
static int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
int validMoveNum(int r, int c, int n, int visited[100][100]) {
	if (r < 0 || r >= n || c < 0 || c >= n || visited[r][c])
		return -1;
	int ret = 0;
	for (int i = 0; i < 8; i++) {
		int tx = r+dx[i], ty = c+dy[i];
		if (tx < 0 || tx >= n || ty < 0 || ty >= n || visited[tx][ty])
			continue;
		ret++;
	}
	return ret;
}
