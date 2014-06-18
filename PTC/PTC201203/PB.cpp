#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
long long Ans = 0;
int A[100000], X[100000];
int Merge(int l, int m, int r) {
	int In1 = l, In2 = m+1;
	int i, j, top = 0;
	long long D = 0;
	while(In1 <= m && In2 <= r) {
		if(A[In1] < A[In2])
			X[top++] = A[In1++], Ans += D;
		else
			X[top++] = A[In2++], D++;
	}
	while(In1 <= m)	X[top++] = A[In1++], Ans += D;
	while(In2 <= r)	X[top++] = A[In2++], D++;
	for(i = 0, j = l; i < top; i++, j++)
		A[j] = X[i];
}
int MergeSort(int l, int r) {
	if(l < r) {
		int m = (l+r)/2;
		MergeSort(l, m);
		MergeSort(m+1, r);
		Merge(l, m, r);
	}
}
int main() {
	int T, n, i;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]);
		Ans = 0;
		MergeSort(0, n-1);
		printf("%lld\n", Ans);
	}
    return 0;
}
