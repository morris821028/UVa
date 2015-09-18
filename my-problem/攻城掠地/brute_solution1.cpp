#include <bits/stdc++.h>
using namespace std;

char A[1024][1024];
int main() {
	int R, C, Q;
	while (scanf("%d %d", &R, &C) == 2) {
		int lx, ly, rx, ry;
		for (int i = 1; i <= R; i++) {
			for (int j = 1; j <= C; j++)
				A[i][j] = 1;
		}
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
			int cnt = 0;
			for (int p = lx; p <= rx; p++)
				for (int q = ly; q <= ry; q++)
					if (A[p][q])
						cnt++;
			printf("%d", cnt);
			for (int p = lx; p <= rx; p++)
				for (int q = ly; q <= ry; q++)
					if (A[p][q])
						printf(" (%d, %d)", p, q), A[p][q] = 0;
			puts("");
		}
	}
	return 0;
}
/*
5 4
3
2 2 3 3
2 3 4 4
3 3 4 4

1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
=>
1 1 1 1
1     1
1     1
1 1 1 1
1 1 1 1
=>
1 1 1 1
1     
1 
1 1   
1 1 1 1
*/
