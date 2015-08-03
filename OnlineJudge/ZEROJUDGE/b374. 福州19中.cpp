#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, x;
	while (scanf("%d", &n) == 1) {
		int A[32768] = {};
		for (int i = 0; i < n; i++)
			scanf("%d", &x), A[x]++;
		int cnt = A[(max_element(A, A+32768) - A)];
		for (int i = 0; i < 32768; i++)
			if (A[i] == cnt)
				printf("%d %d\n", i, cnt);
	}
	return 0;
}
