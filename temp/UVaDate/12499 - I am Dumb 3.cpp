// Staircase Nim, Game Theory
#include <stdio.h>

int main() {
	int testcase, cases = 0;
	int N, L, A[64];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &N, &L);
		for (int i = 0; i < N; i++)
			scanf("%d", &A[i]);
		A[N] = L;
		
		int s = 0;
		for (int i = 0; i < N; i += 2)
			s ^= A[i+1] - A[i];
		printf("Case %d: %s\n", ++cases, s ? "First Player" : "Second Player");
	}
	return 0;
}
