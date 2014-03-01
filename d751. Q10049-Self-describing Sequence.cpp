#include<stdio.h>
struct {
	int n, fn;
}A[4811];
int BinarySearch(int l, int r, int v) {
	int m;
	do {
		m = (l+r)/2;
		if(A[m].n < v)	l = m+1;
		else {
			if(A[m].n >= v && A[m-1].n < v)
				return m;
			r = m-1;
		}
	} while(l <= r);
}
int fn(int n, int limit) {
	int i, fn;
	if(n == 1)	return 1;
	i = BinarySearch(1, limit, n);
	i--;
	fn = (n - A[i].n)/i + A[i].fn;
	return fn;
}
main() {
	A[1].n = 1, A[1].fn = 1;
	A[2].n = 2, A[2].fn = 2;
	A[3].n = 6, A[3].fn = 4;
	int i;
	for(i = 4; i < 4811; i++) {
		A[i].n = A[i-1].n + fn(i-1, i-1)*(i-1);
		A[i].fn = A[i-1].fn + (A[i].n - A[i-1].n)/(i-1);
	}
	while(scanf("%d", &i) == 1 && i)
		printf("%d\n", fn(i, 4810));
	return 0;
}
