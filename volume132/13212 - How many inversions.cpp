#include <bits/stdc++.h>
using namespace std;

long long ret;
const int MAXN = 1048576;
void merge(int A[], int l, int m, int r) {
	int idx1 = l, idx2 = m+1;
	int top = 0, cnt = 0;
	static int B[MAXN];
	while (idx1 <= m && idx2 <= r) {
		if (A[idx1] <= A[idx2])
			B[top++] = A[idx1++], ret += cnt;
		else
			B[top++] = A[idx2++], cnt++;
	}
	while (idx1 <= m)
		B[top++] = A[idx1++], ret += cnt;
	while (idx2 <= r)
		B[top++] = A[idx2++];
	for (int i = 0; i < top; i++)
		A[l+i] = B[i];
}
void mergesort(int A[], int l, int r) {
	if (l >= r)	return ;
	int m = (l+r)>>1;
	mergesort(A, l, m);
	mergesort(A, m+1, r);
	merge(A, l, m, r);
}

int main() {
	static int A[MAXN], n;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		ret = 0;
		mergesort(A, 0, n-1);
//		for (int i = 0; i < n; i++)
//			printf("%d\n", A[i]);
		printf("%lld\n", ret);
	}
	return 0;
}
/*
5
3 2 8 1 6
5
5 4 3 2 1
1
10
0
*/
