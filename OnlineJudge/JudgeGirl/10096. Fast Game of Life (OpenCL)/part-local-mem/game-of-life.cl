#define N %d
#define binN %d
#define CTYPE char


__kernel void simulate(__global CTYPE *IN,
        __global CTYPE *OUT) {
    int x = get_global_id(0);
	int y = get_global_id(1);
	int localX = get_local_id(0);
	int localY = get_local_id(1);
	int localSz = get_local_size(0);
	__local char g[16][16];
	const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	char t = IN[x * binN + y];
	g[localX][localY] = t;
	
	barrier(CLK_LOCAL_MEM_FENCE);
	int adj = 0;
	for (int i = 0; i < 8; i++) {
		int cx = localX + dx[i];
		int cy = localY + dy[i];
		int tx = x + dx[i];
		int ty = y + dy[i];
		if (tx < 0 || ty < 0 || tx >= N || ty >= N)
			continue;

		if (cx >= 0 && cx < localSz && cy >= 0 && cy < localSz)	{
			adj += g[cx][cy];
		} else {
			adj += IN[tx * binN + ty];
		}
	}
	OUT[x * binN + y] = (t == 0 && adj == 3) || (t == 1 && (adj == 2 || adj == 3));
}
