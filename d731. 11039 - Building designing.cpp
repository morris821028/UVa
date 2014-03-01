#include<stdio.h>
#include<stdlib.h>
#define oo 2147483647
int A[500000], B[500000];
int cmp(const void *a, const void *b) {
	int *aa, *bb;
	aa = (int *)a, bb = (int *)b;
	return *aa < *bb;
}
main() {
	int t, n, x, a;
	scanf("%d", &t);
	while(scanf("%d", &n) == 1) {
		int Aidx = 0, Bidx = 0;
		for(a = 0; a < n; a++) {
			scanf("%d", &x);
			if(x > 0)	A[Aidx++] = x;
			else		B[Bidx++] = -x;
		}
		qsort(A, Aidx, sizeof(int), cmp);
		qsort(B, Bidx, sizeof(int), cmp);
		int in1 = 0, in2 = 0, last = oo, flag = 0;
		int tmp = 0, Ans = 0;
		while(in1 <= Aidx && in2 <= Bidx) {
			if(!flag) {
				while(A[in1] > last && in1 < Aidx)	in1++;
				if(in1 == Aidx)	break;
				last = A[in1], in1++;
			} else {
				while(B[in2] > last && in2 < Bidx)	in2++;
				if(in2 == Bidx)	break;
				last = B[in2], in2++;
			}
			tmp++, flag = 1-flag;
		}
		Ans = Ans > tmp ? Ans : tmp;
		in1 = 0, in2 = 0, last = oo, flag = 1, tmp = 0;
		while(in1 <= Aidx && in2 <= Bidx) {
			if(!flag) {
				while(A[in1] > last && in1 < Aidx)	in1++;
				if(in1 == Aidx)	break;
				last = A[in1], in1++;
			} else {
				while(B[in2] > last && in2 < Bidx)	in2++;
				if(in2 == Bidx)	break;
				last = B[in2], in2++;
			}
			tmp++, flag = 1-flag;
		}
		Ans = Ans > tmp ? Ans : tmp;
		printf("%d\n", Ans);
	}
	return 0;
}
