#define N %d
#define binN %d
#define localN %d
#define CTYPE char

inline void move_border(__local char g[][localN+2], __global CTYPE *IN,
	int localX, int localY, int localSz, int x, int y) {
	if (localX == 1) {
		g[localX-1][localY] = IN[(x-1) * binN + y];
		if (localY == 1)
			g[localX-1][localY-1] = IN[(x-1) * binN + (y-1)];
		if (localY == localSz)
			g[localX-1][localY+1] = IN[(x-1) * binN + (y+1)];
	}
	if (localY == 1)	g[localX][localY-1] = IN[x * binN + (y-1)];
	if (localY == localSz)	g[localX][localY+1] = IN[x * binN + (y+1)];
	if (localX == localSz) {
		g[localX+1][localY] = IN[(x+1) * binN + y];
		if (localY == 1)
			g[localX+1][localY-1] = IN[(x+1) * binN + (y-1)];
		if (localY == localSz)
			g[localX+1][localY+1] = IN[(x+1) * binN + (y+1)];
	}
}
__kernel void simulate(__global CTYPE *IN,
        __global CTYPE *OUT) {
    int x = get_global_id(0)+1;
	int y = get_global_id(1)+1;
	int localX = get_local_id(0)+1;
	int localY = get_local_id(1)+1;
	int localSz = get_local_size(0);

	__local char g[localN+2][localN+2];

	const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

	// move itself to local
	char t = IN[x * binN + y];
	g[localX][localY] = t;
	// move border to local
	move_border(g, IN, localX, localY, localSz, x, y);
	barrier(CLK_LOCAL_MEM_FENCE);
	
	if (x > N || y > N)	return ;

	int adj = 0;
	for (int i = 0; i < 8; i++) {
		int cx = localX + dx[i];
		int cy = localY + dy[i];
		adj += g[cx][cy];
	}
	OUT[x * binN + y] = (t == 0 && adj == 3) || (t == 1 && (adj == 2 || adj == 3));
}
