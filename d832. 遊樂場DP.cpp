#include<stdio.h>
main() {
	int n, m, a, b;
	while(scanf("%d %d", &n, &m) == 2) {
		int A[10001] = {};
		for(a = 0; a < n; a++)
			scanf("%d", &A[a]);
		int max[2][10001] = {}, mmax[10001] = {};
		max[0][0] = A[0], mmax[0] = A[0];
		for(a = 1; a < n; a++) {
			if(max[0][a-1] > 0)	max[0][a] = max[0][a-1] + A[a];
			else max[0][a] = A[a];
			if(max[0][a] > mmax[a-1]) mmax[a] = max[0][a];
			else mmax[a] = mmax[a-1];
		}
		for(a = 1; a < 2; a++) {
			for(b = 0; b < n; b++) max[0][b] = mmax[b];
			max[1][a] = max[0][a-1] + A[a];
			mmax[a] = max[1][a];
			for(b = a+1; b < n; b++) {
				if(max[0][b-1] > max[1][b-1])
					max[1][b] = max[0][b-1] + A[b];
				else max[1][b] = max[1][b-1] + A[b];
				if(max[1][b] > mmax[b-1]) mmax[b] = max[1][b];
				else mmax[b] = mmax[b-1];
			}
		}
		printf("%d\n", mmax[n-1]);
	}
	return 0;
}
/*
http://www.cppleyuan.com/viewthread.php?tid=1240
*/
