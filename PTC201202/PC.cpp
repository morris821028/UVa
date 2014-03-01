#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int A[100000];
int main() {
	int N, i;
	while(scanf("%d", &N) == 1) {
		for(i = 0; i < N; i++)
			scanf("%d", &A[i]);
		long long E = 0, max = A[0];
		for(i = 1; i < N; i++) {
			if(A[i] >= max)
				max = A[i];
			else
				E += i;
		}
		printf("%lld.000\n", E);
	}
    return 0;
}
