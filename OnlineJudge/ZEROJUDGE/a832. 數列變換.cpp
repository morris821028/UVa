#include <bits/stdc++.h> 
using namespace std;

void f(int A[], int n, int k) {
	for (int i = 0; ; i += k) {
		int l = i, r = min(i + k-1, n-1);
		int x = A[l];
		for (int j = l+1; j <= r; j++)
			A[j-1] = A[j];
		A[r] = x;
		if (r == n-1)	break;
	}
} 
int main() {
	int n, A[1024];
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			A[i] = i;
		for (int s = 1; s <= n; s++)
			f(A, n, s);
		for (int i = 0; i < n; i++)
			printf("%d%c", A[i]+1, i == n-1 ? '\n' : ' ');
	}
	return 0;
}
