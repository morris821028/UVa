#include <stdio.h>
int f(int n, int m) {
	static int C[16][16] = {}, Cf = 0;
	if (!Cf) {
		C[0][0] = 1;
		for (int i = 1; i < 16; i++) {
			C[i][0] = 1;
			for (int j = 1; j <= i; j++)
				C[i][j] = C[i-1][j-1] + C[i-1][j];
		}
	}
	int ret = 0;
	for (int i = 0; i <= m; i++)
		ret += C[n][i];
	return ret;
}
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2)
		printf("%d\n", f(n, m));
	return 0;
}
