#include <stdio.h> 
#include <algorithm>
using namespace std;

char g[128][128];
int n, m;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
void removeAnimal(int x, int y, int v) {
	g[x][y] = '.';
	int tx, ty;
	for (int i = 0; i < 4; i++) {
		tx = x + dx[i], ty = y + dy[i];
		if (tx < 0 || ty < 0 || tx >= n || ty >= m)
			continue;
		if (g[tx][ty] == v)
			removeAnimal(tx, ty, v);
	}
}
int identifyAnimal(int x, int y) {
	char v = g[x][y];
	int lx, ly, rx = x, ry = y, w, h;
	while (rx+1 < n && g[rx+1][ry] == v)	rx++;
	while (ry+1 < m && g[rx][ry+1] == v)	ry++;
	lx = rx, ly = ry;
	while (lx-1 >= 0 && g[lx-1][ly] == v)	lx--;
	while (ly-1 >= 0 && g[lx][ly-1] == v)	ly--;
	
	int isShark = 0, isDolphin = 0;
	for (int i = ly; i <= ry; i++) {
		if (lx - 1 >= 0 && g[lx-1][i] == v)	isShark = 1;
		if (rx + 1 < n && g[rx+1][i] == v)	isShark = 1;
	}
	for (int i = lx; i <= rx; i++) {
		if (ly - 1 >= 0 && g[i][ly-1] == v)	isShark = 1;
		if (ry + 1 < m && g[i][ry+1] == v)	isShark = 1;
	}
	w = ry - ly + 1, h = rx - lx + 1;
	if (w > h)	swap(w, h);
	removeAnimal(lx, ly, v);
	if (isShark)	return 7;
	if (w == 1 && h == 1)
		return 0; // sardines
	if (w == 1 && h == 2)
		return 1; // mackerel
	if (w == 1)	
		return 2; // salmons
	if (w == h)
		return 4; // turtles
	if (w == 2 && h > 2)
		return 3; // grouper
	if (w == 3 && h > 3)
		return 5; // dolphin
	return 6; // whales
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		while (getchar() != '\n');
		for (int i = 0; i < n; i++)
			scanf("%s", g[i]);
		
		int kinds[16] = {};
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (g[i][j] >= 'a' && g[i][j] <= 'z') {
					int t = identifyAnimal(i, j);
					kinds[t]++;
				}
			}
		}
		for (int i = 0; i < 8; i++)
			printf("%d%c", kinds[i], i == 7 ? '\n' : ' ');
		if (testcase)
			puts("");
	}
	return 0;
}
