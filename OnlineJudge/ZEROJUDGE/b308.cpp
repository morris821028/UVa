#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase, A[5], B[5], P;
	int coin[] = {1, 5, 10, 50, 100};
	scanf("%d", &testcase);
	while (testcase--) {
		for (int i = 0; i < 5; i++)
			scanf("%d", &A[i]);
		for (int i = 0; i < 5; i++)
			scanf("%d", &B[i]);
		scanf("%d", &P);
		int dp[2048] = {};
		dp[0] = 1;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < A[i]; j++) {
				for (int k = 2048 - 1; k >= coin[i]; k--)
					dp[k] |= dp[k - coin[i]];
			}
		}
		int test = 0, mn = 0x3f3f3f3f;
		for (int i = P; i < 2048; i++) {
			if (dp[i]) {
				test++;
				int t = i - P, s = 0, c;
				for (int j = 4; j >= 0; j--) {
					c = min(B[j], t/coin[j]);
					s += c, t -= c * coin[j];
				}
				if (t == 0)		mn = min(mn, s);
			}
		}
		if (test == 0)
			puts("I HAVE MAGIC!");
		else {
			if (mn == 0x3f3f3f3f)
				puts("YOU ARE MAGICIAN!");
			else
				printf("%d\n", mn);
		}
	}
	return 0;
}
