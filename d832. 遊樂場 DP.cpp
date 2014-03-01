#include<stdio.h>
main() {
	int n, m, a;
	while(scanf("%d %d", &n, &m) == 2) {
		int A[10001] = {};
		for(a = 0; a < n; a++)
			scanf("%d", &A[a]);
		int max1 = 0, max2 = 0, sum = 0, t;
		for(a = n-1; a >= 0; a--) {
			sum +=	A[a];
			if(sum > max1) max1 = sum;
			if(sum < 0) {
				if(max1 > max2)	t = max2, max2 = max1, max1 = t;
				sum = 0;
			}
		}
		printf("%d\n", max1 + max2);
	}
	return 0;
}
