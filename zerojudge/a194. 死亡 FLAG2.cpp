#include<stdio.h>
#include<string.h>
int A[502], pos[502], LIS[502];
int Search(int l, int r, int v) {
	int m, L = r;
	if(l > r)	return 0;
	do {
		m = (l+r)/2;
		if(LIS[m] <= v) {
			if(m == L || LIS[m+1] > v)
				return m+1;
			l = m+1;
		}  else
			r = m-1;
	}while(l <= r);
	return 0;
}
int DP_LIS(int n) {
	int i, L = -1, set;
	for(i = 0; i < n; i++) {
		set = Search(0, L, A[i]);
		LIS[set] = A[i], pos[i] = set;
		if(set >= L)	L = set;
	}
	return L+1;
}
main() {
	int i, n;
	while(scanf("%d", &n) == 1) {
		for(i = n-1; i >= 0; i--)
			scanf("%d", &A[i]);
		printf("%d\n", DP_LIS(n));
	}
	return 0;
}
