#include <bits/stdc++.h>
using namespace std;

int n, g[16][16] = {};
const int dx[] = {0, 1, 1, 1};
const int dy[] = {1, 0, 1, -1};
int test(int x, int y, int k) {
	char c = g[x][y];
	int cnt = 0;
	while (x >= 0 && x < n && y >= 0 && y < n) {
		if (g[x][y] != c)
			return 0;
		cnt++;
		x += dx[k], y += dy[k];
	}
	return cnt >= 3;
}
int main() {
	scanf("%d", &n);
	while (getchar() != '\n');
	for (int i = 0; i < n; i++) {
		string line;
		getline(cin, line);
		stringstream sin(line);
		int x;
		while (sin >> x) {
			x--;
			g[i][x] = 1;
		}
	}
	int lines = 0;
	for (int i = 0; i < n; i++) {
		if (test(i, 0, 0))	lines++;
		if (test(0, i, 1))	lines++;
	}
	for (int i = 1; i < n-1; i++) {
		if (test(i, 0, 2))	lines++;
		if (test(0, i, 2))	lines++;
		if (test(i, n-1, 3))	lines++;
		if (test(0, i, 3))	lines++;
	}
	if (test(0, 0, 2))		lines++;
	if (test(0, n-1, 3))	lines++;
	printf("%d\n", lines);
	return 0;
}
