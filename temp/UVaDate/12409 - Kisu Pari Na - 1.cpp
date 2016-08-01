// Staircase Nim, Game Theory
#include <stdio.h>

int main() {
	int testcase, cases = 0;
	int R, C;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &R, &C);
		
		int s = 0, x;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				scanf("%d", &x);
				if (((R - i) + (C - j))%2)
					s ^= x; 
			}
		}
		printf("Case %d: %s\n", ++cases, s ? "win" : "lose");
	}
	return 0;
}
