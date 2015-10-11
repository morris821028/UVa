#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, A[100], ret = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++)
					ret += A[i]*A[i] + A[j]*A[j] == A[k]*A[k];
			}
		}
		printf("%d\n", ret/2);
	}
	return 0;
}

