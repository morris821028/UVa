#include <stdio.h>
#include <stdlib.h>

void findLIS(int A[], int LIS[], int n) {
	int pos[10000] = {};
	int i, j, m, l, r, newSet;
	int L = -1;
	for(i = 0; i < n; i++) {
		l = 0, r = L, newSet = -1;
		while(l <= r) {
			m = (l+r)/2;
			if(pos[m] < A[i]) {
				if(m == L || pos[m+1] >= A[i]) {
					newSet = m+1;
					break;
				} else
					l = m+1;
			} else
				r = m-1;
		}
		if(newSet == -1)
			newSet = 0;
		pos[newSet] = A[i];
		LIS[i] = newSet+1;
		if(L < newSet)
			L = newSet;
	}
}
int main() {
	int n, i, j, tmp;
	int A[10000], LIS[10000], LDS[10000];
	while(scanf("%d", &n) == 1) {
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]);
		findLIS(A, LIS, n);
		for(i = 0, j = n-1; i < j; i++, j--)
			tmp = A[i], A[i] = A[j], A[j] = tmp;
		findLIS(A, LDS, n);
		for(i = 0, j = n-1; i < j; i++, j--)
			tmp = LDS[i], LDS[i] = LDS[j], LDS[j] = tmp;
		int min, ans = 0;
		for(i = 0; i < n; i++) {
			min = LIS[i] < LDS[i] ? LIS[i] : LDS[i];
			min = min*2-1;
			if(min > ans)
				ans = min;
		}
		printf("%d\n", ans);
	}
    return 0;
}
