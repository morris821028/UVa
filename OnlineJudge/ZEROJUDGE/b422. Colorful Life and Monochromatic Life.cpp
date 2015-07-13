#include <bits/stdc++.h> 
using namespace std;

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		printf("%d %d\n", n, m);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				int r, g, b, w;
				scanf("%d %d %d", &r, &g, &b);
				w = (int) round((r + g + b)/3.0);
				printf("%d %d %d%c", w, w, w, j == n-1 ? '\n' : ' ');
			}
		}
	}
	return 0;
}
