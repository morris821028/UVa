#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, m, st;
	while (scanf("%d %d", &n, &m) == 2) {
		int A[n][m][2], B[n];
		for (int i = 0; i < n; i++) {
			B[i] = 0;
			for (int j = 0; j < m; j++) {
				scanf("%d %d", &A[i][j][0], &A[i][j][1]);
				if (A[i][j][0])
					B[i]++;
			}
		}
		scanf("%d", &st);
		int sum = 0;
		for (int i = 0; i < n; i++) {
			int cnt = A[i][st][1];
			sum = (sum + cnt)%20123;
			cnt %= B[i];
			if (cnt == 0)	cnt = B[i];
			while (cnt > 0) {
				if (A[i][st][0])
					cnt--;	
				if (cnt > 0)
					st = (st + 1)%m;			
			}
		}
		printf("%d\n", sum);
	}
	return 0;
}
