#include<stdio.h>
#include<stdlib.h>
int A[500000], pos[500000], LIS[500000];
int BinarySearch(int l, int r, int v) {
	int m, L = r;
	do {
		m = (l+r)/2;
		if(LIS[m] >= v) {
			if(m == 0)
				return m;
			else {
				if(LIS[m-1] < v)
					return m;
				else
					r = m-1;
			}
		} else {
			l = m+1;
		}
	}while(l <= r);
	return L+1;
}
int DP_LIS(int n) {
	int a, b, LIS_L = -1, set, Ans = 0;
	for(a = 0; a < n; a++) {
		set = BinarySearch(0, LIS_L, A[a]);
		LIS[set] = A[a], pos[a] = set;
		if(set >= LIS_L) LIS_L = set;
	}
	for(a = 0; a < n; a++)
		Ans = Ans > pos[a] ? Ans : pos[a];
	printf("%d\n-\n", Ans+1);
	LIS_L = Ans;
	for(a = n-1; a >=0; a--)
		if(pos[a] == Ans)
			LIS[Ans] = A[a], Ans--;
	for(a = 0; a <= LIS_L; a++)
		printf("%d\n", LIS[a]);
}
main() {
	int in = 0;
	while(scanf("%d", &A[in]) == 1)
		in++;
	DP_LIS(in);
	return 0;
}
