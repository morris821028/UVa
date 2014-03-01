#include<stdio.h>
main() {
	int N, M, a, C = 0;
	scanf("%d", &N);
	while(N--) {
		scanf("%d", &M);
		int x, y, bx = 10000, sum = 0;
		for(a = 0; a < M; a++) {
			scanf("%d %d", &x, &y), x = x*60 + y;
			if(x < bx) bx = x;
			sum += x;
		}
		sum /= M;
		printf("Track %d:\n", ++C);
		printf("Best Lap: %d minute(s) %d second(s).\n", bx/60, bx%60);
		printf("Average: %d minute(s) %d second(s).\n\n", sum/60, sum%60);
	}
	return 0;
}
