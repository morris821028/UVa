#include<stdio.h>
#include<stdlib.h>
int cmp(const void *a, const void *b) {
	int *aa, *bb;
	aa = (int *)a, bb = (int *)b;
	if((*aa)%10 < (*bb)%10)	return 0;
	else if((*aa)%10 > (*bb)%10) return 1;
	else {
		return *aa < *bb;
	}
}
main() {
	int n, A[1001], a;
	while(scanf("%d", &n) == 1) {
		for(a = 0; a < n; a++)
			scanf("%d", &A[a]);
		qsort(A, n, sizeof(int), cmp);
		for(a = 0; a < n; a++)
			printf("%d ", A[a]);
		puts("");
	}
	return 0;
}
