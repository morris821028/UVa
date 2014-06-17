#include <stdio.h> 

int main() {
	scanf("%*d");
	for(int x, y; scanf("%d %d", &x, &y) == 2;) {
		long long A[105][5] = {};
		A[1][0] = x;
		for(int i = 2; i <= y; i++) {
			A[i][0] = A[i-1][2] + A[i-1][3];
			A[i][1] = A[i-1][0];
			A[i][2] = A[i-1][1];
			A[i][3] = A[i-1][2];
			A[i][4] = A[i-1][3];
		}
		printf("%lld\n", A[y][0]+A[y][1]+A[y][2]+A[y][3]+A[y][4]);
	}
	return 0;
}
