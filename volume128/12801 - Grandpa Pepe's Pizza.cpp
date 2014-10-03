#include <stdio.h> 
#include <algorithm>
using namespace std;
int main() {
	int n, m, A[65536];
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < m; i++)
			scanf("%d", &A[i]);
		A[m] = A[0] + n;
		int ret = 0, div = n/m;
		for (int i = A[0]; i < A[1]; i++) {
			int d = i, ok = 1;
			for (int j = 1; j <= m; j++) {
//				printf("(%d %d] %d\n", d, d+div, A[j]);
				if (d < A[j] && A[j] <= d + div)
					d += div;
				else {
					ok = 0;
					break;
				}
			}
//			puts("");
			if (ok) {
				ret = 1;
				break;
			}
		}
		puts(ret ? "S" : "N");
	}
	return 0;
}
/*
12 3
2 8 11
12 4
4 5 7 11
*/
