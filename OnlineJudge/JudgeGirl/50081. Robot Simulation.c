#include <stdio.h>

int main() {
	int n, m, cmd;
	int x = 0, y = 0;
	scanf("%d %d", &n, &m);
	printf("0\n0\n");
	while (scanf("%d", &cmd) == 1) {
		int t = cmd%5;
		if (t == 0)
			continue;
		int tx = x, ty = y;
		if (t == 1)			tx += cmd;
		else if (t == 2)	tx -= cmd;
		else if (t == 3)	ty += cmd;
		else				ty -= cmd;
		if (tx < 0 || ty < 0 || tx >= n || ty >= m)			
			continue;
		x = tx, y = ty;
		printf("%d\n%d\n", x, y);
	}
	return 0;
}
