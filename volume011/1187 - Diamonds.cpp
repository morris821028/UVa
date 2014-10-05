#include <stdio.h> 
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main() {
	int R, C, n = 0;
	int A[32767], Dx[32767], Dy[32767];
	scanf("%d %d", &R, &C);
	while (scanf("%d %d", &Dx[n], &Dy[n]) == 2) {
		if (Dx[n] < 0 || Dx[n] >= C || Dy[n] < 0 || Dy[n] >= R)
			continue;
		n++;
	}
	int Rmin[32767], Pmax[32767];
	for (int i = 1; i <= n; i++)
		Rmin[i] = 0, Pmax[i] = 0;
	for (int i = 0; i < C; i++) {
		for (int j = 0; j < R; j++) {
			for (int k = 0; k < n; k++)
				A[k] = abs(Dx[k] - i) + abs(Dy[k] - j);
			sort(A, A+n);
//			printf("(%d, %d) ", i, j);
//			for (int k = 0; k < n; k++)
//				printf("%d ", A[k]);
//			puts("");
			for (int k = 0; k < n; k++) {
				int base = k;
				while (k+1 < n && A[base] == A[k+1])
					k++;
				for (int p = k; p >= base; p--) {
					if (max(A[k], 1) > Rmin[p+1]) {
						Rmin[p+1] = max(A[k], 1);
					}
				}
				Pmax[A[k]] = max(Pmax[A[k]], k+1);
			}
		}
	}
	for (int i = 1; i < 32767; i++)
		Pmax[i] = max(Pmax[i-1], Pmax[i]);
	puts("Pmin  Rmin(Pmin)  Pmax(Pmin)");
	for (int i = 1; i <= n; i++) {
		if (i+1 <= n && Rmin[i] == Rmin[i+1])
			continue;
		printf("%4d  %10d  %10d\n", i, Rmin[i], Pmax[Rmin[i]]);
	}
	return 0;
}
