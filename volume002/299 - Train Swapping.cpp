#include<stdio.h>
int main() {
	int N, L, A[50];
	scanf("%d", &N);
	while(N--) {
		scanf("%d", &L);
		int i, j, count = 0, tmp;
		for(i = 0; i < L; i++)
			scanf("%d", &A[i]);
		for(i = 0; i < L; i++) {
			for(j = L-1; j > i; j--) {
				if(A[j] < A[j-1]) {
					tmp = A[j];
					A[j] = A[j-1];
					A[j-1] = tmp;
					count++;
				}
			}
		}
		printf("Optimal train swapping takes %d swaps.\n", count);
	}
    return 0;
}
