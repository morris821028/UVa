#include <stdio.h> 
#include <string.h>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

map<int, int> RX, RY;
vector<int> VX, VY;
int sx, sy, ex, ey, M, N, Q;
int x1[128], y1[128], x2[128][2], y2[128][2], x3[128][2], y3[128][2];
int g[605][605];
void record(int x, int y) {
	for (int i = -1; i <= 1; i++) {
		RX[min(max(x + i, -1000000000), 1000000000)] = 0;
		RY[min(max(y + i, -1000000000), 1000000000)] = 0;
	}
}
void buildGrid() {
	VX.clear(), VY.clear();
	for (map<int, int>::iterator it = RX.begin();
		it != RX.end(); it++) {
		it->second = VX.size(), VX.push_back(it->first);
	}
	for (map<int, int>::iterator it = RY.begin();
		it != RY.end(); it++) {
		it->second = VY.size(), VY.push_back(it->first);
	}
	
	memset(g, 0, sizeof(g));
	int ux, uy, vx, vy;
	for (int i = 0; i < M; i++) {
		ux = RX[x1[i]], uy = RY[y1[i]];
		g[ux][uy] = 1;
	}
	for (int i = 0; i < N; i++) {
		ux = RX[x2[i][0]], uy = RY[y2[i][0]];
		vx = RX[x2[i][1]], vy = RY[y2[i][1]];
		if (ux > vx)	swap(ux, vx);
		if (uy > vy)	swap(uy, vy);
		for (int p = ux; p <= vx; p++)
			for (int q = uy; q <= vy; q++)
				g[p][q] = 1;
	}
	for (int i = 0; i < Q; i++) {
		ux = RX[x3[i][0]], uy = RY[y3[i][0]];
		vx = RX[x3[i][1]], vy = RY[y3[i][1]];
		if (ux > vx)	swap(ux, vx);
		if (uy > vy)	swap(uy, vy);
		for (int p = ux; p <= vx; p++)
			for (int q = uy; q <= vy; q++)
				g[p][q] = 1;
	}
//	printf("   |");
//	for (int i = 0; i < VY.size(); i++)
//		printf("%3d|", VY[i]);
//	puts("");
//	for (int i = 0; i < VX.size(); i++, puts("")) {
//		printf("%3d|", VX[i]);
//		for (int j = 0; j < VY.size(); j++) {
//			printf("%3d ", g[i][j]);
//		}
//	}
}
long long dist2pt(int sx, int sy, int ex, int ey) {
	long long dx = abs(VX[sx] - VX[ex]);
	long long dy = abs(VY[sy] - VY[ey]);
	return dx + dy;
}
long long dist[605][605];
int inq[605][605];
long long spfa(int sx, int sy, int ex, int ey) {
	memset(dist, 63, sizeof(dist));
	memset(inq, 0, sizeof(inq));
	long long INF = dist[0][0];
	queue<int> X, Y;
	int x, y, tx, ty;
	
	dist[sx][sy] = 0;
	X.push(sx), Y.push(sy);
	while (!X.empty()) {
		x = X.front(), X.pop();
		y = Y.front(), Y.pop();
		inq[x][y] = 0;
		for (int i = 0; i < 4; i++) {
			tx = x + dx[i], ty = y + dy[i];
			if (tx < 0 || ty < 0 || tx >= VX.size() || ty >= VY.size())
				continue;
			if (g[tx][ty])
				continue;
			if (dist[tx][ty] > dist[x][y] + dist2pt(x, y, tx, ty)) {
				dist[tx][ty] = dist[x][y] + dist2pt(x, y, tx, ty);
				if (!inq[tx][ty]) {
					if (dist[tx][ty] <= dist[ex][ey])
						inq[tx][ty] = 1, X.push(tx), Y.push(ty);
				}
			}
		}
	}
	return dist[ex][ey] == INF ? -1 : dist[ex][ey];
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		
		RX.clear(), RY.clear();
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
		scanf("%d %d %d", &M, &N, &Q);
		
		record(sx, sy), record(ex, ey);
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &x1[i], &y1[i]);
			record(x1[i], y1[i]);
		}
		for (int i = 0; i < N; i++) {
			scanf("%d %d %d %d", &x2[i][0], &y2[i][0], &x2[i][1], &y2[i][1]);
			record(x2[i][0], y2[i][0]);
			record(x2[i][1], y2[i][1]);
		}
		for (int i = 0; i < Q; i++) {
			scanf("%d %d %d %d", &x3[i][0], &y3[i][0], &x3[i][1], &y3[i][1]);
			record(x3[i][0], y3[i][0]);
			record(x3[i][1], y3[i][1]);
		}
		
		buildGrid();
		long long ret = spfa(RX[sx], RY[sy], RX[ex], RY[ey]);
		printf("Case %d: ", ++cases);
		if (ret >= 0)	printf("%lld\n", ret);
		else			printf("Impossible\n");
	}
	return 0;
}
/*
2
-1 0 1 0
0 1 0
0 -1000000000 0 1000000000
-2 -1000000000 2 1000000000
0 2 0
-1 -1000000000 -1 999999999
1 -999999999 1 1000000000
*/
