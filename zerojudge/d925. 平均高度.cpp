#include<stdio.h>
main() {
	int M, N, T, x, y, k, a, b;
	long long s;
	while(scanf("%d %d %d", &M, &N, &T) == 3) {
		s = 0;
		while(T--) {
			scanf("%d %d %d", &x, &y, &k);
			for(a = -1, s -= k; a <= 1; a++)
				for(b = -1; b <= 1; b++) {
					if(a == 0 && b == 0) continue;
					if(x+a >= 1 && x+a <= M && y+b >=1 && y+b <= N)
						s += k;
				}
		}
		printf("%.2lf\n", (double)s/(M*N));
	}
	return 0;
}
