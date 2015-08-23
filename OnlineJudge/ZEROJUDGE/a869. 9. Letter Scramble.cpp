#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	char g[16][16][16];
	int C[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++)
			scanf("%s", g[i][j]);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		char s1[16], s2[16];
		int x, y, dx, dy;
		scanf("%s %d %d %s", s1, &x, &y, s2);
		if (s2[0] == 'H')	dx = 0, dy = 1;
		else				dx = 1, dy = 0;
		int p = 0, q = 1;
		for (int j = 0; s1[j]; j++) {
			if (g[x][y][0] == '[')
				p += C[s1[j] - 'A'];
			else if (g[x][y][1] == 'L')
				p += C[s1[j] - 'A'] * (g[x][y][0] - '0');
			else
				p += C[s1[j] - 'A'], q *= g[x][y][0] - '0';
			x += dx, y += dy;
		}
		printf("%s %d\n", s1, p * q);
	}
	return 0;
}
