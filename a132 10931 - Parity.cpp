#include<stdio.h>
int t, N;
int D(int N) {
	if(N) {
		D(N/2);
		printf("%d",N&1), t += N&1;
	}
}
main() {
	while(scanf("%d", &N) == 1 && N) {
		printf("The parity of ");
		t = 0, D(N);
		printf(" is %d (mod 2).\n", t);
	}
	return 0;
}

