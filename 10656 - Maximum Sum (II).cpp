#include<stdio.h>
#include<stdlib.h>
int main() {
	int N, A[1000], i;
	while(scanf("%d", &N) == 1 && N) {
		int MaxSub[1000], idx = 0;
		for(i = 0; i < N; i++) {
			scanf("%d", &A[i]);
			if(A[i] > 0)
				MaxSub[idx++] = A[i];
		}
		if(idx == 0)	puts("0");
		else {
			for(i = 0; i < idx-1; i++)
				printf("%d ", MaxSub[i]);
			printf("%d\n", MaxSub[i]);
		}
	} 
    return 0;
}
