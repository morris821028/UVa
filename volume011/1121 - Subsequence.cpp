#include<stdio.h>
int main() {
	int N, S, A[100000], i;
	while(scanf("%d %d", &N, &S) == 2) {
		for(i = 0; i < N; i++)
			scanf("%d", &A[i]);
		int tail = -1, sum = 0;
		int min = 0xfffffff;
		for(i = 0; i < N; i++) {
			while(sum < S && tail+1 < N)
				sum += A[++tail];
			if(min > tail - i && sum >= S)
				min = tail - i;
			sum -= A[i];
		}
		if(min == 0xfffffff)	puts("0");
		else		printf("%d\n", min+1);
	}
    return 0;
}
