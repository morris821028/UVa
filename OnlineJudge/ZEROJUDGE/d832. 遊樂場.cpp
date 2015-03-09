#include<stdio.h>
#include<stdlib.h>
main() {
	int n , m, a, b, c, d;
	int A[10001] = {};
	while(scanf("%d %d", &n, &m) == 2) {
		for(a = 1; a <= n; a++)
			scanf("%d", &A[a]), A[a] += A[a-1];
		int max = 0;
		for(a = 1; a <= n; a++)
			for(b = a+1; b <= n; b++)
				for(c = b+1; c <= n; c++)
					for(d = c+1; d <= n; d++)
						if(max < A[b]-A[a-1] + A[d]-A[c-1])
							max = A[b]-A[a-1] + A[d]-A[c-1];
		printf("%d\n", max);
	}
	return 0;
}
/*
10 10
41 34 69 -78 62 5 -81 61 95 -27
300
*/

