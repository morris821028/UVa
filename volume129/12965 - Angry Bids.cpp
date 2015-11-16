#include <bits/stdc++.h>
using namespace std;

int A[131072], B[131072], C[131072];
int main() {
	int testcase, n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]), C[i] = A[i];
		for (int i = 0; i < m; i++)
			scanf("%d", &B[i]), C[i+n] = B[i];
		C[n+m] = 0;
		sort(A, A+n);
		sort(B, B+m);
		sort(C, C+n+m+1);
		
		int price = 0, angry = INT_MAX;
		int idx1 = 0, idx2 = 0;
		for (int i = 0; i <= n+m; i++) {
			int test = C[i];
			while (idx1 < n && A[idx1] <= test)
				idx1++;
			while (idx2 < m && B[idx2] < test)
				idx2++;
			int v = n - idx1 + idx2;
			if (v < angry)
				angry = v, price = test;
		}
		printf("%d %d\n", price, angry);
	}
	return 0;
}

