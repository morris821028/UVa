#include<stdio.h>
main() {
	int I, C, a, b, c;
	while(scanf("%d %d", &I, &C) == 2) {
		int v, w, t;
		int DP[1001] = {};
		while(I--) {
			scanf("%d %d %d", &v, &w, &t);
			if(t == -1) {
				for(a = w; a <= C; a++) {
					if(DP[a] < DP[a-w] + v)
						DP[a] = DP[a-w] + v;
				}
			}
			else {
				while(t) {
					for(a = C - w; a >= 0; a--)
						if(DP[a+w] < DP[a] + v)
							DP[a+w] = DP[a] + v;
					t--;
				}
			}
		}
		printf("%d\n", DP[C]);
	}
	return 0;
}
