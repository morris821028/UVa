#include <stdio.h>

int main() {
	int T, i, j;
	scanf("%d", &T);
	while(T--) {
		int N, P, W, G, MW, Ans = 0;
		int DP[31] = {};
		scanf("%d", &N);
		for(i = 0; i < N; i++) {
			scanf("%d %d", &P, &W);
			for(j = 30; j >= W; j--)
				if(DP[j] < DP[j-W]+P)
					DP[j] = DP[j-W]+P;
		}
		scanf("%d", &G);
		while(G--) {
			scanf("%d", &MW);
			Ans += DP[MW];
		}
		printf("%d\n", Ans);
	}
    return 0;
}
