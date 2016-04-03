#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int C, V, A[1024] = {}, N;
		char s[1024], mm[3] = "CV";
		scanf("%d %d", &C, &V);
		N = C + V;
		for (int i = C; i < C+V; i++)
			A[i] = 1;
		
		int f = 0;
		do {
			for (int i = 0; i < N; i++)
				s[i] = mm[A[i]];
			s[N] = '\0';
			if (f)	putchar(' ');
			printf("%s", s), f = 1;
		} while (next_permutation(A, A+N));
		puts("");
	}
	return 0;
}

