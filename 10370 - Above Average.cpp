#include<stdio.h>
int main() {
	int T, n, A[1000];
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		double sum = 0;
		int i, count = 0;
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]), sum += A[i];
		sum /= n;
		for(i = 0; i < n; i++)
			if(A[i] > sum)
				count++;
		printf("%.3lf%%\n", (double)count*100/n);
	}
    return 0;
}
