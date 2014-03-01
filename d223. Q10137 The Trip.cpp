#include<stdio.h>
main() {
	int n, A[1000], x, y, i, j;
	while(scanf("%d", &n) == 1 && n) {
		int sum = 0;
		for(i = 0; i < n; i++) {
			scanf("%d.%d", &x, &y);
			A[i] = x*100+y, sum += A[i];
		}
		int ave = sum/n, tmp = 0;
		int t1 = 0, t2 = 0;
		for(i = 0; i < n; i++)
			if(A[i] < ave) {
				t1 += ave - A[i];
				A[i] = ave;
			}
		t2 = t1;
		for(i = 0; i < n; i++)
			if(A[i] > ave) {
				t2 -= A[i] - ave;
				A[i] = ave;
				tmp ++;
			}
		if(t2 < 0) {
			if(-t2 > tmp)
				t1 += -(t2+tmp);
		}
		printf("$%d.%02d\n", t1/100, t1%100);
	}
	return 0;
}
