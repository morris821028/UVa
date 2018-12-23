#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
int compute_inv(int A[], int l, int r) {
	if (l >= r)	return 0;
	static int tmp[MAXN];
	int m = (l+r)/2;
	int ret = compute_inv(A, l, m) + compute_inv(A, m+1, r);
	int idx1 = l, idx2 = m+1, i = 0;
	while (idx1 <= m && idx2 <= r) {
		if (A[idx1] <= A[idx2])
			tmp[i++] = A[idx1++];
		else
			tmp[i++] = A[idx2++], ret += (m-idx1+1)&1;
	}
	while (idx1 <= m)	tmp[i++] = A[idx1++];
	while (idx2 <= r)	tmp[i++] = A[idx2++];
	memcpy(A+l, tmp, sizeof(A[0])*i);
	return ret&1;
}
int solvable(int n, int A[]) {
	int zero_pos = 0;
	for (int i = 0; i < n*n*n; i++) {
		if (A[i] == 0) {
			zero_pos = i;
			for (; i < n*n*n-1; i++)
				A[i] = A[i+1];
			break;
		}
	}
	int inv = compute_inv(A, 0, n*n*n-2);
	if (n&1) {
		// y: n-1 even, z: n^2-1 even
		if (inv&1)
			return 0;
	} else {
		// y: n-1 odd, z: n^2-1 odd
		int axis[3];
		for (int i = 0; i < 3; i++)
			axis[i] = zero_pos%n, zero_pos /= n;
		int offset = (n-1-axis[2]) + (n-1-axis[1]);
		if ((offset^inv)&1)
			return 0;
	}	
	return 1;
}
int main() {
	int testcase;
	static int A[MAXN], n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					int pos = n*n*i+n*j+k;
					scanf("%d", &A[pos]);
				}
			}
		}
		int ret = solvable(n, A);
		if (!ret)
			puts("Puzzle is unsolvable.");
		else
			puts("Puzzle can be solved.");
	}
	return 0;
}
/*
2
2
1 2 3 4
5 7 6 0
2
2 1 3 5
4 6 0 7
*/
