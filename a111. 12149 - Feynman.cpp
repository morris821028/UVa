#include<stdio.h>
int main() {
	int N;
	while(scanf("%d", &N) == 1 && N)
		printf("%d\n", N*(N+1)*(2*N+1)/6);
	return 0;
}
