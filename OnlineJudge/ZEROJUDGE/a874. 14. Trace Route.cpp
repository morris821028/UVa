#include <bits/stdc++.h>
using namespace std;
const int MAXN = 64;
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		int f[MAXN][MAXN] = {}, w;
		int a, b;
		char s1[8], s2[8];
		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++)
				f[i][j] = 0x3f3f3f3f;
			f[i][i] = 0;
		}
		for (int i = 0; i < n; i++) {
			scanf("%s %s %d", s1, s2, &w);
			a = s1[0] - 'A', b = s2[0] - 'A';
			f[a][b] = f[b][a] = min(w, f[a][b]);
		}
		scanf("%s %s", s1, s2);
		a = s1[0] - 'A', b = s2[0] - 'A';
		for (int k = 0; k < 26; k++) {
			for (int i = 0; i < 26; i++) {
				for (int j = 0; j < 26; j++)
					f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
			}
		}
		if (f[a][b] != 0x3f3f3f3f)
			printf("%d\n", f[a][b]);
		else
			puts("NoRoute");
	}
	return 0;
}

